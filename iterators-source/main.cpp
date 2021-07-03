#include <iostream>

#include "linked_list.h"
#include "max_element4.h"

int main(int argc, char **argv)
{
    LinkedList<int> l;
    l.push_front(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(10);
    l.push_back(4);
    l.push_front(5);

    int arr[] = {1, 2, 3, 10, 4, 5};

    std::cout << "Max: " << *max_element(l.begin(), l.end()) << "\n";
    std::cout << "Max: " << *max_element(arr, arr + 6) << "\n";

    return 0;
}
