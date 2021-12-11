#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                "8 2 3\n"
                "170\n"
                "205\n"
                "225\n"
                "190\n"
                "260\n"
                "130\n"
                "225\n"
                "160"
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    INFO(buffer.str());
    REQUIRE(buffer.str() ==
            "30"
    );
}

TEST_CASE("0 dist", ""){
    std::stringstream input(
            "5 2 2\n"
            "1\n"
            "1\n"
            "100\n"
            "101\n"
            "101\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() == "0"
    );
}
