#ifndef __LIST_NODE_H__
#define __LIST_NODE_H__

template<class T>    
struct Node
{
    T data;
    Node<T>* next;
};

#endif /* __LIST_NODE_H__ */
