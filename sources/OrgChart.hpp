
#include "OrgIter.hpp"


namespace ariel {

    class OrgChart {
    private:
        Node *_root;
        Node *curr_iter;
        void del_nodes();
        void exist_root();

        void updateNodesForLevelOrder();

        void updateNodesForReverseLevelOrder();

        void updateNodesForPreorder();

    public:
        OrgChart();
        OrgChart(OrgChart &other);

        OrgChart(OrgChart &&other) = default;

        OrgChart &operator=(OrgChart &&) = default;

        OrgChart &operator=(const OrgChart &other) = default;

        ~OrgChart();

        OrgChart &add_sub(const std::string& __parent, const std::string& __child);

        OrgChart &add_root(const std::string& name);

        Node *
        getSuperior(const std::string &superiorName);

        Node *getHead();


        /**
         * iteration functions
         */
        // general OrgChart begin and end
        OrgIter begin();

        OrgIter end();

        // level order begin and end
       OrgIter begin_level_order();

        OrgIter end_level_order();

        // reverse level order begin and end
        OrgIter begin_reverse_order();

        OrgIter reverse_order();

        // preorder begin and end
        OrgIter begin_preorder();

        OrgIter end_preorder();

        friend std::ostream &operator<<(std::ostream &output, const OrgChart &chart);

    };

    /**
     * validation functions.
     */
    void check_name(const std::string &name);


}
