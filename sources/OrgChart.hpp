#include "Tree.hpp"
namespace ariel{
class OrgChart
{
    class orgChart_Iterator{
        private:
            std::vector<node*> _order;
            size_t _version;
            const size_t * pt_curr_version;
            size_t pt_place;
        public:

            OrgChart::orgChart_Iterator operator++();
            OrgChart::orgChart_Iterator operator++(int);
            OrgChart::orgChart_Iterator operator--();
            OrgChart::orgChart_Iterator operator--(int);
            bool operator==(OrgChart::orgChart_Iterator other) const;
            bool operator!=(OrgChart::orgChart_Iterator other) const;
            node& operator*() const;
            node* operator->() const;
            orgChart_Iterator(std::vector<node*> order, size_t version,size_t * pTree_version, size_t ptmemory);
            //~orgChart_Iterator();

            bool check_valid() const; // has no change on the tree, ther same level and version
    };
private:
    Tree* T;
public:
    OrgChart& add_root(const std::string name);
    OrgChart& add_sub(const std::string parent,const std::string child_new);

    orgChart_Iterator begin_level_order() const;
    orgChart_Iterator end_level_order() const;
    orgChart_Iterator begin_reverse_order() const;
    orgChart_Iterator reverse_order() const;
    orgChart_Iterator begin_preorder() const;
    orgChart_Iterator end_preorder() const;

    orgChart_Iterator begin() const;
    orgChart_Iterator end() const;
    friend std::ostream& operator << (std::ostream & oStream, OrgChart & other);
    Tree* get_Tree()const {return this->T;}

    OrgChart();
    ~OrgChart();
};
}