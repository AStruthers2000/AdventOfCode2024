#pragma once
#include "../Problem.h"

class Day03 : public Problem
{
public:
    Day03(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 3: Mull It Over")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    std::vector<std::pair<int, int>> mul_pairs;
    std::vector<std::pair<int, int>> enabled_mul_pairs;
};

