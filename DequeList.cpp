#include "DequeList.hpp"

//Constructor
DequeList::DequeList() {
    //allocating memory for sentinels
    header = new DequeListNode;
    trailer = new DequeListNode;
    //point sentinels to each other
    header->next = trailer;
    trailer->prev = header;
    size = 0; //initial size is 0
}

//Destructor
DequeList::~DequeList() {
    while (!emptyList()) {
        removeFront(); //Call removeFront() until the list is empty
    }
    //Manually delete the sentinels
    delete trailer;
    delete header;
}

//Helper function to add a new node to an empty list
void DequeList::emptyAdd(DequeListNode* new_part) {
    header->next = new_part;
    new_part->prev = header;
    new_part->next = trailer;
    trailer->prev = new_part;
}

//Add an element to the front of the list
void DequeList::addFront(const std::string& part) {
    DequeListNode* new_part = new DequeListNode; //allocating memory
    new_part->part = part;

    if (emptyList()) {
        emptyAdd(new_part); //Call helper function if the list is empty
    }
    else { //Slip the new element at the beginning
        auto next_node = header->next;
        header->next = new_part;
        new_part->prev = header;
        new_part->next = next_node;
        next_node->prev = new_part;
    }
}

//Add an element to the back of the list
void DequeList::addBack(const std::string& part) {
    DequeListNode* new_part = new DequeListNode; //Allocating memory
    new_part->part = part;
    if (emptyList()) {
        emptyAdd(new_part); //Call helper function if the list is empty
    }
    else { //Slip the new element at the back 
        auto prev_node = trailer->prev;
        trailer->prev = new_part;
        new_part->next = trailer;
        new_part->prev = prev_node;
        prev_node->next = new_part;
    }
}

//Remove element at beginning of the list
void DequeList::removeFront() {
    if (emptyList())
        throw("EmptyList"); //Cannot remove from empty list

    //Removing a node and changing list accordingly
    auto node_to_remove = header->next;
    auto next_node = node_to_remove->next;
    header->next = next_node;
    next_node->prev = header;

    delete node_to_remove; //delete the node
    size--; //decrement size
}

//Remove element at back of the list
void DequeList::removeBack() {
    if (emptyList())
        throw("EmptyList"); //Cannot remove from empty list

    //Removing the node and changing list accordingly
    auto node_to_remove = trailer->prev;
    auto prev_node = node_to_remove->prev;
    trailer->prev = prev_node;
    prev_node->next = trailer;

    delete node_to_remove; //delete the node
    size--; //decrement size
}