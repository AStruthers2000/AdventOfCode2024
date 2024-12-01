#include "Problem.h"

#include <chrono>
#include <iostream>
import FileParsing;

Problem::Problem(std::string_view file_name, const std::optional<std::string_view>& problem_name)
{
    _lines = ReadFromFile(file_name);
    _problem_name = problem_name.value_or("=====DAY NOT IMPLEMENTED=====");
}

void Problem::Solve()
{
    std::cout << "Solving " << _problem_name << std::endl;

    LoadProblem();
    
    auto start = std::chrono::high_resolution_clock::now();
    const auto part1_solution = SolvePart1();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Part 1 solution:\t" << part1_solution.value_or(0) << "\n\tSolved in " << static_cast<double>(duration.count()) / 1e+6 << " seconds." << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    const auto part2_solution = SolvePart2();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Part 2 solution:\t" << part2_solution.value_or(0) << "\n\tSolved in " << static_cast<double>(duration.count()) / 1e+6 << " seconds." << std::endl;
    std::cout << "========================================" << std::endl;
}
