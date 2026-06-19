#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <functional>
#include <utility>
#include "AVL.hpp"

/*
 * KHAI BÁO VÀ ĐỊNH NGHĨA HASH TABLE
 * MỖI BUCKET LÀ MỘT AVL TREE, XỬ LÝ ĐỤNG ĐỘ BẰNG SEPARATE CHAINING
 */
template <typename K, typename V>
struct HashTable
{
    AVL<std::pair<K, V>> *table; // Con trỏ quản lý mảng động chứa các cây AVL là các buckets
    int capacity;                // Số lượng bucket hay sức chứa tối đa của bảng băm
    int count;                   // Tổng số cặp key - value được lưu trữ trong bảng băm

    HashTable(int cap = 101)
    {
        if (cap <= 0)
        {
            cap = 101;
        }
        capacity = cap;
        count = 0;
        table = new AVL<std::pair<K, V>>[capacity];
    }

    // Tự động được gọi khi bảng băm bị hủy để tránh rò rỉ bộ nhớ
    ~HashTable()
    {
        clear();
        delete[] table;
        table = nullptr;
    }

    // Hàm băm biến đổi khóa thành index hợp lệ trong mảng table
    int hashFunction(const K &key) const
    {
        std::hash<K> hashFn;
        return static_cast<int>(hashFn(key) % capacity);
    }

    // Tìm kiếm và trả về cặp key - value thông qua khóa
    std::pair<K, V> *findPair(const K &key) const
    {
        int idx = hashFunction(key);
        AVLNode<std::pair<K, V>> *current = table[idx].root;
        while (current)
        {
            if (key == current->data.first)
            {
                return &(current->data);
            }
            else if (key < current->data.first)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return nullptr;
    }

    // Thêm phần tử vào bảng băm
    void insert(const K &key, const V &value)
    {
        std::pair<K, V> *found = findPair(key);

        // Nếu như đã tồn tại key thì cập nhật lại value
        if (found)
        {
            found->second = value;
            return;
        }

        int idx = hashFunction(key);
        table[idx].insert(std::make_pair(key, value));
        count++;
    }

    // Xóa phần tử ra khỏi bảng băm
    void remove(const K &key)
    {
        int idx = hashFunction(key);

        std::pair<K, V> *found = findPair(key);
        if (!found)
        {
            return;
        }

        std::pair<K, V> target = *found;
        table[idx].remove(target);
        count--;
    }

    // Tìm kiếm và trả về giá trị thông qua khóa
    V *find(const K &key) const
    {
        std::pair<K, V> *found = findPair(key);

        if (found)
        {
            return &(found->second);
        }

        return nullptr;
    }

    // Kiểm tra xem một khóa có nằm trong bảng băm hay không
    bool contains(const K &key) const
    {
        return find(key) != nullptr;
    }

    // Lấy tổng số phần tử có trong bảng băm
    int size() const
    {
        return count;
    }

    // Xóa toàn bộ dữ liệu trong bảng băm
    void clear()
    {
        for (int i = 0; i < capacity; i++)
        {
            table[i].clear();
        }
        count = 0;
    }
};

#endif