#include "OrgChart.hpp"

using std::string;
using std::vector;
namespace ariel{
    OrgChart::OrgChart(){
        this->T = new Tree();
    }
    OrgChart::~OrgChart(){
        std::cout << "removing the tree and all the nodes";
        delete(this->T);
    }

    OrgChart& OrgChart::add_root(const string name){
        this->T->set_root(name);
        return (*this);
    }
    OrgChart& OrgChart::add_sub(const string parent, const string child){
        node* nParent;
        try
        {
            nParent = this->T->find_node(parent);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        nParent->set_children(new node(child));
        this->T->update_version();
        return (*this);
    }

    OrgChart::orgChart_Iterator::orgChart_Iterator(std::vector<node*> order, size_t version,size_t * pTree_version, size_t ptmemory){
        this->_order = order;
        this->_version = version;
        this->pt_curr_version = pTree_version;
        this->pt_place = ptmemory;
    }
    OrgChart::orgChart_Iterator OrgChart::orgChart_Iterator::operator++(){
        this->pt_place++;
        return *this;
    }
    OrgChart::orgChart_Iterator OrgChart::orgChart_Iterator::operator++(int){
        orgChart_Iterator temp(*this);
        this->pt_place++;
        return temp;
    }
    OrgChart::orgChart_Iterator OrgChart::orgChart_Iterator::operator--(){
        this->pt_place--;
        return *this;
    }
    OrgChart::orgChart_Iterator OrgChart::orgChart_Iterator::operator--(int){
        orgChart_Iterator temp(*this);
        this->pt_place--;
        return temp;
    }
    bool OrgChart::orgChart_Iterator::operator==(OrgChart::orgChart_Iterator other) const{
        return &(this->_order.at(this->pt_place))==&(other._order.at(other.pt_place));
    }
    bool OrgChart::orgChart_Iterator::operator!=(OrgChart::orgChart_Iterator other) const{
        return !(*this==other);
    }

    node& OrgChart::orgChart_Iterator::operator*() const {
        return *(this->_order.at(pt_place));
    }
    node* OrgChart::orgChart_Iterator::operator->() const {
        return (this->_order.at(pt_place));
    }

    bool OrgChart::orgChart_Iterator::check_valid() const{
        if(this->_version!= *this->pt_curr_version){
            throw std::runtime_error ("the graph cahnged");
        }
        if(this->pt_place>this->_order.size()){
            throw std::runtime_error ("out of bounds");
        }
        return true;
    }





    OrgChart::orgChart_Iterator OrgChart::begin() const{
        vector < node*> vec = this->T->BFS();
        orgChart_Iterator it(vec,this->T->get_version(), this->T->get_ptVersion(), 0);
        return it;
    }
    OrgChart::orgChart_Iterator OrgChart::end() const{
        vector < node*> vec = this->T->BFS();
        orgChart_Iterator it(vec,this->T->get_version(), this->T->get_ptVersion(),vec.size());
        return it;
    }


}