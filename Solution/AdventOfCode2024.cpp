//import std;
import FileParsing;
import StringHelper;
import Math;

#include <iostream>
import <string>;
import <vector>;

#include "Problems/Problem.h"
#include "Problems/Day1/Day1.h"

enum RunMode
{
    Test,
    Run
};

constexpr RunMode mode = Run;
constexpr int day = 1;

int main(int argc, char* argv[])
{
    std::vector<std::shared_ptr<Problem>> problems;
    problems.push_back(std::make_shared<Day1>(mode == Test ? R"(.\Problems\Day1\test.txt)" : R"(.\Problems\Day1\input.txt)"));

    problems[day - 1]->Solve();
    
    return 0;
}
