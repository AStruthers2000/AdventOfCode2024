#pragma once
#include "../Problem.h"

class Day14 : public Problem
{
public:
    Day14(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 14: Restroom Redoubt")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    using Point = std::pair<int, int>;
    struct Robot
    {
        Point location;
        Point velocity;
    };
    std::vector<Robot> robots;

    void MoveRobot(Robot& robot);
};


