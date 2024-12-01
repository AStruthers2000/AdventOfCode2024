#include "Problem.h"

#include <iostream>
import FileParsing;

Problem::Problem(std::string_view filename)
{
    lines = ReadFromFile(filename);
}

void Problem::Solve()
{
    std::cout << "Solving problem"  << std::endl;

    const auto part1_solution = SolvePart1();
    std::cout << "Part 1 solution: " << part1_solution.value_or(0) << std::endl;
    
    
    const auto part2_solution = SolvePart2();
    std::cout << "Part 2 solution: " << part2_solution.value_or(0) << std::endl;
}
