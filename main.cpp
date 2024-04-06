/*
firaol berehanu 
3/20/2024
this is a shunting yard algrothim wich will take in exprision the print them out in variosu wasys
using the queue or stack 
Used algorithm from http://mathcenter.oxford.emory.edu/site/cs171/shuntingYardAlgorithm/
*/
#include <iostream>
#include "binary3node.h"
#include <map>
#include <cmath>

using namespace std;

class StackNode {
public:
    StackNode* next;
    Binary3Node* currentNode;

    StackNode(Binary3Node* temp);
};
//creating the ndoe 
StackNode::StackNode(Binary3Node* temp) {
    currentNode = temp;
    next = nullptr;
}
//moving it to next 
void push(Binary3Node* toPush, StackNode* &top) {
    if (top == nullptr) {
        top = new StackNode(toPush);
    } else {
        StackNode* ptr = new StackNode(toPush);
        ptr->next = top;
        top = ptr;
    }
}
//checking if there is sumthin
Binary3Node* peek(Binary3Node* top) {
    if (top != nullptr)
        return top;
    return nullptr;
}

Binary3Node* peek(StackNode* top) {
    if (top != nullptr)
        //need this to get postions 
        return top->currentNode;
    return nullptr;
}

Binary3Node* pop(StackNode* &top) {
    if (top == nullptr)
        //return to null for memory  
        return nullptr;

    Binary3Node* temp = top->currentNode;
    top = top->next;
    return temp;
}
//startsing from the back 
void enqueue(Binary3Node* toAdd, Binary3Node* &top, Binary3Node* &rear) {
    if (rear == nullptr) {
        rear = toAdd;
        top = rear;
        return;
    }
    rear->setRight(toAdd);
    rear = toAdd;
}

void dequeue(Binary3Node* &top, Binary3Node* &rear) {
    if (top == nullptr)
        return;

    Binary3Node* temp = top;
    top = top->getRight();

    if (top == nullptr)
        rear = nullptr;
    delete temp;
}

bool isOperator(char value) {
    return (value == '*' || value == '/' || value == '+' || value == '-' || value == '^');
}

bool isDigit(char value) {
    return (value >= '0' && value <= '9');
}
//checing for the type of oprater 
int apply(char a, char b, char op) {
    a -= '0';
    b -= '0';
    if (op == '+')
        return a + b;
    else if (op == '-')
        return a - b;
    else if (op == '*')
        return a * b;
    else if (op == '/')
        return a / b;
    else
        return (int)pow(a, b);
}
//infix 
void inorder(Binary3Node* node) {
    if (node == nullptr)
        return;
    inorder(node->getLeft());
    cout << node->getData() << " ";
    inorder(node->getRight());
}
//post fix
void postorder(Binary3Node* node) {
    if (node == nullptr)
        return;
    postorder(node->getLeft());
    postorder(node->getRight());
    cout << node->getData() << " ";
}
//prefix
void preorder(Binary3Node* node) {
    if (node == nullptr)
        return;
    cout << node->getData() << " ";
    preorder(node->getLeft());
    preorder(node->getRight());
}

int main() {
    //precedend the order in which they matter 
    map<char, int> precedence;
    precedence['^'] = 4;
    precedence['*'] = 3;
    precedence['/'] = 3;
    precedence['+'] = 2;
    precedence['-'] = 2;
//intatilze evryhting to null
    StackNode* stackTop = nullptr;
    StackNode* valueStack = nullptr;
    Binary3Node* outTop = nullptr;
    Binary3Node* outRear = nullptr;
    char temp;
    char expression[100];
    int index = 0;

    cout << "Please enter an expression in INFIX form" << endl;
    cin.getline(expression, 100, '\n');
//checks for some of the order
    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] == ' ')
            continue;
        temp = expression[i];
        if (isDigit(temp)) {
            enqueue(new Binary3Node(temp), outTop, outRear);
        } else if (temp == '(') {
            push(new Binary3Node(temp), stackTop);
        } else if (temp == ')') {
            //looking for a a cause to start or terminate   case with (
            while (peek(stackTop) != nullptr && peek(stackTop)->getData() != '(') {
                Binary3Node* op = pop(stackTop);
                enqueue(op, outTop, outRear);
            }
            //pop func to spit vars out  them back out 
            pop(stackTop);
        } else if (isOperator(temp) && (peek(stackTop) == nullptr || peek(stackTop)->getData() == '(')) {
            push(new Binary3Node(temp), stackTop);
        } else if (isOperator(temp) && precedence[temp] >= precedence[peek(stackTop)->getData()] && temp == '^') {
            push(new Binary3Node(temp), stackTop);
        } else if (isOperator(temp)) {
            while (peek(stackTop) != nullptr && precedence[temp] <= precedence[(peek(stackTop)->getData())] && temp != '^') {
                Binary3Node* op = pop(stackTop);
                enqueue(op, outTop, outRear);
            }
            push(new Binary3Node(temp), stackTop);
        }
    }
    while (stackTop != nullptr) {
        Binary3Node* op = pop(stackTop);
        enqueue(op, outTop, outRear);
    }

    StackNode* expressionTree = nullptr;
    Binary3Node* front = peek(outTop);
//when the front is finshed 
    while (front != nullptr) {
        //retrive the data 
        //will precident matter 
        if (front->getData() == '+' || front->getData() == '-' || front->getData() == '/' ||
            front->getData() == '*' || front->getData() == '^') {
            Binary3Node* temp = new Binary3Node(front->getData());
            Binary3Node* a = pop(expressionTree);
            Binary3Node* b = pop(expressionTree);
            //out them to stach or queeue or like the side
            temp->setRight(a);
            temp->setLeft(b);
            push(temp, expressionTree);
        } else {
            Binary3Node* temp = new Binary3Node(front->getData());
            push(temp, expressionTree);
        }
        dequeue(outTop, outRear);
        cout << front->getData();
        front = peek(outTop);
    }
    cout << endl;
//just callig all the fuction after asking the input 
    char userInput[10];
    while (true) {
        cout << "Enter PREFIX, INFIX, POSTFIX, or QUIT" << endl;
        cin >> userInput;
        if (!strcmp(userInput, "PREFIX")) {
            preorder(expressionTree->currentNode);
        } else if (!strcmp(userInput, "INFIX")) {
            inorder(expressionTree->currentNode);
        } else if (!strcmp(userInput, "POSTFIX")) {
            postorder(expressionTree->currentNode);
        } else if (!strcmp(userInput, "QUIT")) {
            break;
        }
        cout << endl;
    }

    return 0;
}

