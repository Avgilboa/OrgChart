#include "Node.hpp"
using namespace std;
namespace ariel{
    Node::Node(const string & name){
        this->_name = name;
        this->next = nullptr;
        this->prev = nullptr;
        this->parent = nullptr;
        this->leftMostSon = nullptr;
        this->rightMostSon = nullptr;
        this->nextInIteration = nullptr;
    }

    void Node::add_child(string const &name){
        /* Makeing the new child and looking for 3 cases for the parent:
            1. There is no children to the parent
            2. there is one children to the parent
            3. there is more than 1 children
         */
            Node *new_child = new Node(name);
            new_child->parent = &*this;

            if (this->leftMostSon == nullptr) {
                this->leftMostSon = new_child;
            }
            else if(this->rightMostSon == nullptr) {
                this->rightMostSon = new_child;
                new_child->prev = this->leftMostSon;
                this->leftMostSon->next = new_child;
                return;

            }
            else{
                Node *currentRightMost = this->rightMostSon;
                this->rightMostSon = new_child;
                currentRightMost->next = new_child;
                new_child->prev = currentRightMost;
            }
    }
    string & Node::getName(){
        return this->_name;
    }
}