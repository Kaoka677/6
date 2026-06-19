#ifndef BST_HPP
#define BST_HPP

#include <iostream>

// ĐỊNH NGHĨA NODE CỦA BINARY SEARCH TREE
template <typename T>
struct TreeNode
{
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode(T val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// KHAI BÁO VÀ ĐỊNH NGHĨA BINARY SEARCH TREE
template <typename T>
struct BST
{
    TreeNode<T> *root; // Con trỏ quản lý nút gốc của cây nhị phân tìm kiếm
    int count;         // Đếm số lượng nút có trong cây nhị phân tìm kiếm

    BST()
    {
        root = nullptr;
        count = 0;
    }

    // Tự động được gọi khi cây nhị phân tìm kiếm bị hủy để tránh rò rỉ bộ nhớ
    ~BST()
    {
        clear();
    }

    /*
     * Hàm hỗ trợ đệ quy chèn phần tử mới vào cây nhị phân tìm kiếm
     * Input: Nút hiện tại, giá trị val cần chèn vào, biến kiểm tra đã chèn chưa (Nhằm cập nhật count)
     * Output: Con trỏ tới nút
     */
    TreeNode<T> *insertHelper(TreeNode<T> *node, const T &val, bool &added)
    {
        if (!node)
        {
            node = new TreeNode<T>(val);
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
        return node;
    }

    // Thêm phần tử vào cây nhị phân tìm kiếm
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
     * Hàm hỗ trợ đệ quy xóa phần tử ra khỏi cây nhị phân tìm kiếm
     * Input: Nút hiện tại, giá trị val cần xóa đi, biến kiểm tra đã xóa chưa (Nhằm cập nhật count)
     * Output: Con trỏ tới nút
     */
    TreeNode<T> *removeHelper(TreeNode<T> *node, const T &val, bool &removed)
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
                TreeNode<T> *current = node->right;
                while (current->left)
                {
                    current = current->left; // Tìm phần tử có giá trị nhỏ nhất ở cây con bên phải
                }
                node->data = current->data;
                node->right = removeHelper(node->right, current->data, removed);
            }
            else if (node->left)
            { // Nút muốn xóa có 1 con bên trái
                TreeNode<T> *temp = node->left;
                delete node;
                node = nullptr;
                return temp;
            }
            else if (node->right)
            { // Nút muốn xóa có 1 con bên phải
                TreeNode<T> *temp = node->right;
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
        return node;
    }

    // Xóa phần tử ra khỏi cây nhị phân tìm kiếm
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
     * Hàm hỗ trợ đệ quy kiểm tra xem phần tử có trong cây nhị phân tìm kiếm không
     * Input: Nút hiện tại, giá trị val cần tìm kiếm
     * Output: Trả về true nếu tìm thấy, false nếu không tìm thấy
     */
    bool searchHelper(TreeNode<T> *node, const T &val) const
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

    // Kiểm tra xem phần tử có trong cây nhị phân tìm kiếm không
    bool search(const T &val) const
    {
        return searchHelper(root, val);
    }

    /*
     * Hàm hỗ trợ đệ quy tìm kiếm phần tử trong cây nhị phân tìm kiếm
     * Input: Nút hiện tại, giá trị val cần tìm kiếm
     * Output: Con trỏ tới nút được tìm kiếm
     */
    TreeNode<T> *searchNodeHelper(TreeNode<T> *node, const T &val) const
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

    // Tìm kiếm nút có giá trị val trong cây nhị phân tìm kiếm
    TreeNode<T> *searchNode(const T &val) const
    {
        return searchNodeHelper(root, val);
    }

    // Hàm hỗ trợ duyệt tiền thứ tự
    void preOrderHelper(TreeNode<T> *node) const
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
    void inOrderHelper(TreeNode<T> *node) const
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
    void postOrderHelper(TreeNode<T> *node) const
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

    // Lấy số lượng phần tử có trong cây nhị phân tìm kiếm
    int size() const
    {
        return count;
    }

    // Hàm hỗ trợ xóa cây từ lá đến gốc bằng cách duyệt hậu thứ tự
    void clearHelper(TreeNode<T> *node)
    {
        if (node)
        {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
            node = nullptr;
        }
    }

    // Xóa toàn bộ nút trong cây nhị phân tìm kiếm và giải phóng bộ nhớ
    void clear()
    {
        clearHelper(root);
        root = nullptr;
        count = 0;
    }
};

#endif