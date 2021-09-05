#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include "Hand.h"

//First task
class myIntVector
{
private:
    int _capacity;
    int* _data;

    void _realloc(int capacity) {
        if (capacity == _capacity)
            return;
        if (capacity <= 0) {
            erase();
            return;
        }
        int* data = new int[capacity];
        if (_capacity > 0) {
            int elementsToCopy = (capacity > _capacity) ? _capacity : capacity;
            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = _data[index];
        }
        delete[] _data;
        _data = data;
        _capacity = capacity;
    };
//Quick sort
    void _quickSort(int* data, int end) {
        int _begin = 0, _end = end - 1;
        int _pivot = data[(end) / 2];

        do {

            while (data[_begin] < _pivot)
                _begin++;

            while (data[_end] > _pivot)
                _end--;

            if (_begin <= _end) {
                int changeInt = data[_begin];
                data[_begin] = data[_end];
                data[_end] = changeInt;
                _begin++;
                _end--;
            }
        } while (_begin <= _end);

        if (_end > 0)
            _quickSort(data, _end + 1);

        if (_begin < end)
            _quickSort(&data[_begin], end - _begin);
    };
//Quick sort

public:
    myIntVector() : _capacity(0), _data(nullptr) {};
    myIntVector(int capacity) : _capacity(capacity) {
        assert(_capacity >= 0);
        if (_capacity > 0)
            _data = new int[_capacity];
        else
            _data = nullptr;
    };

    ~myIntVector() {
        delete[] _data;
    };

    void erase() {
        delete[] _data;
        _data = nullptr;
        _capacity = 0;
    };

    int capacity() { return _capacity; };

    int& operator[](int index) {
        assert(index >= 0 && index < _capacity);
        return _data[index];
    };

    void reserve(int newLength) {
        _realloc(newLength);
    };

    bool pop_back() {
        if (_capacity == 0)
            return false;
        _data[--_capacity] = 0;
        return true;
    };

    bool pop_front() {
        if (_capacity == 0)
            return false;
        for (int index = 1; index < _capacity; ++index)
            _data[index - 1] = _data[index];
        --_capacity;
        return true;
    };

    void bubbleSort() {
        bool _sort = true;
        while (_sort) {
            _sort = false;
            for (int i = 1; i < _capacity; ++i) {
                if (_data[i] < _data[i - 1]) {
                    int changeInt = _data[i];
                    _data[i] = _data[i-1];
                    _data[i-1] = changeInt;
                    _sort = true;
                }
            }
        }
    };
    
    void quickSort() {
        _quickSort(_data, _capacity);
    };

    void print() {
        std::cout << "( ";
        for (int i = 0; i < _capacity; ++i) {
            std::cout << std::to_string(_data[i]) + " ";
        }
        std::cout << ")" << std::endl;
    };
};
//Fist task

//Second task
int findDifferentCountUnorderedSet(const std::vector<int>& data)
{
    std::unordered_set<int> s;
    for (int i : data)
        s.insert(i);
    return s.size();
}

int findDifferentSortErase(const std::vector<int>& data) {
    std::vector<int> copy = data;
    std::sort(copy.begin(), copy.end());
    copy.erase(std::unique(copy.begin(), copy.end()), copy.end());
    return copy.size();
}
//Second task

void FirstTask() {
    myIntVector vecInt;
    vecInt.reserve(5);
    vecInt[0] = 21;
    vecInt[1] = 1;
    vecInt[2] = 8;
    vecInt[3] = 19;
    vecInt[4] = 14;
    vecInt.print();
    //vecInt.bubbleSort(); //bubble sort
    vecInt.quickSort(); //quick sort
    vecInt.print();
};

void SecondTask(const int numElements) {
    std::vector<int> toCheck;
    toCheck.reserve(numElements);
    for (int i = 0; i < numElements; i++)
    {
        toCheck.push_back(std::rand());
    }
    auto sortEraseStart = std::chrono::high_resolution_clock::now();
    int foundAmountSortErase = findDifferentSortErase(toCheck);
    auto sortEraseStop = std::chrono::high_resolution_clock::now();
    std::cout << "Found elements: " << foundAmountSortErase << " from " << toCheck.size() << std::endl;
    std::cout << "Sort/erase algo: " << std::chrono::duration_cast<std::chrono::milliseconds>(sortEraseStop - sortEraseStart).count() << " ms.(int.)" << std::endl;

    auto unorderedSetStart = std::chrono::high_resolution_clock::now();
    int foundAmountUnorderedSet = findDifferentCountUnorderedSet(toCheck);
    auto unorderedSetEnd = std::chrono::high_resolution_clock::now();
    std::cout << "Found elements: " << foundAmountUnorderedSet << " from " << toCheck.size() << std::endl;
    std::cout << "Unordered set algo: " << std::chrono::duration_cast<std::chrono::milliseconds>(unorderedSetEnd - unorderedSetStart).count() << " ms.(int.)" << std::endl;
};

int main() {    
    FirstTask();
    SecondTask(1000000); 
    
    //Speed fo second task depends on numElements amount.
    //For small amount common sort/erase is working faster, but for huge amount unordered_set is much faster  
}

