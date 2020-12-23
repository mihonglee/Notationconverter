#include "DequeList.hpp"

class LinkedDeque {
public:
    LinkedDeque();
    ~LinkedDeque() = default;

    int getSize() const { return size; }
    bool emptyDeque() { return list.emptyList(); } //Uses the list to check if the list is empty
    std::string front(); //returns the front of the deque
    std::string back(); //returns the back of the deque

    void insertFront(const std::string& part); //Insert element at front of deque
    void insertBack(const std::string& part); //Insert element at back of deque
    void removeFront(); //remove first element of the deque
    void removeBack(); //remove last element of the deque
private:
    int size; //num of elements in the deque
    DequeList list; //list used to implement the deque
    friend class DequeList;
};
