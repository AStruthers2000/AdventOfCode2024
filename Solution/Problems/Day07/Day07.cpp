#include "Day07.h"

#include <execution>
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
        calibrations.push_back(std::make_pair(target, val_numbers));
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
    uint64_t sum = 0;
    
    std::vector<uint64_t> calibration_results(calibrations.size(), 0);
    std::ranges::for_each(calibrations, [&](const auto& equation)
    {
        bool found_exact = CheckSolution_WithConcat_Recursive(equation.first, equation.second, 1, equation.second[0], Multiply) ||
            CheckSolution_WithConcat_Recursive(equation.first, equation.second, 1, equation.second[0], Add) ||
            CheckSolution_WithConcat_Recursive(equation.first, equation.second, 1, equation.second[0], Concat);
        sum += found_exact ? equation.first : 0;
    });

    /* This doesn't work, and it's slower, despite me trying to be cool :(
    std::for_each(calibrations.begin(), calibrations.end(), [&](const auto& equation)
    {
        if (GenerateOperationPermutations(equation.second.size(), 3, equation.second, equation.first))
            sum += equation.first;
    });
    */
    
    return sum;
}

bool Day07::CheckSolution_Recursive(const uint64_t target, const std::vector<uint64_t>& values, const int index, uint64_t running_total,
    BasicOperation operation)
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
    
    return  CheckSolution_Recursive(target, values, index + 1, new_total, Multiply) || CheckSolution_Recursive(target, values, index + 1, new_total, Add);
}

bool Day07::CheckSolution_WithConcat_Recursive(uint64_t target, const std::vector<uint64_t>& values, int index,
    uint64_t running_total, BasicOperation operation)
{
    if (index == values.size() && running_total == target)
        return true;
    if (index >= values.size())
        return false;

    std::vector<uint64_t> new_values = values;
    uint64_t new_total = running_total;
    int new_index = index;
    switch (operation)
    {
    case Add:
        new_total += values[index];
        ++new_index;
        break;
    case Multiply:
        new_total *= values[index];
        ++new_index;
        break;
        
    case Concat:
        {
            uint64_t concat_value = std::stoll(std::to_string(running_total) + std::to_string(values[index]));
            new_values.clear();
            new_values.push_back(concat_value);
            new_values.insert(new_values.end(), values.begin() + index + 1, values.end());
            new_total = concat_value;
            new_index = 1;
            break;
        }
    default: return false;
    }

    if (new_total < running_total || new_total > target)
        return false;

    return  CheckSolution_WithConcat_Recursive(target, new_values, new_index, new_total, Multiply) ||
        CheckSolution_WithConcat_Recursive(target, new_values, new_index, new_total, Add) ||
        CheckSolution_WithConcat_Recursive(target, new_values, new_index, new_total, Concat);

}

bool Day07::GenerateOperationPermutations(int num_elements, int num_operations, const std::vector<uint64_t>& values,
    uint64_t target)
{
    int totalSlots = num_elements - 1;       // Number of operation slots
    int totalPermutations = static_cast<int>(std::pow(num_operations, totalSlots)); // Total permutations (k^(n-1))

    for (int i = 0; i < totalPermutations; ++i) {
        std::vector<BasicOperation> operations;
        int temp = i;

        // Decode `temp` into a base-k representation
        for (int slot = 0; slot < totalSlots; ++slot) {
            int opIndex = temp % num_operations; // Extract the last digit in base-k
            temp /= num_operations;              // Move to the next digit

            // Map index to Operation
            switch (opIndex) {
            case 0: operations.push_back(Add); break;
            case 1: operations.push_back(Multiply); break;
            case 2: operations.push_back(Concat); break;
            }
        }

        // Print or process the permutation
        //PrintOperation(operations);
        const auto result = ApplyOperations(operations, values);
        if (result == target) return true;
    }

    return false;
}

uint64_t Day07::ApplyOperations(const std::vector<BasicOperation>& ops, const std::vector<uint64_t>& values)
{
    uint64_t running_total = values[0];
    for (int i = 0; i < ops.size(); ++i)
    {
        switch (ops[i])
        {
            case Add:
                running_total += values[i + 1];
                break;
            case Multiply:
                running_total *= values[i + 1];
                break;
            case Concat:
                uint64_t concat_value = std::stoll(std::to_string(running_total) + std::to_string(values[i + 1]));
                running_total = concat_value;
                break;
        }
    }
    return running_total;
}

void Day07::PrintOperation(const std::vector<BasicOperation>& ops)
{
    for (const auto& op : ops)
    {
        switch (op)
        {
        case Add:
            std::cout << "+ "; break;
        case Multiply:
            std::cout << "* "; break;
        case Concat:
            std::cout << "| "; break;
        }
    }
    std::cout << "\n";
}
