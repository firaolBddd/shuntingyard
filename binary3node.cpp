// binary3node.cpp

#include "binary3node.h"

#define NULL 0
//seting everything to null c++
Binary3Node::Binary3Node() {
    leftNode = NULL;
    rightNode = NULL;
    nodeData = '\0';
}
//added the char 
Binary3Node::Binary3Node(char value) {
    leftNode = NULL;
    rightNode = NULL;
    nodeData = value;
}

Binary3Node::~Binary3Node() {}

void Binary3Node::setData(char value) {
    nodeData = value;
}
//setting left 
void Binary3Node::setLeft(char value) {
    if (leftNode == NULL)
        leftNode = new Binary3Node(value);
    else
        leftNode->setData(value);
}
//seting up  the right 
void Binary3Node::setRight(char value) {
    if (rightNode == NULL)
        rightNode = new Binary3Node(value);
    else
        rightNode->setData(value);
}
//using the binart node pointer 
void Binary3Node::setRight(Binary3Node* node) {
    rightNode = node;
}

void Binary3Node::setLeft(Binary3Node* node) {
    leftNode = node;
}
//data collection
char Binary3Node::getData() {
    return nodeData;
}

Binary3Node* Binary3Node::getRight() {
    return rightNode;
}

Binary3Node* Binary3Node::getLeft() {
    return leftNode;
}

