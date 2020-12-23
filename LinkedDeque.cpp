#include "LinkedDeque.hpp"

//Constructor
LinkedDeque::LinkedDeque() {
    size = 0; //set initial size to 0
}

//Return the first element of the list
std::string LinkedDeque::front() {
    if (emptyDeque())
        throw("EmptyDeque");  //No elements if list is empty
    return list.front(); //Uses list to retrieve first element
}

//Return the last element of the list
std::string LinkedDeque::back() {
    if (emptyDeque())
        throw("EmptyDeque"); //No elements if list is empty
    return list.back(); //Uses list to retrieve the last element
}

//Inserting a element to the front
void LinkedDeque::insertFront(const std::string& part) {
    list.addFront(part); //uses list to insert the new element
    size++; //increment size
}

//Inserting element to the back
void LinkedDeque::insertBack(const std::string& part) {
    list.addBack(part); //uses list to insert the new element
    size++; //increment size
}

//Remove First element of the Deque
void LinkedDeque::removeFront() {
    if (emptyDeque())
        throw("EmptyDeque"); //Cannot remove from empty deque
    list.removeFront(); //uses list to remove first element
    size--; //decrements size
}

//Remove Last element of the Deque
void LinkedDeque::removeBack() {
    if (emptyDeque())
        throw("EmptyDeque"); //Cannot remove from empty deque
    list.removeBack(); //uses list to remove last element
    size--; //decrement size
}