#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <algorithm>

// ĐỊNH NGHĨA NODE CỦA AVL TREE
template <typename T>
struct AVLNode
{
    T data;
    AVLNode<T> *left;
    AVLNode<T> *right;
    int height;

    AVLNode(T val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// KHAI BÁO VÀ ĐỊNH NGHĨA AVL TREE
template <typename T>
struct AVL
{
    AVLNode<T> *root; // Con trỏ quản lý nút gốc của cây cân bằng
    int count;        // Đếm số lượng nút có trong cây cân bằng

    AVL()
    {
        root = nullptr;
        count = 0;
    }

    // Tự động được gọi khi cây cân bằng bị hủy để tránh rò rỉ bộ nhớ
    ~AVL()
    {
        clear();
    }

    // Lấy chiều cao của nút
    int getHeight(AVLNode<T> *node) const
    {
        if (!node)
        {
            return 0;
        }
        return node->height;
    }

    // Cập nhật lại chiều cao của nút dựa trên 2 nhánh con
    void updateHeight(AVLNode<T> *node)
    {
        if (!node)
        {
            return;
        }
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    /*
     * Phép xoay phải
     * Input: Nút bị mất cân bằng
     * Output: Nút gốc mới của nhánh sau khi xoay
     */
    AVLNode<T> *rightRotate(AVLNode<T> *node)
    {
        if (!node->left)
        {
            return node;
        }

        AVLNode<T> *L = node->left;
        AVLNode<T> *rL = L->right;

        L->right = node;
        node->left = rL;

        updateHeight(node);
        updateHeight(L);

        return L;
    }

    /*
     * Phép xoay trái
     * Input: Nút bị mất cân bằng
     * Output: Nút gốc mới của nhánh sau khi xoay
     */
    AVLNode<T> *leftRotate(AVLNode<T> *node)
    {
        if (!node->right)
        {
            return node;
        }

        AVLNode<T> *R = node->right;
        AVLNode<T> *lR = R->left;

        R->left = node;
        node->right = lR;

        updateHeight(node);
        updateHeight(R);

        return R;
    }

    // Lấy hệ số cân bằng của nút
    int getBalance(AVLNode<T> *node) const
    {
        if (!node)
        {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    /*
     * Khôi phục tính cân bằng của cây tại một nút
     * Input: Con trỏ tới nút cần kiểm tra
     */
    void rebalance(AVLNode<T> *&node)
    {
        if (!node)
        {
            return;
        }
        if (getBalance(node) > 1)
        {
            if (getBalance(node->left) >= 0)
            { // Trường hợp lệch L-L (Trái - Trái)
                node = rightRotate(node);
            }
            else
            { // Trường hợp lệch L-R (Trái - Phải)
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }
        }
        else if (getBalance(node) < -1)
        { // Trường hợp lệch R-R (Phải - Phải)
            if (getBalance(node->right) <= 0)
            {
                node = leftRotate(node);
            }
            else
            { // Trường hợp lệch R-L (Phải - Trái)
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }
        }
    }

    // Hàm hỗ trợ xóa cây từ lá đến gốc bằng cách duyệt hậu thứ tự
    void clearHelper(AVLNode<T> *node)
    {
        if (node)
        {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
            node = nullptr;
        }
    }

    /*
     * Hàm hỗ trợ đệ quy chèn phần tử mới vào cây cân bằng
     * Input: Nút hiện tại, giá trị val cần chèn vào, biến kiểm tra đã chèn chưa (Nhằm cập nhật count)
     * Output: Con trỏ tới nút
     */
    AVLNode<T> *insertHelper(AVLNode<T> *node, const T &val, bool &added)
    {
        if (!node)
        {
            node = new AVLNode<T>(val);
            added = true;
            return node;
        }
        if (val < node->data)
        {
            node->left = insertHelper(node->left, val, added);
        }
        else if (val > node->data)
        {
            node->right = insertHelper(node->right, val, added);
        }
        updateHeight(node); // Cập nhật lại chiều cao tại nút
        rebalance(node);    // Khôi phục lại tính cân bằng của cây tại nút
        return node;
    }

    // Thêm phần tử vào cây cân bằng
    void insert(const T &val)
    {
        bool added = false;
        root = insertHelper(root, val, added);
        if (added)
        {
            count++;
        }
    }

    /*
     * Hàm hỗ trợ đệ quy xóa phần tử ra khỏi cây cân bằng
     * Input: Nút hiện tại, giá trị val cần xóa đi, biến kiểm tra đã xóa chưa (Nhằm cập nhật count)
     * Output: Con trỏ tới nút
     */
    AVLNode<T> *removeHelper(AVLNode<T> *node, const T &val, bool &removed)
    {
        if (!node)
        {
            return nullptr;
        }
        if (val < node->data)
        {
            node->left = removeHelper(node->left, val, removed);
        }
        else if (val > node->data)
        {
            node->right = removeHelper(node->right, val, removed);
        }
        else
        {
            removed = true;
            if (node->left && node->right)
            { // Nút muốn xóa có 2 con
                AVLNode<T> *current = node->right;
                while (current->left)
                {
                    current = current->left; // Tìm phần tử có giá trị nhỏ nhất ở cây con bên phải
                }
                node->data = current->data;
                node->right = removeHelper(node->right, current->data, removed);
            }
            else if (node->left)
            { // Nút muốn xóa có 1 con bên trái
                AVLNode<T> *temp = node->left;
                delete node;
                node = nullptr;
                return temp;
            }
            else if (node->right)
            { // Nút muốn xóa có 1 con bên phải
                AVLNode<T> *temp = node->right;
                delete node;
                node = nullptr;
                return temp;
            }
            else
            { // Nút muốn xóa không có con nào
                delete node;
                node = nullptr;
                return nullptr;
            }
        }
        updateHeight(node); // Cập nhật lại chiều cao tại nút
        rebalance(node);    // Khôi phục lại tính cân bằng của cây tại nút
        return node;
    }

    // Xóa phần tử ra khỏi cây cân bằng
    void remove(const T &val)
    {
        bool removed = false;
        root = removeHelper(root, val, removed);
        if (removed)
        {
            count--;
        }
    }

    /*
     * Hàm hỗ trợ đệ quy kiểm tra xem phần tử có trong cây cân bằng không
     * Input: Nút hiện tại, giá trị val cần tìm kiếm
     * Output: Trả về true nếu tìm thấy, false nếu không tìm thấy
     */
    bool searchHelper(AVLNode<T> *node, const T &val) const
    {
        if (!node)
        {
            return false;
        }
        if (val == node->data)
        {
            return true;
        }
        if (val < node->data)
        {
            return searchHelper(node->left, val);
        }
        else if (val > node->data)
        {
            return searchHelper(node->right, val);
        }
        return false;
    }

    // Kiểm tra xem phần tử có trong cây cân bằng không
    bool search(const T &val) const
    {
        return searchHelper(root, val);
    }

    /*
     * Hàm hỗ trợ đệ quy tìm kiếm phần tử trong cây cân bằng
     * Input: Nút hiện tại, giá trị val cần tìm kiếm
     * Output: Con trỏ tới nút được tìm kiếm
     */
    AVLNode<T> *searchNodeHelper(AVLNode<T> *node, const T &val) const
    {
        if (!node)
        {
            return nullptr;
        }
        if (val == node->data)
        {
            return node;
        }
        if (val < node->data)
        {
            return searchNodeHelper(node->left, val);
        }
        else
        {
            return searchNodeHelper(node->right, val);
        }
    }

    // Tìm kiếm phần tử trong cây cân bằng
    AVLNode<T> *searchNode(const T &val) const
    {
        return searchNodeHelper(root, val);
    }

    // Hàm hỗ trợ duyệt tiền thứ tự
    void preOrderHelper(AVLNode<T> *node) const
    {
        if (node)
        {
            std::cout << node->data << ' ';
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // Duyệt tiền thứ tự
    void preOrder() const
    {
        preOrderHelper(root);
        std::cout << '\n';
    }

    // Hàm hỗ trợ duyệt trung thứ tự
    void inOrderHelper(AVLNode<T> *node) const
    {
        if (node)
        {
            inOrderHelper(node->left);
            std::cout << node->data << ' ';
            inOrderHelper(node->right);
        }
    }

    // Duyệt trung thứ tự
    void inOrder() const
    {
        inOrderHelper(root);
        std::cout << '\n';
    }

    // Hàm hỗ trợ duyệt hậu thứ tự
    void postOrderHelper(AVLNode<T> *node) const
    {
        if (node)
        {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            std::cout << node->data << ' ';
        }
    }

    // Duyệt hậu thứ tự
    void postOrder() const
    {
        postOrderHelper(root);
        std::cout << '\n';
    }

    // Lấy số lượng phần tử có trong cây cân bằng
    int size() const
    {
        return count;
    }

    // Xóa toàn bộ nút trong cây cân bằng và giải phóng bộ nhớ
    void clear()
    {
        clearHelper(root);
        root = nullptr;
        count = 0;
    }

    // Hàm hỗ trợ đệ quy xuất dữ liệu ra mảng (Duyệt trung thứ tự để mảng tự động sắp xếp tăng dần)
    void toArrayHelper(AVLNode<T> *node, T *arr, int &index) const
    {
        if (node)
        {
            toArrayHelper(node->left, arr, index);
            arr[index++] = node->data;
            toArrayHelper(node->right, arr, index);
        }
    }

    /*
     * Hàm trích xuất toàn bộ phần tử trong cây AVL ra một mảng động
     * Output: Con trỏ trỏ tới mảng động chứa dữ liệu. NHỚ PHẢI DELETE MẢNG SAU KHI DÙNG XONG.
     */
    T *toArray() const
    {
        if (count == 0)
        {
            return nullptr;
        }
        T *arr = new T[count];
        int index = 0;
        toArrayHelper(root, arr, index);
        return arr;
    }
};

#endif