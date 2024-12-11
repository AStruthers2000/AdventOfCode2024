#pragma once
#include <map>
#include <set>

#include "../Problem.h"

class Day07 : public Problem
{
public:
    Day07(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 7: Bridge Repair")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;


private:
    std::vector<std::pair<uint64_t, std::vector<uint64_t>>> calibrations;

    enum BasicOperation : uint8_t
    {
        Add,
        Multiply,
        Concat
    };

    bool CheckSolution_Recursive(uint64_t target, const std::vector<uint64_t>& values, int index, uint64_t running_total, BasicOperation operation);
    bool CheckSolution_WithConcat_Recursive(uint64_t target, const std::vector<uint64_t>& values, int index, uint64_t running_total, BasicOperation operation);
};


