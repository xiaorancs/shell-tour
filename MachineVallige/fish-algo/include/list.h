/**
 * Author: xiaoran
 * Time: 2020-10-28 20:00
 * Email: xiaoranone@126.com
 */ 

#ifndef FISH_ALGO_INCLUDE_LIST_H
#define FISH_ALGO_INCLUDE_LIST_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

namespace fish {

template<class T>
struct ListNode { 
    T data; 
    ListNode<T> *next; 
    ListNode<T>() {}
    ListNode<T>(const T _data, const ListNode<T>* _next) : data(_data), next(_next) {}
}; 

template<class T>
struct DListNode { 
    T data; 
    DListNode<T> *next; 
    DListNode<T> *pre; 
    DListNode<T>() {}
    DListNode<T>(const T _data, const DListNode<T>* _pre, const DListNode<T>* _next) : 
        data(_data), next(_next), pre(_pre) {}
}; 


template<class T>
class List {
public:
    List () {
        agent_root = new ListNode<T>();
        root = agent_root;
        pre_agent_root = nullptr;
        _size = 0;
    }

    List(int size, const T& val) {
        agent_root = new ListNode<T>();
        root = agent_root;
        pre_agent_root = nullptr;
        _size = 0;
    }

    int size() {
        return _size;
    }

    void clear() {
        while (root && root->next) {
            ListNode<T>* tmp = root;
            root = root->next;
            delete tmp;
        }
        delete root;
    }

    bool empty() {
        return _size == 0;
    }

    void push_back(const T& val) {
        ListNode<T> *temp = new ListNode<T>(val, nullptr);
        agent_root->next = temp;
        pre_agent_root = agent_root;
        agent_root = agent_root->next;
        ++ _size;
    }

    void pop_back() {
        delete agent_root;
        pre_agent_root->next = NULL;
        agent_root = pre_agent_root;
    }

    void insert(int index, const T& val) {
        if (index >= _size) {
            push_back(val);
        }
        else if (index >= 1 && index < _size) {
            ListNode<T>* new_node = new ListNode<T>(val, nullptr);
            int i = 0;
            ListNode<T>* tmp_root = root;
            while (i < index) {
                tmp_root = tmp_root->next;
            }
            new_node->next = tmp_root->next;
            tmp_root->next = new_node;
        }
    }
    
    // 删除第index个节点
    void erase(int index) {
        assert(index >= 1 && index <= _size);
        int i = 0;
        ListNode<T>* tmp_root = root;
        while (i < index) {
            tmp_root = tmp_root->next;
        }
        ListNode<T>* tmp = tmp_root->next;
        tmp_root->next = tmp_root->next->next;
        delete tmp;
    }

    ListNode<T>* get_root() {
        return root->next;
    }

private:
    List(const List&);
    List& operator=(const List&);


private:
    int _size;
    ListNode<T>* root;
    // 执行头节点的指针为了便于操作
    ListNode<T>* agent_root;
    ListNode<T>* pre_agent_root;



};

template<class T>
class DoublyList {
public:

private:
    DoublyList(const DoublyList&);
    DoublyList& operator=(const DoublyList&);

private:


};


} // namespace fish

#endif // FISH_ALGO_INCLUDE_LIST_H