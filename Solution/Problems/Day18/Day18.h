#pragma once
#include "../Problem.h"

class Day18 : public Problem
{
public:
    Day18(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 18: RAM Run")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    using Point = std::pair<int, int>;
    
    enum GridObjectType : uint8_t
    {
        Empty = 0,
        Obstacle = 1,
        Path = 2
    };
    struct GridObject
    {
        GridObjectType obstacle;
        Point position;
    };
    
    using Grid = std::vector<std::vector<std::optional<GridObject>>>;
    
    Grid empty_grid;
    std::vector<Point> corrupted_points;

    Grid SimulateFallenBytes(int num_bytes) const;
    std::pair<Grid, Grid> SimulateThisAndPrevious(int num_bytes) const;
    std::vector<Point> PathfindThroughGrid(const Grid& grid) const;
};




