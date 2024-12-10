#pragma once
#include "../Problem.h"

class Day09 : public Problem
{
public:
    Day09(const std::string_view& filename)
        : Problem(filename, std::nullopt)
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    using Disk = std::vector<std::optional<int>>;
    Disk expanded_disk;

    Disk SortIndividual();
};


