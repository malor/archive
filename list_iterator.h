#ifndef __LIST_ITERATOR_H__
#define __LIST_ITERATOR_H__

template<class T>
class ListIterator
{
public:
    ListIterator(Node<T>* node);

    const Node<T>* node() const;

    ListIterator<T>& operator++();
    const T& operator*() const;
    bool operator!=(const ListIterator<T>& it) const;

private:
    Node<T>* _currentNode;
};

template<class T>
ListIterator<T>::ListIterator(Node<T>* node)
    : _currentNode(node)
{ }

template<class T>
const Node<T>* ListIterator<T>::node() const
{
    return _currentNode;
}

template<class T>
ListIterator<T>& ListIterator<T>::operator++()
{
    _currentNode = _currentNode->next;
    return *this;
}

template<class T>
const T& ListIterator<T>::operator*() const
{
    return _currentNode->data;
}

template<class T>
bool ListIterator<T>::operator!=(const ListIterator<T>& it) const
{
    return _currentNode != it.node();
}

#endif /* __LIST_ITERATOR_H__ */
