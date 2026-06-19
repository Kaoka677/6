#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>

// ĐỊNH NGHĨA NODE CỦA LINKED LIST
template <typename T>
struct ListNode {
    T data;
    ListNode<T>* next;

    ListNode(T val) {
        data = val;
        next = nullptr;
    }
};

// KHAI BÁO VÀ ĐỊNH NGHĨA LINKED LIST
template <typename T>
struct LinkedList {
    ListNode<T>* head;   // Con trỏ quản lý đầu danh sách liên kết
    ListNode<T>* tail;   // Con trỏ quản lý cuối danh sách liên kết
    int count;           // Đếm số lượng phần tử trong danh sách liên kết

    LinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    // Tự động được gọi khi danh sách liên kết bị hủy để tránh rò rỉ bộ nhớ
    ~LinkedList() {
        clear();
    }

    /*
     * Thêm phần tử vào đầu danh sách liên kết
     * Input: Giá trị val cần thêm vào
     */
    void insertFront(const T& val) {
        ListNode<T>* newNode = new ListNode<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        count++;
    }

    /*
     * Thêm phần tử vào cuối danh sách liên kết
     * Input: Giá trị val cần thêm vào
     */
    void insertBack(const T& val) {
        ListNode<T>* newNode = new ListNode<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    /*
     * Thêm phần tử vào một vị trí cụ thể trong danh sách liên kết (Tính từ 0)
     * Input: Vị trí index (0 <= index <= count) và giá trị val cần thêm vào
     */
    void insertAt(int index, const T& val) {
        if (index < 0 || index > count) {
            return;
        }
        
        // Xử lý nếu thêm phần tử ở đầu mảng hoặc cuối mảng
        if (index == 0) {
            insertFront(val);
            return;
        } else if (index == count) {
            insertBack(val);
            return;
        }

        ListNode<T>* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        ListNode<T>* newNode = new ListNode<T>(val);
        newNode->next = current->next;
        current->next = newNode;
        count++;
    }

    /*
     * Xóa tất cả các phần tử trong danh sách liên kết có giá trị bằng với một giá trị cho trước
     * Input: Giá trị val cần xóa đi
     */
    void remove(const T& val) {
        // Xóa liên tục nếu các giá trị đầu danh sách liên kết bằng val
        while (head && head->data == val) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
            temp = nullptr;
            count--;
        }

        if (!head) {
            tail = nullptr;
            return;
        }

        // Tìm và xóa các phần tử bằng val ở phần thân và cuối danh sách liên kết
        ListNode<T>* current = head;
        while (current->next) {
            if (current->next->data == val) {
                ListNode<T>* temp = current->next;
                current->next = temp->next;
                if (temp == tail) {
                    tail = current;
                }
                delete temp;
                temp = nullptr;
                count--;
            } else {
                current = current->next;
            }
        }
    }

    /*
     * Xóa phần tử tại một vị trí cụ thể trong danh sách liên kết (Tính từ 0)
     * Input: Vị trí index cần xóa đi (0 <= index < count)
     */
    void removeAt(int index) {
        if (index < 0 || index >= count) {
            return;
        }

        // Xử lý nếu xóa phần tử ở đầu danh sách
        if (index == 0) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
            temp = nullptr;
            count--;
            if (!head) {
                tail = nullptr;
            }
            return;
        }

        ListNode<T>* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        ListNode<T>* temp = current->next;
        current->next = temp->next;
        if (temp == tail) {
            tail = current;
        }
        delete temp;
        temp = nullptr;
        count--;
    }

    /*
     * Kiểm tra xem một giá trị cho trước có tồn tại trong danh sách liên kết hay không
     * Input: Giá trị val cần tìm kiếm
     * Output: Trả về true nếu tìm thấy, false nếu không tìm thấy
     */
    bool find(const T& val) const {
        ListNode<T>* current = head;
        while (current) {
            if (current->data == val) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Lấy số lượng phần tử có trong danh sách liên kết
    int size() const {
        return count;
    }

    // Xóa tất cả phần tử có trong danh sách liên kết và giải phóng bộ nhớ
    void clear() {
        ListNode<T>* current = head;
        while (current) {
            ListNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    // Đảo ngược thứ tự toàn bộ các phần tử trong danh sách liên kết
    void reverse() {
        if (!head || head == tail) {
            return; // Nếu danh sách liên kết rỗng hoặc có 1 phần tử thì không cần đảo
        }

        ListNode<T>* prev = nullptr;
        ListNode<T>* current = head;
        ListNode<T>* nextNode = nullptr;

        tail = head;

        while (current) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }

        head = prev;
    }

    // Duyệt và in tất cả các phần tử trong danh sách liên kết từ đầu đến cuối
    void traverseForward() const {
        ListNode<T>* current = head;
        while (current) {
            std::cout << current->data << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }

    // Hàm hỗ trợ dùng đệ quy để duyệt và in danh sách từ cuối lên đầu
    void traverseBackwardsHelper(ListNode<T>* node) const {
        if (!node) return;
        traverseBackwardsHelper(node->next);
        std::cout << node->data << ' ';
    }

    // Duyệt và in tất cả các phần tử trong danh sách liên kết từ cuối lên đầu
    void traverseBackward() const {
        traverseBackwardsHelper(head);
        std::cout << '\n';
    }
};

#endif