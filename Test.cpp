#include "doctest.h"
#include "sources/node.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

TEST_CASE("Node functions"){
    node n("nizan");
    CHECK_EQ(n.GetName(), "nizan");
}
