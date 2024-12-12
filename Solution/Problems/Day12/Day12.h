#pragma once
#include <map>
#include <set>

#include "../Problem.h"

enum Plant_Direction : uint8_t
{
    up = 0, right = 1, down = 2, left = 3
};

inline Plant_Direction& operator++(Plant_Direction& direction)
{
    direction = static_cast<Plant_Direction>((direction + 1) % 4);
    return direction;
}

inline Plant_Direction operator++(Plant_Direction& direction, int)
{
    Plant_Direction dir = direction;
    ++direction;
    return dir;
}

inline Plant_Direction& operator--(Plant_Direction& direction)
{
    switch (direction)
    {
    case up: direction = left; return direction;
    case right: direction = up; return direction;
    case down: direction = right; return direction;
    case left: direction = down; return direction;
    }
    return direction;
}

inline Plant_Direction operator--(Plant_Direction& direction, int)
{
    Plant_Direction dir = direction;
    --direction;
    return dir;
}

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
    
    using GardenPlot = std::pair<std::set<Point>, std::set<std::pair<Point, Plant_Direction>>>;
    std::map<char, std::set<GardenPlot>> plots;

    GardenPlot flood_fill(Point start, char plant_type);

    std::map<Plant_Direction, Point> directions_map{
                    {up, std::make_pair(-1, 0)},
                    {right, std::make_pair(0, 1)},
                    {down, std::make_pair(1, 0)},
                    {left, std::make_pair(0, -1)}
    };
};


