#pragma once
#include "../Problem.h"

//enum Direction : uint8_t;

enum Direction : uint8_t;

class Day06 : public Problem
{
public:
    Day06(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 6: Guard Gallivant")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<char>> initial_grid;
    std::pair<int, int> guard_location;
    std::pair<int, int> initial_guard_location;

    void ResetGrid()
    {
        grid = {initial_grid.begin(), initial_grid.end()};
        guard_location = initial_guard_location;
    }

    bool IsValidLocation(std::pair<int, int> location) const;
    bool StepThroughGrid(Direction& current_direction);

    char GetTileInFront(std::pair<int, int>& location, Direction current_direction) const;
    Direction RotateDirection(Direction current_direction);
};




