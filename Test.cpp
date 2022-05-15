#include "doctest.h"
#include "OrgChart.hpp"
#include <exception>

using namespace ariel;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

TEST_CASE(""){
    OrgChart org;
    CHECK_NOTHROW(org.add_root("nizan"));
    CHECK_NOTHROW(org.add_sub("nizan", "Aviad"));
    CHECK_NOTHROW(org.add_sub("aviad", "lior"));
    CHECK_THROWS(org.add_sub("shir", "chen"));
    CHECK_THROWS(org.add_sub("Lior", "shir"));
    CHECK_NOTHROW(org.add_sub("lior", "hagai"));
    CHECK_NOTHROW(org.add_root("michal and nizan"));
    vector<node*> names_bfs= org.get_Tree()->BFS();
    CHECK(names_bfs.at(0)->get_name()=="michal and nizan");
    CHECK(names_bfs.at(1)->get_name()=="Aviad");
    CHECK(names_bfs.at(2)->get_name()=="lior");
    CHECK(names_bfs.at(3)->get_name()=="hagai");
    CHECK_THROWS(names_bfs.at(4));
    size_t count =0;
    for(auto& name : org){
        count++;
    }
    CHECK(count==4);
    CHECK_THROWS(org.add_sub("hagai", "shir"));
    CHECK_NOTHROW(org.add_sub("shir", "chen"));
    CHECK_THROWS(org.add_sub("shir", "chen"));
    CHECK_THROWS(org.add_sub("yosii", "chen"));
    CHECK_THROWS(org.add_sub("chen", "chen"));
    CHECK_THROWS(org.add_sub("shir", "chen"));
    CHECK_NOTHROW(org.add_root("Gilboa family"));

}
