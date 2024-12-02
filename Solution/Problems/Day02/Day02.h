#pragma once
#include <map>

#include "../Problem.h"

class Day02 : public Problem
{
public:
    Day02(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 2: Red-Nosed Reports")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    std::map<std::vector<uint64_t>, int> report_levels;
    void CalculateSafetyFactor();
    bool CheckSafety(const std::vector<uint64_t>& safety_factors);
};

