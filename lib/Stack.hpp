#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <stdexcept>

// ĐỊNH NGHĨA NODE CỦA STACK
template <typename T>
struct StackNode {
    T data;
    StackNode<T>* next;

    StackNode(T val) {
        data = val;
        next = nullptr;
    }
};

// KHAI BÁO VÀ ĐỊNH NGHĨA STACK
template <typename T>
struct Stack {
    StackNode<T>* topNode;  // Con trỏ quản lý phần tử trên cùng của ngăn xếp
    int count;              // Đếm số lượng phần tử trong ngăn xếp

    Stack() {
        topNode = nullptr;
        count = 0;
    }

    // Tự động được gọi khi ngăn xếp bị hủy để tránh rò rỉ bộ nhớ
    ~Stack() {
        clear();
    }

    /*
     * Thêm một phần tử vào đỉnh ngăn xếp
     * Input: Giá trị val cần thêm vào
     */
    void push(const T& val) {
        StackNode<T>* newNode = new StackNode<T>(val);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    // Xóa phần tử nằm ở đỉnh ngăn xếp
    void pop() {
        if (empty()) {
            return;
        }
        StackNode<T>* temp = topNode;
        topNode = topNode->next;
        delete temp;
        temp = nullptr;
        count--;
    }

    // Lấy giá trị của phần tử nằm trên đỉnh ngăn xếp
    T top() const {
        if (empty()) {
            throw std::out_of_range("Ngăn xếp rỗng, không có phần tử ở đầu!");
        }
        return topNode->data;
    }

    /*
     * Kiểm tra xem ngăn xếp có rỗng hay không
     * Output: Trả về true nếu ngăn xếp rỗng, false nếu không rỗng
     */
    bool empty() const {
        return count == 0;
    }

    // Lấy số lượng phần tử trong ngăn xếp
    int size() const {
        return count;
    }

    // Xóa toàn bộ các phần tử trong ngăn xếp và giải phóng bộ nhớ
    void clear() {
        StackNode<T>* current = topNode;
        while (current) {
            StackNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        topNode = nullptr;
        count = 0;
    }
};

#endif