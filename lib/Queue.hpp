#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <stdexcept>

// ĐỊNH NGHĨA NODE CỦA QUEUE
template <typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;

    QueueNode(T val) {
        data = val;
        next = nullptr;
    }
};

// KHAI BÁO VÀ ĐỊNH NGHĨA QUEUE
template <typename T>
struct Queue {
    QueueNode<T>* frontNode;  // Con trỏ quản lý phần tử ở đầu hàng đợi
    QueueNode<T>* backNode;   // Con trỏ quản lý phần tử ở cuối hàng đợi
    int count;                // Đếm số lượng phần tử trong hàng đợi

    Queue() {
        frontNode = nullptr;
        backNode = nullptr;
        count = 0;
    }

    // Tự động được gọi khi hàng đợi bị hủy để tránh rò rỉ bộ nhớ
    ~Queue() {
        clear();
    }

    /*
     * Thêm một phần tử vào cuối hàng đợi
     * Input: Giá trị val cần thêm vào
     */
    void enqueue(const T& val) {
        QueueNode<T>* newNode = new QueueNode<T>(val);
        if (empty()) {
            frontNode = backNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
        count++;
    }

    // Xóa phần tử nằm ở đầu hàng đợi
    void dequeue() {
        if (empty()) {
            return;
        }
        QueueNode<T>* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;
        temp = nullptr;
        count--;
        // Nếu hàng đợi đã rỗng thì cập nhật lại backNode
        if (!frontNode) {
            backNode = nullptr;
        }
    }

    // Lấy giá trị của phần tử nằm ở đầu hàng đợi
    T front() const {
        if (empty()) {
            throw std::out_of_range("Hàng đợi rỗng, không có phần tử ở đầu!");
        }
        return frontNode->data;
    }

    // Lấy giá trị của phần tử nằm ở cuối hàng đợi
    T back() const {
        if (empty()) {
            throw std::out_of_range("Hàng đợi rỗng, không có phần tử ở cuối!");
        }
        return backNode->data;
    }

    /*
     * Kiểm tra xem hàng đợi có rỗng hay không
     * Output: Trả về true nếu rỗng, false nếu không rỗng
     */
    bool empty() const {
        return count == 0;
    }

    // Lấy số lượng phần tử trong hàng đợi
    int size() const {
        return count;
    }

    // Xóa toàn bộ các phần tử trong hàng đợi và giải phóng bộ nhớ
    void clear() {
        QueueNode<T>* current = frontNode;
        while (current) {
            QueueNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        frontNode = nullptr;
        backNode = nullptr;
        count = 0;
    }
};

#endif