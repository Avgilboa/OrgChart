#include "sources/OrgChart.hpp"
using namespace ariel;
using namespace std;
int main(){
    OrgChart org;
    org.add_root("Aviad").add_root("bobb").add_sub("bobb", "kobi").add_sub("bobb","willam").add_sub("bobb","toot");
    cout << org.GetRoot()->_next->_name<< endl;
    cout << org;

    return 0;
}