#pragma once
#include <set>

#include "../Problem.h"

class Day16 : public Problem
{
public:
    Day16(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 16: Reindeer Maze")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    enum Direction : uint8_t
    {
        UP, DOWN, LEFT, RIGHT
    };
        
    enum TileData : uint8_t
    {
        Wall,
        Empty,
        Path,
        Start,
        Finish
    };
    struct Tile
    {
        std::pair<int, int> position;
        TileData tile;

        bool operator==(const Tile& other) const
        {
            return position == other.position && tile == other.tile;
        }

        bool operator<(const Tile& other) const
        {
            return position < other.position;
        }
    };
    struct PathfindingState
    {
        std::pair<int, int> position;
        int cost;
        std::pair<int, int> direction;
        bool operator>(const PathfindingState& other) const
        {
            return cost > other.cost;
        }
    };
    std::vector<std::vector<Tile>> map;
    Tile start;
    Tile finish;

    std::pair<std::vector<Tile>, int> GetPathThroughMap(std::pair<int, int> start);

    void PrintMap();
};



