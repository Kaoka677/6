#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <iostream>
#include <stdexcept>

// ĐỊNH NGHĨA NODE CỦA PRIORITY QUEUE
template <typename T>
struct PriorityQueueNode {
    T data;
    int priority;    // Chỉ số ưu tiên
    PriorityQueueNode<T>* next;

    PriorityQueueNode(T val, int p) {
        data = val;
        priority = p;
        next = nullptr;
    }
};

// KHAI BÁO VÀ ĐỊNH NGHĨA PRIORITY QUEUE
template <typename T>
struct PriorityQueue {
    PriorityQueueNode<T>* frontNode;  // Con trỏ quản lý phần tử ở đầu hàng đợi ưu tiên
    int count;                        // Đếm số lượng phần tử trong hàng đợi ưu tiên

    PriorityQueue() {
        frontNode = nullptr;
        count = 0;
    }

    // Tự động được gọi khi hàng đợi ưu tiên bị hủy để tránh rò rỉ bộ nhớ
    ~PriorityQueue() {
        clear();
    }

    /*
     * Thêm phần tử vào hàng đợi ưu tiên dựa trên chỉ số ưu tiên
     * Nếu có cùng mức ưu tiên, phần tử nào đến trước sẽ đứng trước trong hàng đợi
     * Input: Giá trị val cần thêm vào và chỉ số ưu tiên p (p càng lớn, mức ưu tiên càng cao)
     */
    void insert(const T& val, int p) {
        PriorityQueueNode<T>* newNode = new PriorityQueueNode<T>(val, p);
        if (empty() || frontNode->priority < p) {
            newNode->next = frontNode;
            frontNode = newNode;
        } else {
            PriorityQueueNode<T>* current = frontNode;
            while (current->next && current->next->priority >= p) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        count++;
    }

    // Xóa phần tử nằm ở đầu trong hàng đợi ưu tiên
    void extract() {
        if (empty()) {
            return;
        }
        PriorityQueueNode<T>* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;
        temp = nullptr;
        count--;
    }

    // Lấy giá trị của phần tử nằm ở đầu trong hàng đợi ưu tiên
    T peek() const {
        if (empty()) {
            throw std::out_of_range("Hàng đợi ưu tiên rỗng, không có phần tử ở đầu!");
        }
        return frontNode->data;
    }

    /*
     * Kiểm tra xem hàng đợi ưu tiên có rỗng hay không
     * Output: Trả về true nếu hàng đợi rỗng, false nếu không rỗng
     */
    bool empty() const {
        return count == 0;
    }

    // Lấy số lượng phần tử có trong hàng đợi ưu tiên
    int size() const {
        return count;
    }

    // Xóa toàn bộ các phần tử trong hàng đợi ưu tiên và giải phóng bộ nhớ
    void clear() {
        PriorityQueueNode<T>* current = frontNode;
        while (current) {
            PriorityQueueNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        frontNode = nullptr;
        count = 0;
    }
};

#endif