#pragma once
#include <map>
#include <set>

#include "../Problem.h"

class Day12 : public Problem
{
public:
    Day12(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 12: Garden Groups")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
     std::vector<std::vector<char>> garden;

    using Point = std::pair<int, int>;

    enum Direction : uint8_t { above, below, left, right };
    using GardenPlot = std::pair<std::set<Point>, std::set<std::pair<Point, Direction>>>;
    std::map<char, std::set<GardenPlot>> plots;

    GardenPlot flood_fill(Point start, char plant_type);

    std::vector<std::pair<Point, Direction>> directions{
        std::make_pair(std::make_pair(0, 1), right),
        std::make_pair(std::make_pair(1, 0), below),
        std::make_pair(std::make_pair(0, -1), left),
        std::make_pair(std::make_pair(-1, 0), above)
    };
};


