#include "node.hpp"
class Tree{
    /** 
     * @brief represent tree and algorithem on it**/
    private:
        node* _root;
        size_t _version;
        size_t _sizeTree;
        size_t _maxLevel;
    public:
        Tree();
        ~Tree();

        std::vector<node*> BFS();
        std::vector<node*> preorder(node * start);

        node* find_node(std::string name);

        node* get_root() const;
        size_t get_version() const ;
        size_t get_size() const;
        size_t* get_ptVersion();

        void update_version();

        void set_root(std::string name);
};