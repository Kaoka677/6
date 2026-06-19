#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <functional>

namespace Algorithms {

    // Hàm hỗ trợ hoán đổi giá trị giữa 2 biến có cùng kiểu dữ liệu
    template <typename T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    /*
     * Thuật toán Bubble Sort (Sắp xếp nổi bọt)
     * Độ phức tạp thời gian: O(n^2)
     */
    template <typename T, typename Comp = std::less<T>>
    void bubbleSort(T arr[], int n, Comp cmp = Comp()) {
        for (int i = 1; i <= n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i; j++) {
                if (cmp(arr[j + 1], arr[j])) {
                    Algorithms::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) {
                break; // Dừng sớm nếu mảng đã được sắp xếp hoàn toàn
            }
        }
    }

    /*
     * Thuật toán Selection Sort (Sắp xếp chọn)
     * Độ phức tạp thời gian: O(n^2)
     */
    template <typename T, typename Comp = std::less<T>>
    void selectionSort(T arr[], int n, Comp cmp = Comp()) {
        for (int i = 0; i < n; i++) {
            int minIndex = i;
            for (int j = i; j < n; j++) {
                if (cmp(arr[j], arr[minIndex])) {
                    minIndex = j;
                }
            }
            Algorithms::swap(arr[i], arr[minIndex]);
        }
    }

    /*
     * Thuật toán Insertion Sort (Sắp xếp chèn)
     * Độ phức tạp thời gian: O(n^2)
     */
    template <typename T, typename Comp = std::less<T>>
    void insertionSort(T arr[], int n, Comp cmp = Comp()) {
        for (int i = 1; i < n; i++) {
            int j = i;
            while (j > 0 && cmp(arr[j], arr[j - 1])) {
                Algorithms::swap(arr[j - 1], arr[j]);
                j--;
            }
        }
    }

    // Duy trì tính chất Max Heap cho cây con có gốc tại id (id là chỉ số trong mảng arr)
    template <typename T, typename Comp>
    void heapify(T arr[], int n, int id, Comp cmp) {
        int left = 2 * id + 1;
        int right = 2 * id + 2;
        int maxId = id;
        if (left < n && cmp(arr[maxId], arr[left])) {
            maxId = left;
        }
        if (right < n && cmp(arr[maxId], arr[right])) {
            maxId = right;
        }
        if (maxId != id) {
            Algorithms::swap(arr[id], arr[maxId]);
            heapify(arr, n, maxId, cmp);
        }
    }

    /*
     * Thuật toán Heap Sort (Sắp xếp vun đống)
     * Độ phức tạp thời gian: O(nlogn)
     */
    template <typename T, typename Comp = std::less<T>>
    void heapSort(T arr[], int n, Comp cmp = Comp()) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i, cmp);
        }
        // Liên tục đưa phần tử lớn nhất về cuối mảng và vun đống lại
        for (int i = n - 1; i >= 1; i--) {
            Algorithms::swap(arr[0], arr[i]);
            heapify(arr, i, 0, cmp);
        }
    }

    /*
     * Thuật toán Quick Sort (Sắp xếp nhanh)
     * Độ phức tạp thời gian trung bình: O(nlogn)
     * Độ phức tạp thời gian xấu nhất: O(n^2)
     */
    template <typename T, typename Comp = std::less<T>>
    void quickSort(T arr[], int lo, int hi, Comp cmp = Comp()) {
        if (lo >= hi) {
            return;
        }
        T pivot = arr[lo + (hi - lo) / 2];
        int i = lo;
        for (int j = lo; j <= hi; j++) {
            if (cmp(arr[j], pivot)) {
                Algorithms::swap(arr[i++], arr[j]);
            }
        }
        int mid1 = i - 1;
        for (int j = lo; j <= hi; j++) {
            if (!cmp(arr[j], pivot) && !cmp(pivot, arr[j])) {
                Algorithms::swap(arr[i++], arr[j]);
            }
        }
        int mid2 = i;
        quickSort(arr, lo, mid1, cmp);
        quickSort(arr, mid2, hi, cmp);
    }

    // Hàm hỗ trợ đệ quy cho thuật toán Merge Sort (Sắp xếp trộn), dùng mảng phụ temp để gộp
    template <typename T, typename Comp>
    void mergeSortHelper(T arr[], T temp[], int lo, int hi, Comp cmp) {
        if (lo >= hi) {
            return;
        }
        int mid = (lo + hi) / 2;
        mergeSortHelper(arr, temp, lo, mid, cmp);
        mergeSortHelper(arr, temp, mid + 1, hi, cmp);
        int i = lo;
        int j = mid + 1;
        int k = lo;
        while (i <= mid && j <= hi) {
            if (!cmp(arr[j], arr[i])) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) {
            temp[k++] = arr[i++];
        }
        while (j <= hi) {
            temp[k++] = arr[j++];
        }
        for (int idx = lo; idx <= hi; idx++) {
            arr[idx] = temp[idx];
        }
    }

    /*
     * Thuật toán Merge Sort (Sắp xếp trộn)
     * Độ phức tạp thời gian: O(nlogn)
     */
    template <typename T, typename Comp = std::less<T>>
    void mergeSort(T arr[], int n, Comp cmp = Comp()) {
        T* temp = new T[n];
        mergeSortHelper(arr, temp, 0, n - 1, cmp);
        delete []temp;
        temp = nullptr;
    }

    /*
     * Thuật toán Linear Search (Tìm kiếm tuyến tính)
     * Duyệt qua từng phần tử của mảng để tìm giá trị khớp với giá trị key
     */
    template <typename T>
    int linearSearch(const T arr[], int n, const T& key) {
        for (int i = 0; i < n; i++) {
            if (arr[i] == key) {
                return i;
            }
        }
        return -1; // Nếu không tìm thấy
    }

    /*
     * Thuật toán Binary Search (Tìm kiếm nhị phân)
     * Chia đôi mảng liên tục để tìm giá trị khớp với giá trị key
     * Yêu cầu mảng đã được sắp xếp sẵn
     */
    template <typename T, typename Comp = std::less<T>>
    int binarySearch(const T arr[], int n, const T& key, Comp cmp = Comp()) {
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (!cmp(arr[mid], key) && !cmp(key, arr[mid])) {
                return mid;
            } else if (cmp(arr[mid], key)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1; // Nếu không tìm thấy
    }
}

#endif