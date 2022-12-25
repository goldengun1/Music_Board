#define CONFIG_CATCH_MAIN
#include "../catch_amalgamated.hpp"


TEST_CASE("1 je 1", "[1]" )
{
    REQUIRE(1 == 1);
}
