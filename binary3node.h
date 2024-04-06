// binary3node.h
//all the h file header for the classes
#ifndef _BINARY3NODE_H_
#define _BINARY3NODE_H_

class Binary3Node {
private:
    Binary3Node* leftNode;
    Binary3Node* rightNode;
    char nodeData;
//used in other code 
public:
    Binary3Node();
    Binary3Node(char value);
    ~Binary3Node();
//and the chars dont forget firaol 
    void setData(char value);
    void setLeft(char value);
    void setRight(char value);
    void setRight(Binary3Node* node);
    void setLeft(Binary3Node* node);
    char getData();
    Binary3Node* getRight();
    Binary3Node* getLeft();
};

#endif

