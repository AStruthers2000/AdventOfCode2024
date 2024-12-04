#pragma once
#include <map>

#include "../Problem.h"

enum Direction : uint8_t;

class Day04 : public Problem
{
public:
    Day04(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 4: Ceres Search")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    
    std::vector<std::pair<std::pair<int, int>, Direction>> xmas_instances;
    std::vector<std::pair<int, int>> x_mas_instances;
    std::vector<std::vector<char>> grid;

    /*
    std::map<Direction, std::optional<std::string>> BuildStringsFromGrid(
        const std::vector<std::vector<char>>& grid, std::pair<int, int> position, int length);
    */
};

