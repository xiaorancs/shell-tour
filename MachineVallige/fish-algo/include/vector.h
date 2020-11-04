/**
 * Author: xiaoran
 * Time: 2020-10-28 20:00
 * Email: xiaoranone@126.com
 */ 

#ifndef FISH_ALGO_INCLUDE_VECTOR_H
#define FISH_ALGO_INCLUDE_VECTOR_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

namespace fish {
const uint32_t XSIZE = 1024;

template<class T, uint32_t xsize=XSIZE>
class Vector {
public:
    Vector() {
        this->_capacity = xsize;
        this->_size = 0;
        this->_data = new T[xsize + 1];
    }

    Vector(uint32_t n, const T& val) {
        this->_capacity = xsize;
        this->_size = n;
        this->_data = new T[xsize + 1];
        for (int i = 0; i < _size; i ++) {
            _data[i] = val;
        }
    }

    ~Vector() {
        delete []_data;
    }

private:
    Vector(const Vector&);
    Vector& operator=(const Vector&);

public:
    const uint32_t size() {
        return _size;
    }

    const uint32_t capacity() {
        return _capacity;
    }
    
    const bool empty() {
        bool is_empty = false;
        if (_size == 0) is_empty = true;
        return is_empty;
    }

    T& operator[](uint32_t _n) {
        return *(_data + _n);
    }

    T& at(uint32_t _n) {
        assert(_n < _size);
        return (*this)[_n];
    }

    T& front() {
        assert(_size > 0);
        return _data[0];
    }

    T& back() {
        assert(_size > 0);
        return _data[_size - 1];
    }

    T* data() {
        return _data;
    }

    void assign(const Vector& origin, uint32_t start, uint32_t end) {
        if (end - start > 2 * capacity()) {
            _capacity <<= 1;
            T* new_data = new T[_capacity];
            delete []_data;
            _data = new_data;
            _size = 0;
        }
        for (uint32_t i = start; i < end; i++) {
            _data[_size ++] = origin[i];
        }
    }

    void assign(uint32_t n, const T& val) {
        _size = 0;
        for (uint32_t i = 0; i < n; i++) {
            _data[_size ++] = val;
        }
    }

    inline void push_back(const T& val) {
        if (_size * 2 > _capacity) {
            _capacity <<= 1;
            T* new_data = new T[_capacity];
            memcpy(new_data, _data, _size);
            delete []_data;
            _data = new_data;
        }
        _data[_size ++] = val;
    }

    inline const T& pop_back() {
        assert(_size > 0);
        _size --;
        return _data[_size];
    }

    void insert(uint32_t n, const T& val) {
        assert(n > 0 && n <= _size);
        for (uint32_t i = n - 1; i < _size; i++) {
            _data[i + 1] = _data[i];
        }
        _data[n - 1] = val;
        ++ _size;
    }

    void erase_first(const T& val) {
        uint32_t k = 0;
        bool flag = false;
        for (uint32_t i = 0; i < _size; i++) {
            if (!flag && val == _data[i]) {
                flag = true;
                continue;
            }
            else {
                _data[k ++] = _data[i];
            }
        }
        _size = k;
    }   

    void erase_last(const T& val) {
        int index = _size - 1;
        for (index = _size - 1; index >= 0 && _data[index] != val; index--);
        if (index >= 0) {
            for (int i = index; i < _size; i++) {
                _data[i] = _data[i + 1];
            }
            -- _size ;
        }
    } 

    void erase_all(const T& val) {
        uint32_t k = 0;
        for (uint32_t i = 0; i < _size; i++) {
            if (val == _data[i]) {
                continue;
            }
            else {
                _data[k ++] = _data[i];
            }
        }
        _size = k;
    }

    void clear() {
        delete []_data;
    }

    void swap(Vector& dist) {
        T* tmp_data = _data;
        _data = dist._data;
        dist._data = tmp_data;

        uint32_t tmp_size = _size;
        _size = dist.size();
        dist._size = tmp_size;

        uint32_t tmp_cap = _capacity;
        _capacity = dist._capacity;
        dist._capacity = tmp_cap;
    }

private:
    T* _data;
    uint32_t _size;
    uint32_t _capacity;
};

} // namespace fish

#endif // FISH_ALGO_INCLUDE_VECTOR_H