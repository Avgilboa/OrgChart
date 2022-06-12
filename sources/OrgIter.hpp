#pragma once
#include "Node.hpp"
#include <stack>
#include <queue>
namespace ariel{
class OrgIter
{
    private:
        Node * currNode;
    public:
        OrgIter(Node* BeginIter){
            currNode = BeginIter;
        }
        OrgIter operator++(int){
            OrgIter temp = *this;
            this->currNode = currNode->next;
            return temp;
        }
        OrgIter& operator++(){
            currNode = currNode->next;
            return *this;
        }

        std::string& operator*() const{
            return currNode->_name;
        }
        std::string* operator->() const{
            return &(currNode->_name);
        }

        bool operator==(const OrgIter& other){
            return currNode == other.currNode;
        }

        bool operator!=(const OrgIter& other){
            return currNode != other.currNode;
        }

};
}