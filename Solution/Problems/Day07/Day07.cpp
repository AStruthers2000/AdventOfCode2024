#include "Day07.h"

#include <iostream>
import StringHelper;
import <string>;

void Day07::LoadProblem()
{
    for (const auto& line : _lines)
    {
        const auto split = SplitLineByToken(line, ": ");
        const uint64_t target = static_cast<uint64_t>(std::stoll(split[0]));
        const auto vals = SplitLineByToken(split[1], " ");
        std::vector<uint64_t> val_numbers;
        for (const auto& val : vals)
        {
            val_numbers.push_back(std::stoll(val));
        }
        calibrations.emplace(target, val_numbers);
    }
}

std::optional<uint64_t> Day07::SolvePart1()
{
    uint64_t sum = 0;
    for (const auto& equation : calibrations)
    {
        bool found_exact = CheckSolution_Recursive(equation.first, equation.second, 1, equation.second[0], Multiply) ||
            CheckSolution_Recursive(equation.first, equation.second, 1, equation.second[0], Add);

        sum += found_exact ? equation.first : 0;
    }
    return sum;
}

std::optional<uint64_t> Day07::SolvePart2()
{
    // TODO: Implement SolvePart2 logic
    return std::nullopt;
}

bool Day07::CheckSolution_Recursive(const uint64_t target, const std::vector<uint64_t>& values, const int index, uint64_t running_total,
                                    const BasicOperation operation)
{
    if (index == values.size() && running_total == target)
        return true;
    if (index >= values.size())
        return false;

    uint64_t new_total = running_total;
    switch (operation)
    {
    case Add:
        new_total += values[index];
        break;
    case Multiply:
        new_total *= values[index];
        break;
    default: return false;
    }
   
    if (new_total < running_total || new_total > target)
        return false;

    if (new_total == target)
        return true;

    return CheckSolution_Recursive(target, values, index + 1, new_total, Multiply) ||
        CheckSolution_Recursive(target, values, index + 1, new_total, Add);
}
