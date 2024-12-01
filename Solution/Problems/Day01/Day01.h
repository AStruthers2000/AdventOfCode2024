#pragma once
#include "../Problem.h"

class Day01 : public Problem
{
public:
    Day01(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 1: Historian Hysteria")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    std::vector<uint64_t> left_list;
    std::vector<uint64_t> right_list;


};
