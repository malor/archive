#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "list_node.h"
#include "list_iterator.h"

template<class T>    
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    ListIterator<T> begin() const;
    ListIterator<T> end() const;

    void push_front(const T& elem);
    void push_back(const T& elem);

private:
    Node<T>* _head;
    Node<T>* _tail;
};

template<class T>    
LinkedList<T>::LinkedList()
    : _head(0), _tail(0)
{ }

template<class T>    
LinkedList<T>::~LinkedList()
{
    while (_head)
    {
        Node<T>* next = _head->next;
        delete _head;
        _head = next;
    }
}

template<class T>    
void LinkedList<T>::push_front(const T& elem)
{
    if (!_head)
    {
        _head = new Node<T>;
        _head->data = elem;
        _head->next = 0;

        _tail = _head;
    }
    else
    {
        Node<T>* oldfirst = _head;
        
        _head = new Node<T>;
        _head->data = elem;
        _head->next = oldfirst;
    }
}

template<class T>    
void LinkedList<T>::push_back(const T& elem)
{
    if (!_tail)
    {
        _tail = new Node<T>;
        _tail->data = elem;
        _tail->next = 0;

        _head = _tail;
    }
    else
    {
        Node<T>* oldlast = _tail;

        _tail = new Node<T>;
        _tail->data = elem;
        _tail->next = 0;

        oldlast->next = _tail;
    }
}

template<class T>    
ListIterator<T> LinkedList<T>::begin() const
{
    return ListIterator<T>(_head);
}

template<class T>    
ListIterator<T> LinkedList<T>::end() const
{
    return ListIterator<T>(0);
}

#endif /* __LINKED_LIST_H__ */
