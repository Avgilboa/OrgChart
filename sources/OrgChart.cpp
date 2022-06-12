#include "OrgChart.hpp"
#include <vector>

using namespace std;
namespace ariel {
    vector<string> invalidArguments = {"\n", "\t", "\r", "", " "};

    /// defult constructor --> null every node;
    OrgChart::OrgChart() {
        this->_root = nullptr;
        this->curr_iter = nullptr;
    }
    // copy constractor   --> need to copy all the pointers on the "other chart"
    OrgChart::OrgChart(OrgChart &other) {
        /* 
            saving the other nodes on the queue and using the pointer to refidinition the pointers of the 
            new Tree.
        */
        if (other._root != nullptr) {
            queue<Node *> q;
            q.push(other._root);
            this->_root = new Node(other._root->_name);
            this->curr_iter = nullptr;
            while (!q.empty()) {
                ///iterate all the nodes and add them to the queue
                Node *p_curr_Node = q.front();
                q.pop();
                Node *pt_Child = p_curr_Node->leftMostSon;
                ///add the left (first) of the children in the order
                while (pt_Child != nullptr) {
                    // add all of the node children to the queue 
                    q.push(pt_Child);
                    this->add_sub(p_curr_Node->_name, pt_Child->_name);
                    pt_Child = pt_Child->next;
                }
            }
        }
        // if the other == null
        else{this->_root = nullptr;
             this->curr_iter = nullptr;}
}


    OrgChart::~OrgChart() {
        this->del_nodes();
    }


    /// orginized all the pointers on a queu and remove them
    void OrgChart::del_nodes() {
        if(this->_root != nullptr){
            queue<Node*> q;
            q.push(this->_root);
            while (!q.empty()) {
                Node *currentNode = q.front();
                q.pop();
                Node *currentLeftMostSon = currentNode->leftMostSon;
                /* saving the first child, we will iter all over them and add them to the queue */
                while (currentLeftMostSon != nullptr) {
                    q.push(currentLeftMostSon);
                    currentLeftMostSon = currentLeftMostSon->next;
                }
                /*delete the node after adding all his childrens */
                delete currentNode; 
            
            }
        }
    }

    OrgChart &OrgChart::add_root(const string & name) {
        check_name(name);
        /* checking if the name is ok.
        if there is no root we will add new one
        if there is: we will change his name */
        if(this->_root == nullptr) {
            this->_root = new Node(name);
            return *this;
        }
        this->_root->_name = name;
        return *this;
    }

    OrgChart &OrgChart::add_sub(const string& __parent, const string& __child) {
        /* 
        check if the child name is free and the root is exist.
        adding the child to the end of his childrens
        */
        exist_root();
        check_name(__child);

        Node *parent = getSuperior(__parent);
        parent->add_child(__child);
        return *this;
    }

    Node *OrgChart::getSuperior(const string &superiorName) {
        queue<Node *> queue;
        queue.push(this->_root);
        while (!queue.empty()) {
            Node *currentNode = queue.front();
            queue.pop();
            if (currentNode->_name == superiorName) {
                return currentNode;
            }
            Node *currentLeftMostSon = currentNode->leftMostSon;
            if (currentLeftMostSon == nullptr) {
                continue;
            }
            while (currentLeftMostSon != nullptr) {
                queue.push(currentLeftMostSon);
                currentLeftMostSon = currentLeftMostSon->next;
            }
        }
        throw invalid_argument("Superior Name Does Not Exist In Organization Chart!\n");
    }

    Node *OrgChart::getHead() {
        return this->_root;
    }

    OrgIter OrgChart::begin() {
        exist_root();
        updateNodesForLevelOrder();
        return OrgIter(curr_iter);
    }

    OrgIter OrgChart::end() {
        exist_root();
        updateNodesForLevelOrder();
        return OrgIter(nullptr);
    }

    OrgIter OrgChart::begin_level_order() {
        return begin();
    }

    OrgIter OrgChart::end_level_order() {
        return end();
    }

    OrgIter OrgChart::begin_reverse_order() {
        exist_root();
        updateNodesForReverseLevelOrder();
        return OrgIter(curr_iter);
    }

    OrgIter OrgChart::reverse_order() {
        exist_root();
        updateNodesForReverseLevelOrder();
        return OrgIter(nullptr);
    }

    OrgIter OrgChart::begin_preorder() {
        exist_root();
        updateNodesForPreorder();
        return OrgIter(curr_iter);
    }

    OrgIter OrgChart::end_preorder() {
        exist_root();
        updateNodesForPreorder();
        return OrgIter(nullptr);
    }

    void OrgChart::updateNodesForLevelOrder() {
        curr_iter = this->_root;
        queue<Node *> queue;
        queue.push(this->_root);
        while (!queue.empty()) {
            Node *temp = queue.front();
            queue.pop();
            Node *currentSon = temp->leftMostSon;
            while (currentSon != nullptr) {
                queue.push(currentSon);
                currentSon = currentSon->next;
            }
            if (queue.empty()) {
                temp->nextInIteration = nullptr;
                return;
            }
            temp->nextInIteration = queue.front();
        }
    }

    void OrgChart::updateNodesForReverseLevelOrder() {
        queue<Node *> queue;
        queue.push(this->_root);
        this->_root->nextInIteration = nullptr;
        Node *lastInQueue = nullptr;
        while (!queue.empty()) {
            Node *temp = queue.front();
            queue.pop();
            Node *currentSon = nullptr;
            if (temp->rightMostSon == nullptr) {
                currentSon = temp->leftMostSon;
            } else {
                currentSon = temp->rightMostSon;
            }
            while (currentSon != nullptr) {
                queue.push(currentSon);
                currentSon = currentSon->prev;
            }
            if (queue.empty()) {
                temp->nextInIteration = lastInQueue;
                curr_iter = temp;
                return;
            }
            queue.front()->nextInIteration = temp;
            lastInQueue = temp;
        }
    }


    void OrgChart::updateNodesForPreorder() {
        curr_iter = this->_root;
        stack<Node *> stack;
        stack.push(this->_root);
        while (!stack.empty()) {
            Node *temp = stack.top();
            stack.pop();
            Node *currentSon = nullptr;
            if (temp->rightMostSon == nullptr) {
                currentSon = temp->leftMostSon;
            } else {
                currentSon = temp->rightMostSon;
            }
            while (currentSon != nullptr) {
                stack.push(currentSon);
                currentSon = currentSon->prev;
            }
            if (stack.empty()) {
                temp->nextInIteration = nullptr;
                return;
            }
            temp->nextInIteration = stack.top();
        }
    }

        std::ostream &operator<<(std::ostream &output, const OrgChart &chart) {
            if (chart._root == NULL) {
                return output;
            }
            queue<Node *> q;
            q.push(chart._root);
            while (!q.empty()) {
                int n = q.size();
                // If this node has children
                while (n > 0) {
                    // Dequeue an item from queue and print it
                    Node *currentNode = q.front();
                    q.pop();
                    output << currentNode->_name << " ";

                    // Enqueue all children of the dequeued item
                    Node *currentSon = currentNode->leftMostSon;
                    while (currentSon != nullptr) {
                        q.push(currentSon);
                        currentSon = currentSon->next;
                    }
                    n--;
                }
                output << endl;
            }
            return output;
        }

        void check_name(const string &name) {
                if (name.empty() || name =="\n" || name =="\t" || name =="\r" || name ==" ") {
                    throw std::runtime_error("name unreadbale\n");}
        }

        void OrgChart::exist_root() {
            if (this->_root == nullptr) {
                throw std::runtime_error("empty Tree");
            }
        }

    }