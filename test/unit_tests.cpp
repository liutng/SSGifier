#include"./catch_amalgamated.hpp"
#include "../Utils.h"
#include "../ArgumentQueue.h"
/**
 * This test case tests the robustness of the ArgumentQueue::addArg() function.
*/
TEST_CASE("Arguments test","[ArgumentQueue::addArg()]"){
    SDDS::ArgumentQueue aq = SDDS::ArgumentQueue();
    SECTION("Correct full switch"){
    REQUIRE(aq.addArg("--output", "output") == true);
    }
    SECTION("Wrong full switch"){
    REQUIRE(aq.addArg("--invalid", "nope") == false);
    }
    SECTION("Correct abbreviated switch"){
    REQUIRE(aq.addArg("-o", "output") == true);
    }
    SECTION("Wrong abbreviated switch"){
        REQUIRE(aq.addArg("-z","asdz") == false);
    }
    SECTION("Without dash argument"){
    REQUIRE(aq.addArg("zxc", "zxc") == false);
    }
    SECTION("With non-dash switch modifier"){
        REQUIRE(aq.addArg("|!djqiw", "none") == false);
    }
    SECTION("With empty switch"){
        REQUIRE(aq.addArg("", "something") == false);
    }
}
/**
 * This test case tests the function that reads the original file as HTML string
*/
TEST_CASE("HTML file parser test", "[SDDS::Utils::readFileAsHtmlStr()]"){
    SECTION("Existing file"){
        REQUIRE(!SDDS::readFileAsHtmlStr("test/test.txt").empty());
    }
    SECTION("Non-existing file"){
        REQUIRE(SDDS::readFileAsHtmlStr("test/nonexist.txt").empty());
    }
    SECTION("Empty file name"){
        REQUIRE(SDDS::readFileAsHtmlStr("").empty());
    }
    }
/**
 * This test case tests the markdown functionality
*/
TEST_CASE("HTML Markdown test","[SDDS::Utils::readFileAsHtmlStrMD()]"){
    SECTION("Existing file"){
        REQUIRE(!SDDS::readFileAsHtmlStr("test/test.md").empty());
    }
    SECTION("Non-existing file"){
        REQUIRE(SDDS::readFileAsHtmlStr("test/nonexist.md").empty());
    }
    SECTION("Empty file name"){
        REQUIRE(SDDS::readFileAsHtmlStr("").empty());
    }
}