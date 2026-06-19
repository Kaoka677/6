#include <iostream>
#include <string>
#include <functional>

#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "Algorithms.hpp"
#include "BST.hpp"
#include "AVL.hpp"
#include "HashTable.hpp"

using namespace std;

void printSection(const string &title)
{
    cout << "\n==================== " << title << " ====================\n";
}

// In mảng dùng chung cho phần thuật toán sắp xếp và tìm kiếm
template <typename T>
void printArray(const T arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

void demoLinkedList()
{
    printSection("LINKED LIST");

    LinkedList<int> list;

    // insertBack(val): Thêm phần tử vào cuối danh sách
    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    // insertFront(val): Thêm phần tử vào đầu danh sách
    list.insertFront(5);

    // insertAt(index, val): Thêm phần tử vào vị trí index (Tính từ 0)
    list.insertAt(2, 15);

    cout << "Danh sách sau khi thêm: ";
    list.traverseForward();

    // traverseBackward(): Duyệt và in danh sách từ cuối lên đầu
    cout << "Duyệt ngược: ";
    list.traverseBackward();

    // find(val): Kiểm tra giá trị có tồn tại trong danh sách không
    cout << "Tìm giá trị 20: " << (list.find(20) ? "Có" : "Không") << '\n';

    // size(): Trả về số lượng phần tử hiện có
    cout << "Số phần tử hiện tại: " << list.size() << '\n';

    // remove(val): Xóa tất cả phần tử có giá trị bằng val
    list.remove(20);
    cout << "Sau khi remove(20): ";
    list.traverseForward();

    // removeAt(index): Xóa phần tử tại vị trí index
    list.removeAt(1);
    cout << "Sau khi removeAt(1): ";
    list.traverseForward();

    // reverse(): Đảo ngược danh sách
    list.reverse();
    cout << "Sau khi reverse(): ";
    list.traverseForward();

    // clear(): Xóa toàn bộ danh sách
    list.clear();
    cout << "Sau khi clear(), size = " << list.size() << '\n';
}

void demoStack()
{
    printSection("STACK");

    Stack<int> st;

    // push(val): Thêm phần tử vào đỉnh ngăn xếp
    st.push(10);
    st.push(20);
    st.push(30);

    cout << "Số phần tử trong stack: " << st.size() << '\n';

    // top(): Lấy giá trị phần tử ở đỉnh stack
    cout << "Phần tử ở đỉnh stack: " << st.top() << '\n';

    // pop(): Xóa phần tử ở đỉnh stack
    st.pop();
    cout << "Sau khi pop(), top = " << st.top() << '\n';

    // empty(): Kiểm tra stack rỗng hay không
    cout << "Stack có rỗng không? " << (st.empty() ? "Có" : "Không") << '\n';

    // clear(): Xóa toàn bộ stack
    st.clear();
    cout << "Sau khi clear(), stack có rỗng không? " << (st.empty() ? "Có" : "Không") << '\n';
}

void demoQueue()
{
    printSection("QUEUE");

    Queue<string> q;

    // enqueue(val): Thêm phần tử vào cuối hàng đợi
    q.enqueue("An");
    q.enqueue("Bình");
    q.enqueue("Cường");

    cout << "Số phần tử trong queue: " << q.size() << '\n';

    // front(): Lấy phần tử ở đầu hàng đợi
    cout << "Phần tử ở đầu hàng đợi: " << q.front() << '\n';

    // back(): Lấy phần tử ở cuối hàng đợi
    cout << "Phần tử ở cuối hàng đợi: " << q.back() << '\n';

    // dequeue(): Xóa phần tử ở đầu hàng đợi
    q.dequeue();
    cout << "Sau khi dequeue(), front = " << q.front() << '\n';

    // empty(): Kiểm tra hàng đợi rỗng hay không
    cout << "Queue có rỗng không? " << (q.empty() ? "Có" : "Không") << '\n';

    // clear(): Xóa toàn bộ hàng đợi
    q.clear();
    cout << "Sau khi clear(), queue có rỗng không? " << (q.empty() ? "Có" : "Không") << '\n';
}

void demoPriorityQueue()
{
    printSection("PRIORITY QUEUE");

    PriorityQueue<string> pq;

    // insert(val, priority): Thêm phần tử với mức ưu tiên tương ứng
    // Quy ước: priority càng lớn thì mức ưu tiên càng cao
    pq.insert("Việc bình thường", 1);
    pq.insert("Việc khẩn cấp", 5);
    pq.insert("Việc trung bình", 3);
    pq.insert("Việc khẩn cấp thứ hai", 5);

    cout << "Số phần tử trong priority queue: " << pq.size() << '\n';

    // peek(): Lấy phần tử đang có độ ưu tiên cao nhất
    cout << "Phần tử ưu tiên cao nhất: " << pq.peek() << '\n';

    // extract(): Xóa phần tử ưu tiên cao nhất
    pq.extract();
    cout << "Sau khi extract(), phần tử ưu tiên cao nhất mới: " << pq.peek() << '\n';

    // empty(): Kiểm tra hàng đợi ưu tiên rỗng hay không
    cout << "Priority queue có rỗng không? " << (pq.empty() ? "Có" : "Không") << '\n';

    // clear(): Xóa toàn bộ hàng đợi ưu tiên
    pq.clear();
    cout << "Sau khi clear(), priority queue có rỗng không? " << (pq.empty() ? "Có" : "Không") << '\n';
}

void demoAlgorithms()
{
    printSection("ALGORITHMS");

    // Algorithms::swap(a, b): Hoán đổi 2 giá trị có cùng kiểu dữ liệu
    int x = 3;
    int y = 7;
    cout << "Trước swap: x = " << x << ", y = " << y << '\n';
    Algorithms::swap(x, y);
    cout << "Sau swap: x = " << x << ", y = " << y << '\n';

    int a1[] = {5, 1, 4, 2, 8};
    int a2[] = {5, 1, 4, 2, 8};
    int a3[] = {5, 1, 4, 2, 8};
    int a4[] = {5, 1, 4, 2, 8};
    int a5[] = {5, 1, 4, 2, 8};
    int a6[] = {5, 1, 4, 2, 8};
    int n = 5;

    // Các hàm sort mặc định dùng std::less<T>() (Sắp xếp tăng dần)
    // Tại thầy yêu cầu sắp xếp cả tăng dần và giảm dần, m thử xem source code là hiểu nha
    Algorithms::bubbleSort(a1, n);
    cout << "Bubble Sort tăng dần: ";
    printArray(a1, n);

    Algorithms::selectionSort(a2, n);
    cout << "Selection Sort tăng dần: ";
    printArray(a2, n);

    Algorithms::insertionSort(a3, n);
    cout << "Insertion Sort tăng dần: ";
    printArray(a3, n);

    Algorithms::heapSort(a4, n);
    cout << "Heap Sort tăng dần: ";
    printArray(a4, n);

    Algorithms::quickSort(a5, 0, n - 1);
    cout << "Quick Sort tăng dần: ";
    printArray(a5, n);

    Algorithms::mergeSort(a6, n);
    cout << "Merge Sort tăng dần: ";
    printArray(a6, n);

    // Truyền comparator std::greater<int>() để sắp xếp giảm dần
    int descArr[] = {5, 1, 4, 2, 8};
    Algorithms::mergeSort(descArr, n, greater<int>());
    cout << "Merge Sort giảm dần: ";
    printArray(descArr, n);

    // linearSearch(arr, n, key): Tìm kiếm tuyến tính, không yêu cầu mảng đã sắp xếp sẵn
    int unsortedArr[] = {12, 4, 9, 20, 7};
    cout << "linearSearch tìm 20, vị trí = " << Algorithms::linearSearch(unsortedArr, 5, 20) << '\n';

    // binarySearch(arr, n, key): Tìm kiếm nhị phân, yêu cầu mảng đã sắp xếp theo comparator tương ứng
    int ascArr[] = {1, 3, 5, 7, 9};
    cout << "binarySearch tăng dần tìm 7, vị trí = " << Algorithms::binarySearch(ascArr, 5, 7) << '\n';

    int sortedDescArr[] = {9, 7, 5, 3, 1};
    cout << "binarySearch giảm dần tìm 7, vị trí = " << Algorithms::binarySearch(sortedDescArr, 5, 7, greater<int>()) << '\n';
}

void demoBST()
{
    printSection("BST");

    BST<int> tree;

    // insert(val): Thêm phần tử vào cây BST
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Duyệt trung thứ tự inOrder(): ";
    tree.inOrder();

    cout << "Duyệt tiền thứ tự preOrder(): ";
    tree.preOrder();

    cout << "Duyệt hậu thứ tự postOrder(): ";
    tree.postOrder();

    // search(val): Kiểm tra giá trị có tồn tại trong cây hay không
    cout << "Tìm giá trị 40: " << (tree.search(40) ? "Có" : "Không") << '\n';

    // searchNode(val): Trả về con trỏ tới node chứa giá trị cần tìm kiếm
    TreeNode<int> *foundNode = tree.searchNode(60);
    if (foundNode)
    {
        cout << "searchNode(60) tìm thấy node có data = " << foundNode->data << '\n';
    }

    // size(): Trả về số lượng node trong cây
    cout << "Số node trong BST: " << tree.size() << '\n';

    // remove(val): Xóa một giá trị khỏi cây
    tree.remove(70);
    cout << "Sau khi remove(70), inOrder(): ";
    tree.inOrder();

    // clear(): Xóa toàn bộ cây
    tree.clear();
    cout << "Sau khi clear(), size = " << tree.size() << '\n';
}

void demoAVL()
{
    printSection("AVL");

    AVL<int> avl;

    // insert(val): Thêm phần tử vào cây AVL và tự cân bằng
    avl.insert(30);
    avl.insert(20);
    avl.insert(10); // Cây lệch trái, AVL sẽ tự cân bằng lại
    avl.insert(25);
    avl.insert(40);
    avl.insert(50); // Cây lệch phải, AVL sẽ tự cân bằng lại

    cout << "Duyệt trung thứ tự inOrder(): ";
    avl.inOrder();

    cout << "Duyệt tiền thứ tự preOrder(): ";
    avl.preOrder();

    cout << "Duyệt hậu thứ tự postOrder(): ";
    avl.postOrder();

    // getHeight(node): Lấy chiều cao của một node
    cout << "Chiều cao của root: " << avl.getHeight(avl.root) << '\n';

    // getBalance(node): Lấy hệ số cân bằng của một node
    cout << "Hệ số cân bằng của root: " << avl.getBalance(avl.root) << '\n';

    // search(val): Kiểm tra giá trị có tồn tại trong cây hay không
    cout << "Tìm giá trị 25: " << (avl.search(25) ? "Có" : "Không") << '\n';

    // searchNode(val): Trả về con trỏ tới node chứa giá trị cần tìm kiếm
    AVLNode<int> *foundNode = avl.searchNode(40);
    if (foundNode)
    {
        cout << "searchNode(40) tìm thấy node có data = " << foundNode->data << '\n';
    }

    // size(): Trả về số lượng node trong cây
    cout << "Số node trong AVL: " << avl.size() << '\n';

    // remove(val): Xóa một giá trị khỏi cây AVL và tự cân bằng lại
    avl.remove(20);
    cout << "Sau khi remove(20), inOrder(): ";
    avl.inOrder();

    // clear(): Xóa toàn bộ cây AVL
    avl.clear();
    cout << "Sau khi clear(), size = " << avl.size() << '\n';
}

void demoHashTable()
{
    printSection("HASH TABLE");

    HashTable<int, string> students(7);

    // insert(key, value): Thêm cặp key - value vào bảng băm
    students.insert(10, "An");
    students.insert(17, "Bình");  // 10 và 17 có thể cùng bucket nếu capacity = 7
    students.insert(24, "Cường"); // Tiếp tục minh họa đụng độ
    students.insert(31, "Dung");

    cout << "Số phần tử trong HashTable: " << students.size() << '\n';

    // hashFunction(key): Xem key được ánh xạ vào bucket nào
    cout << "Bucket của key 10: " << students.hashFunction(10) << '\n';
    cout << "Bucket của key 17: " << students.hashFunction(17) << '\n';

    // find(key): Trả về con trỏ tới value nếu tìm thấy, ngược lại trả về NULL
    string *name = students.find(17);
    if (name)
    {
        cout << "find(17) = " << *name << '\n';
    }

    // findPair(key): Trả về con trỏ tới cả cặp pair<key, value>
    pair<int, string> *pairPtr = students.findPair(24);
    if (pairPtr)
    {
        cout << "findPair(24) = (" << pairPtr->first << ", " << pairPtr->second << ")\n";
    }

    // contains(key): Kiểm tra key có tồn tại hay không
    cout << "contains(31): " << (students.contains(31) ? "Có" : "Không") << '\n';
    cout << "contains(99): " << (students.contains(99) ? "Có" : "Không") << '\n';

    // Nếu insert lại key đã tồn tại, HashTable cập nhật value mới cho key đó
    students.insert(17, "Bình đã cập nhật");
    cout << "Sau khi insert lại key 17, find(17) = " << *students.find(17) << '\n';

    // remove(key): Xóa cặp key - value theo key
    students.remove(10);
    cout << "Sau khi remove(10), contains(10): " << (students.contains(10) ? "Có" : "Không") << '\n';
    cout << "Số phần tử sau khi xóa: " << students.size() << '\n';

    // clear(): Xóa toàn bộ bảng băm
    students.clear();
    cout << "Sau khi clear(), size = " << students.size() << '\n';
}

int main()
{
    cout << "DEMO CÁCH DÙNG\n";

    demoLinkedList();
    demoStack();
    demoQueue();
    demoPriorityQueue();
    demoAlgorithms();
    demoBST();
    demoAVL();
    demoHashTable();

    cout << "\nHẾT\n";
    return 0;
}