//import std;
import FileParsing;
import StringHelper;
import Math;

#include <iostream>
import <string>;
import <vector>;

#include "Problems/Problem.h"
#include "Problems/Day1/Day1.h"

int main(int argc, char* argv[])
{
    std::vector<std::shared_ptr<Problem>> problems;
    problems.push_back(std::make_shared<Day1>(R"(.\Problems\Day1\input.txt)"));

    problems[0]->Solve();
    
    return 0;
}
