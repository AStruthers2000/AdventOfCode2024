#include "Problem.h"

import FileParsing;
#include <chrono>
#include <iostream>
#include <format>

Problem::Problem(std::string_view file_name, const std::optional<std::string_view>& problem_name)
{
    _lines = ReadFromFile(file_name);
    _problem_name = problem_name.value_or("=====DAY NOT IMPLEMENTED=====");
}

void Problem::Solve()
{
    std::cout << "Solving " << _problem_name << std::endl;

    double total_time = 0.0;
    
    auto start = std::chrono::high_resolution_clock::now();
    LoadProblem();
    auto end = std::chrono::high_resolution_clock::now();
    auto load_time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1e+6;
    
    
    
    start = std::chrono::high_resolution_clock::now();
    const auto part1_solution = SolvePart1();
    end = std::chrono::high_resolution_clock::now();
    auto part1_time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1e+6;
    
    std::cout << "Part 1 solution:\t\t" << part1_solution.value_or(0) << std::endl;// << "\n\tSolved in " << part1_time << " seconds.\n" << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    const auto part2_solution = SolvePart2();
    end = std::chrono::high_resolution_clock::now();
    auto part2_time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1e+6;
    std::cout << "Part 2 solution:\t\t" << part2_solution.value_or(0) << std::endl;//"\n\tSolved in " << part2_time << " seconds.\n" << std::endl;

    total_time += load_time;
    total_time += part1_time;
    total_time += part2_time;
    std::cout << std::endl;
    std::cout << std::format("Loading/parsing solution took:\t{:08.6f} seconds. \t({:06.3f}%)\n", load_time, (load_time / total_time) * 100.0);
    //std::cout << "Loading/parsing solution took:\t" << load_time << " seconds.  \t(" << (load_time / total_time) * 100.0 << "%)" << std::endl;
    std::cout << std::format("Part 1 solved in:             \t{:08.6f} seconds.  \t({:06.3f}%)\n", part1_time, (part1_time / total_time) * 100.0);
    std::cout << std::format("Part 2 solved in:             \t{:08.6f} seconds.  \t({:06.3f}%)\n", part2_time, (part2_time / total_time) * 100.0);
    std::cout << std::format("Total time:                   \t{:08.6f} seconds.", total_time) << std::endl;
    std::cout << "=================================================" << std::endl;
}
