#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

template <typename T>
class Heap {
private:
    std::vector<T> data;
    size_t heap_size = 0;
    size_t length = 0;

    size_t parent(const size_t& i) const {
        return i >> 1;
    }

    size_t left(const size_t& i) const {
        return i << 1;
    }

    size_t right(const size_t& i) const {
        return (i << 1) + 1;
    }

public:
    Heap<T>& max_heapify(size_t i) {
        size_t l = left(i);
        size_t r = right(i);
        size_t largest = i;
        if (l <= heap_size && data[l] > data[i])
            largest = l;
        else
            largest = i;
        if (r <= heap_size && data[r] > data[largest])
            largest = r;
        if (largest != i) {
            std::swap(data[i], data[largest]);
            max_heapify(largest);
        }
        return *this;
    }

    void insert(const T& elem) {
        data.push_back(elem);
        ++heap_size;
        length = heap_size;
        for (size_t i = length / 2; i != 0; --i) {
            max_heapify(i);
        }
    }

    Heap(const std::vector<T>& v) : data(v) {
        data.insert(data.begin(), T());
        heap_size = v.size();
        length = heap_size;
        for (size_t i = length / 2; i != 0; --i) {
            max_heapify(i);
        }
    }

    Heap<T>& heapsort() {
        for (size_t i = length; i != 1; --i) {
            std::swap(data[1], data[i]);
            --heap_size;
            max_heapify(1);
        }
        heap_size = data.size() - 1;
        return *this;
    }

    void print_heap() const {
        for (size_t i = 1; i <= heap_size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    void print_max() const {
        std::cout << data[1] << std::endl;
    }
};


int main() {
    size_t N;
    std::cin >> N;
    std::vector<int> numbers;
    numbers.reserve(N);
    for (int i = 0; i != N; ++i) {
        int x;
        std::cin >> x;
        numbers.push_back(x);
    }

    Heap<int> h(numbers);
    h.print_heap();
    h.insert(7);
    h.print_heap();
    h.heapsort();
    h.print_heap();

    Heap<int> h2({});
    h2.insert(4);
    h2.print_heap();
    h2.insert(2);
    h2.print_heap();
    h2.insert(8);
    h2.print_max();
    h2.heapsort();
    h2.print_heap();
    return 0;
}
