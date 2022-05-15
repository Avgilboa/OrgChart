#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class node{
    private:    
        std::string _name;
        std::vector<node*> _childrens;
        node* _parent;
    public:
        node(std::string name);
        ~node();
        
        void set_children(node* child);
        void set_parent(node* parent);

        std::string get_name() const;
        std::vector<node*> get_children() const;
        node* get_parent() const;
        size_t size(){ return this->get_name().size();}

        void set_name(std::string name);
        
        bool operator == (node other);
        bool operator == (std::string name);
        friend std::ostream& operator<< (std::ostream & oStream, node & node);


};