#include "Problem.h"

import FileParsing;
#include <chrono>
#include <iostream>
#include <format>

Problem::Problem(std::string_view file_name, const std::optional<std::string_view>& problem_name)
{
    _problem_name = problem_name.value_or("=====DAY NOT IMPLEMENTED=====");
    try
    {
        _lines = ReadFromFile(file_name);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
}

void Problem::Solve(int mode)
{
    std::cout << "Solving " << _problem_name << ":" << std::endl;

    double total_time = 0.0;
    
    auto start = std::chrono::high_resolution_clock::now();
    LoadProblem();
    auto end = std::chrono::high_resolution_clock::now();
    auto load_time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1e+6;
    
    start = std::chrono::high_resolution_clock::now();
    const auto part1_solution = SolvePart1();
    end = std::chrono::high_resolution_clock::now();
    auto part1_time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1e+6;
    
    start = std::chrono::high_resolution_clock::now();
    const auto part2_solution = SolvePart2();
    end = std::chrono::high_resolution_clock::now();
    auto part2_time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1e+6;

    std::cout << "//==============================================\\\\" << std::endl;
    std::cout << "||  " << (mode == 1 ? "Full Input" : "TEST INPUT") << "\t\t|  Answer\t\t||" << std::endl;
    std::cout << "||----------------------+-----------------------||" << std::endl;
    std::cout << "||  Part 1        \t|  " << std::format("{:<20}", part1_solution.value_or(0)) << " ||" << std::endl;
    std::cout << "||  Part 2        \t|  " << std::format("{:<20}", part2_solution.value_or(0)) << " ||" << std::endl;
    std::cout << "\\\\==============================================//" << std::endl;

    total_time += load_time;
    total_time += part1_time;
    total_time += part2_time;
    
    std::cout << std::endl;
    std::cout << "//======================================================================\\\\" << std::endl;
    std::cout << "||  " << (mode == 1 ? "Full Input" : "TEST INPUT") << "\t\t|  Runtime (seconds)\t|  Percent of runtime   ||" << std::endl;
    std::cout << "||----------------------+-----------------------+-----------------------||" << std::endl;
    std::cout << std::format("||  Loading/parsing\t|  {:08.6f}\t\t|  {:06.3f}%\t\t||\n", load_time, (load_time / total_time) * 100.0);
    std::cout << std::format("||  Part 1         \t|  {:08.6f}\t\t|  {:06.3f}%\t\t||\n", part1_time, (part1_time / total_time) * 100.0);
    std::cout << std::format("||  Part 2         \t|  {:08.6f}\t\t|  {:06.3f}%\t\t||\n", part2_time, (part2_time / total_time) * 100.0);
    std::cout << "||----------------------+-----------------------+-----------------------||" << std::endl;
    std::cout << std::format("||  Total time     \t|  {:08.6f}\t\t|=======================||", total_time) << std::endl;
    std::cout << "\\\\======================================================================//" << std::endl;
}
