#pragma once
#include "../Problem.h"

class Day1 : public Problem
{
public:
    Day1(const std::string_view& filename)
        : Problem(filename)
    {
    }

protected:
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

public:

private:
    std::vector<uint64_t> left_list;
    std::vector<uint64_t> right_list;

    void ReadAndSort();
};
