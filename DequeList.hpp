#ifndef DEQUELIST_HPP
#define DEQUELIST_HPP

#include <string>

class DequeListNode {
public:
    //using default constructor and destructor
    DequeListNode() = default;
    ~DequeListNode() = default;
private:
    std::string part; //data that the node will hold
    DequeListNode* prev; //pointer to the previous DequeListNode
    DequeListNode* next; //pointer to the next DequeListNode
    friend class DequeList; //allow friend class access to DequeList
};

class DequeList {
public:
    DequeList();
    ~DequeList();
    std::string front() const { return header->next->part; } //returns the string held at the first element of the linked list
    std::string back() const { return trailer->prev->part; } //returns the string held at the last element of the linked list
    void emptyAdd(DequeListNode* new_part); //Helper function to add a new element to an empty list
    bool emptyList() { return (header->next == trailer); } //checks if the list is empty


    void addFront(const std::string& part);
    void addBack(const std::string& part);
    void removeFront();
    void removeBack();
private:
    unsigned int size; //keeps track of how many elements are in the list
    //sentinels of list
    DequeListNode* header;
    DequeListNode* trailer;
};

#endif /* DEQUELIST_HPP */
