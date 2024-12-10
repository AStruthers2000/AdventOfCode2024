#pragma once
#include <map>
#include <vector>

#include "../Problem.h"

class Day08 : public Problem
{
public:
    Day08(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 8: Resonant Collinearity")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    using Grid = std::vector<std::vector<char>>;
    std::map<char, std::vector<std::pair<int, int>>> antenna_map;

    Grid FindAllAntinodes(int n);
};

