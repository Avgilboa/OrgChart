#include "node.hpp"
using std::string;
node::node(string name){
    this->_name = name;
    this->_parent = nullptr;
}
node::~node(){
    for(size_t i=0; i<this->_childrens.size();i++){
        node* temp =this->_childrens.at(i);
        delete(temp); 
    }
    std::cout << "\ndelete node name: " << this->get_name() 
    << "\nafter he have: " << this->get_children().size() << " number of childrens" 
    << std::endl;
}

void node::set_children(node* child){
    this->_childrens.push_back(child);
    
}

void node::set_parent(node* parent){
    this->_parent = parent;
}

string node::get_name() const{ return this->_name;}
std::vector<node*> node::get_children() const { return this->_childrens;}
node* node::get_parent() const { return this->_parent;}

void node::set_name(std::string name){
    this->_name = name;
}

bool node::operator==(node other){ 
    return this->_name == other._name;}

bool node::operator==(string name){
    return this->_name == name;}

std::ostream& operator<< (std::ostream & oStream, node & node){
    oStream << node.get_name();
    return oStream;
}

