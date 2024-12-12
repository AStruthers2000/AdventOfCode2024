//import std;
import FileParsing;
import StringHelper;
import Math;

#include <iostream>
import <string>;
import <vector>;

#include "Problems/Problem.h"
#include "Problems/Day01/Day01.h"
#include "Problems/Day02/Day02.h"
#include "Problems/Day03/Day03.h"
#include "Problems/Day04/Day04.h"
#include "Problems/Day05/Day05.h"
#include "Problems/Day06/Day06.h"
#include "Problems/Day07/Day07.h"
#include "Problems/Day08/Day08.h"
#include "Problems/Day09/Day09.h"
#include "Problems/Day10/Day10.h"
#include "Problems/Day11/Day11.h"
#include "Problems/Day12/Day12.h"
#include "Problems/Day13/Day13.h"
#include "Problems/Day14/Day14.h"
#include "Problems/Day15/Day15.h"
#include "Problems/Day16/Day16.h"
#include "Problems/Day17/Day17.h"
#include "Problems/Day18/Day18.h"
#include "Problems/Day19/Day19.h"
#include "Problems/Day20/Day20.h"
#include "Problems/Day21/Day21.h"
#include "Problems/Day22/Day22.h"
#include "Problems/Day23/Day23.h"
#include "Problems/Day24/Day24.h"
#include "Problems/Day25/Day25.h"

enum RunMode
{
    Test = 0,
    Run = 1
};

constexpr RunMode mode = Test;
constexpr int day = 12;

std::vector<std::unique_ptr<Problem>> LoadProblems()
{
    std::vector<std::unique_ptr<Problem>> problems;
    
    problems.push_back(std::make_unique<Day01>(mode == Test ? R"(.\Problems\Day01\test.txt)" : R"(.\Problems\Day01\input.txt)"));
    problems.push_back(std::make_unique<Day02>(mode == Test ? R"(.\Problems\Day02\test.txt)" : R"(.\Problems\Day02\input.txt)"));
    problems.push_back(std::make_unique<Day03>(mode == Test ? R"(.\Problems\Day03\test.txt)" : R"(.\Problems\Day03\input.txt)"));
    problems.push_back(std::make_unique<Day04>(mode == Test ? R"(.\Problems\Day04\test.txt)" : R"(.\Problems\Day04\input.txt)"));
    problems.push_back(std::make_unique<Day05>(mode == Test ? R"(.\Problems\Day05\test.txt)" : R"(.\Problems\Day05\input.txt)"));
    problems.push_back(std::make_unique<Day06>(mode == Test ? R"(.\Problems\Day06\test.txt)" : R"(.\Problems\Day06\input.txt)"));
    problems.push_back(std::make_unique<Day07>(mode == Test ? R"(.\Problems\Day07\test.txt)" : R"(.\Problems\Day07\input.txt)"));
    problems.push_back(std::make_unique<Day08>(mode == Test ? R"(.\Problems\Day08\test.txt)" : R"(.\Problems\Day08\input.txt)"));
    problems.push_back(std::make_unique<Day09>(mode == Test ? R"(.\Problems\Day09\test.txt)" : R"(.\Problems\Day09\input.txt)"));
    problems.push_back(std::make_unique<Day10>(mode == Test ? R"(.\Problems\Day10\test.txt)" : R"(.\Problems\Day10\input.txt)"));
    problems.push_back(std::make_unique<Day11>(mode == Test ? R"(.\Problems\Day11\test.txt)" : R"(.\Problems\Day11\input.txt)"));
    problems.push_back(std::make_unique<Day12>(mode == Test ? R"(.\Problems\Day12\test.txt)" : R"(.\Problems\Day12\input.txt)"));
    problems.push_back(std::make_unique<Day13>(mode == Test ? R"(.\Problems\Day13\test.txt)" : R"(.\Problems\Day13\input.txt)"));
    problems.push_back(std::make_unique<Day14>(mode == Test ? R"(.\Problems\Day14\test.txt)" : R"(.\Problems\Day14\input.txt)"));
    problems.push_back(std::make_unique<Day15>(mode == Test ? R"(.\Problems\Day15\test.txt)" : R"(.\Problems\Day15\input.txt)"));
    problems.push_back(std::make_unique<Day16>(mode == Test ? R"(.\Problems\Day16\test.txt)" : R"(.\Problems\Day16\input.txt)"));
    problems.push_back(std::make_unique<Day17>(mode == Test ? R"(.\Problems\Day17\test.txt)" : R"(.\Problems\Day17\input.txt)"));
    problems.push_back(std::make_unique<Day18>(mode == Test ? R"(.\Problems\Day18\test.txt)" : R"(.\Problems\Day18\input.txt)"));
    problems.push_back(std::make_unique<Day19>(mode == Test ? R"(.\Problems\Day19\test.txt)" : R"(.\Problems\Day19\input.txt)"));
    problems.push_back(std::make_unique<Day20>(mode == Test ? R"(.\Problems\Day20\test.txt)" : R"(.\Problems\Day20\input.txt)"));
    problems.push_back(std::make_unique<Day21>(mode == Test ? R"(.\Problems\Day21\test.txt)" : R"(.\Problems\Day21\input.txt)"));
    problems.push_back(std::make_unique<Day22>(mode == Test ? R"(.\Problems\Day22\test.txt)" : R"(.\Problems\Day22\input.txt)"));
    problems.push_back(std::make_unique<Day23>(mode == Test ? R"(.\Problems\Day23\test.txt)" : R"(.\Problems\Day23\input.txt)"));
    problems.push_back(std::make_unique<Day24>(mode == Test ? R"(.\Problems\Day24\test.txt)" : R"(.\Problems\Day24\input.txt)"));
    problems.push_back(std::make_unique<Day25>(mode == Test ? R"(.\Problems\Day25\test.txt)" : R"(.\Problems\Day25\input.txt)"));
    return problems;
}

int main(int argc, char* argv[])
{
    const auto problems = LoadProblems();

    problems[day - 1]->Solve(mode);

    return 0;
}
