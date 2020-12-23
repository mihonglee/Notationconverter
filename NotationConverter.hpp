#ifndef NOTATIONCONVERTER_HPP
#define NOTATIONCONVERTER_HPP

#include <algorithm> //To reverse a string

#include "NotationConverterInterface.hpp"
#include "DequeList.hpp"
#include "LinkedDeque.hpp"

class NotationConverter : public NotationConverterInterface {
public:
    //Default constructor and destructor
    NotationConverter() = default;
    ~NotationConverter() = default;
    void clear(); //helper function to clear the entire deque

    //postfix conversion functions
    virtual std::string postfixToInfix(std::string inStr);
    virtual std::string postfixToPrefix(std::string inStr);

    //infix conversion functions
    virtual std::string infixToPostfix(std::string inStr);
    virtual std::string infixToPrefix(std::string inStr);

    //prefix conversion functions
    virtual std::string prefixToInfix(std::string inStr);
    virtual std::string prefixToPostfix(std::string inStr);
private:
    LinkedDeque notation_deque; //Deque that we use to convert between notations
};

#endif /* NOTATIONCONVERTER_HPP */