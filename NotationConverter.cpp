#include "NotationConverter.hpp"

//Free funciton that checks if a char is a letter
bool isCharLetter(const char& c) {
    bool islower = (c >= 'a' && c <= 'z');
    bool isupper = (c >= 'A' && c <= 'Z');
    bool isLetter = (islower || isupper);

    return isLetter;
}

//Free function to check if a char is an operator
bool isCharOp(const char& c) {
    bool isTimes = (c == '*');
    bool isAdd = (c == '+');
    bool isSub = (c == '-');
    bool isDivide = (c == '/');

    bool isOP = (isTimes || isAdd || isSub || isDivide);
    return isOP;
}

//Free function to return precedence of operator
int pemdas(char op) {
    switch (op) {
    case '*': //Multiplication and Division Highest Precedence
        return 2;
        break;
    case '/':
        return 2;
        break;
    case '+': //Addition and Subtraction Lowest Precedence
        return 1;
        break;
    case '-':
        return 1;
        break;
    default:
        return 0;
    }
}

//Helper function to clear the whole deque
void NotationConverter::clear() {
    while (!notation_deque.emptyDeque()) {
        notation_deque.removeFront();
    }
}

//Postfix Converters
std::string NotationConverter::postfixToInfix(std::string inStr) {
    std::string ret; //String to return
    for (auto c : inStr) { //Main loop to go through each char of input string
        if (c == ' ') { //ignore white spaces
            continue;
        }
        else if (isCharLetter(c)) { //when char is an operand
            std::string temp = "";
            temp += c; //append operand on string to insert into the deque
            notation_deque.insertFront(temp);
        }
        else if (isCharOp(c)) { //when char is an operator
            std::string temp = "";
            temp += ')'; //Add parenthesis for infix string
            temp += notation_deque.front(); //Add operand to infix string
            notation_deque.removeFront();
            temp += ' ';
            temp += c; //add operator to string
            temp += ' ';
            temp += notation_deque.front(); //Add operand to infix string
            notation_deque.removeFront();
            temp += '('; //Parenthesis for infix string
            notation_deque.insertFront(temp); //Insert entire infix string into the deque
            //NOTE: parenthesis are backwards becasue we reverse the string later
        }
        else {
            throw("InvalidString"); //if there is an invalid char we throw InvalidString
        }
    }
    while (!notation_deque.emptyDeque()) { //Until the deque is empty
        ret += notation_deque.front(); //Appending the strings held by the deck to the return string
        notation_deque.removeFront(); //Remove the element that was put into the return string
    }

    //Must reverse the return string to get proper infix string according to the input string
    //The elements are put into the deque backwards
    reverse(ret.begin(), ret.end());
    return ret;
}

std::string NotationConverter::postfixToPrefix(std::string inStr) {
    std::string ret = "";
    std::string temp = "";
    temp = postfixToInfix(inStr); //postfix -> infix
    ret = infixToPrefix(temp); //infix -> prefix
    return ret; //return prefix
}
//End of Postfix Converters

//Infix Converters
std::string NotationConverter::infixToPostfix(std::string inStr) {
    std::string ret;
    std::string endFlag = "end"; //end flag to denote the end of our deque 
    notation_deque.insertBack(endFlag); //only element of the deque at first is the end flag
    for (auto c : inStr) { //checking every char in the input string
        if (c == ' ') { //ignore white spaces
            continue;
        }
        else if (isCharLetter(c)) { //if char is operand
            ret += c; //append operand to the return string
            ret += ' ';
        }
        else if (c == '(') { //if char is a open parenthesis
            std::string temp = "";
            temp += c;
            notation_deque.insertFront(temp); //add this parenthesis to the front of the deque
        }
        else if (c == ')') { //if char is a closed parenthesis
            while (notation_deque.front() != endFlag && notation_deque.front() != "(") { //until our endflag is reached AND the front of the deque does not contain a (
                std::string temp = "";
                temp = notation_deque.front();
                notation_deque.removeFront();
                ret += temp; //Append the data at the front of the deque to the return string
                ret += ' ';
            }
            if (notation_deque.front() == "(") { //when the front of the deque contains a (
                notation_deque.removeFront(); //ignore and remove it
            }
        }
        else if (isCharOp(c)) { //if the char is a operator
            while (notation_deque.front() != endFlag && pemdas(c) <= pemdas(notation_deque.front().at(0))) { //while the endflag of the deque is not reached AND the precedence of the operator is less than the one at the front of the deque
                std::string temp = notation_deque.front();
                notation_deque.removeFront();
                ret += temp; //appending the front of the deque to the return string
                ret += ' ';
            }
            std::string strToInsert = "";
            strToInsert += c; //add the new operator to the front of the deque
            notation_deque.insertFront(strToInsert);
        }
        else {
            throw("InvalidString"); //Invalid char in input string
        }
    }

    while (notation_deque.front() != endFlag) { //Go through the entire deque
        std::string temp = "";
        temp = notation_deque.front();
        notation_deque.removeFront();
        ret += temp; //append the front of the deque to return string until the deque is empty
        ret += ' ';
    }

    clear(); //clears the elements of the deque (including the end flag)
    if (ret.at(0) == ' ') //Gets rid of unecessary white space at beginning of string
        ret.erase(ret.begin());
    if (ret.back() == ' ') //Gets rid of unecssary whtie space at end of string
        ret.erase(ret.end() - 1);
    return ret;
}

std::string NotationConverter::infixToPrefix(std::string inStr) {

    std::string ret = "";
    std::string temp = "";

    for (auto c : inStr) {
        //append every char of input string to a temporary string
        temp += c;
    }

    for (unsigned int i = 0; i < temp.length(); i++) { //checking every char of the temp string
        //replace the parenthesis for backwards for reversal later
        if (temp.at(i) == '(') {
            temp.at(i) = ')';
        }
        else if (temp.at(i) == ')') {
            temp.at(i) = '(';
        }
    }

    reverse(temp.begin(), temp.end()); //reverse string to send to infixToPostFix()
    ret = infixToPostfix(temp); //set return string to the postfix string
    reverse(ret.begin(), ret.end()); //reverse the postfix to retrieve the infix string

    clear(); //clears the elements of the deque (including the end flag used in infixToPostfix)
    if (ret.at(0) == ' ') //Gets rid of unecessary white space at beginning of string
        ret.erase(ret.begin());
    if (ret.back() == ' ') //Gets rid of unecssary whtie space at end of string
        ret.erase(ret.end() - 1);
    return ret;
}
//End of Postfix Converters

//Prefix Converters
std::string NotationConverter::prefixToInfix(std::string inStr) {
    std::string ret;
    reverse(inStr.begin(), inStr.end()); //reverse the string initally 
    for (auto c : inStr) { //checking every char in input string
        if (c == ' ') { //ignore white spaces
            continue;
        }
        else if (isCharLetter(c)) { //when char is operand
            std::string temp = "";
            temp += c; //insert operand to the back of the deque
            notation_deque.insertBack(temp);
        }
        else if (isCharOp(c)) { //when char is operator
            std::string temp = "";
            temp += '('; //append parenthesis
            temp += notation_deque.back(); //append operand
            notation_deque.removeBack();
            temp += ' ';
            temp += c; //append operator
            temp += ' ';
            temp += notation_deque.back(); //append operand
            notation_deque.removeBack();
            temp += ')'; //append parenthesis
            notation_deque.insertBack(temp); //insert the new string created back into the deque
        }
        else {
            throw("InvalidString"); //Invalid char in input string
        }
    }
    while (!notation_deque.emptyDeque()) { //until the deque is empty
        ret += notation_deque.back(); //appending the back of the deque to to the return string
        notation_deque.removeBack();
    }

    return ret;
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
    std::string ret = "";
    std::string temp = "";
    temp = prefixToInfix(inStr); //prefix -> infix
    ret = infixToPostfix(temp); //infix -> postfix
    return ret;
}
//End of Prefix  Converters