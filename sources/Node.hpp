#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief : this is a node class its contain the name of the employee and pointers.
 * 
 */
namespace ariel {
    class Node {
    public:
        std::string _name;
        Node *next;
        Node *prev;
        Node *parent;
        Node *leftMostSon;
        Node *rightMostSon;
        Node *nextInIteration;

        Node(const std::string &_name);
        /// make the new node when all the pointers are zeros an

        void add_child(std::string const &sonName);
        // this function add employy to the chart and updated the pointers

        std::string & getName();
        // Node* next();
        // Node* prev();
        // Node* parent();

    };
}