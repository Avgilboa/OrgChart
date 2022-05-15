#include "Tree.hpp"
using std::string;
using std::vector;
Tree::Tree(){
    node* root = nullptr;
    _root  = root;
    _version =0;
    _sizeTree =0;
    _maxLevel =0;
}
Tree::~Tree(){
    /*
     * @brief : iterarte the Tree to top
      and remove the nodes
     * need to understand this and do it
     */
    delete(this->get_root());
    // vector<node*> nodes = this->BFS();
    // nodes.reserve(nodes.size());
    // for(size_t i=0; i<nodes.size();i++){
    //     delete(nodes.at(i));
    // }
}

vector<node*> Tree::BFS(){
    /**
     * @brief: get the tree and return the nodes in BFS order
     *  we will use this vector to iterat the nodes
     *  pay attention: we still dont have an null pointer at the end
     */
    vector<node*> curr_order;
    curr_order.push_back(this->_root);
    size_t p_index =0;
    node* Curr_Node = this->get_root();
    while(this->get_size()>p_index+1){
        for(auto it : Curr_Node->get_children())
        {
            curr_order.push_back(it);
        }
        Curr_Node = curr_order.at(++p_index);
    }
    return curr_order;
}

vector<node*> Tree::preorder(node * start=nullptr){
    static vector<node*> curr_order;
    if(start==nullptr){
        curr_order.push_back(this->get_root());
    }
    else if (start!=nullptr)
    {
        curr_order.push_back(start);
    }
    
    for(auto it : curr_order){
        return preorder(it);
    }
    return curr_order;
}

node* Tree::find_node(string name){
    vector<node*> bfs_order = this->BFS();
    for(auto it : bfs_order){
        if(*it == name){
            return it;
        }
    }
    throw ("there is no node called this name");
}

node* Tree::get_root() const{return this->_root;}
size_t Tree::get_version() const{return this->_version;}
size_t Tree::get_size() const {return this->_sizeTree;}
size_t* Tree::get_ptVersion() {return &(this->_sizeTree);}
void Tree::update_version(){
    this->_version++;
    this->_sizeTree++;
}

void Tree::set_root(std::string name){
    if(this->_root == nullptr){
        this->_root = new node(name);
        this->_version++;
        this->_sizeTree++;
        this->_maxLevel++;
    }
    else{
        this->_root->set_name(name);
        this->_version++;
    }
}