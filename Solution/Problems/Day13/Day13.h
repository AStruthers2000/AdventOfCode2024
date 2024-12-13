#pragma once
#include "../Problem.h"

class Day13 : public Problem
{
public:
    Day13(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 13: Claw Contraption")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

    using Point = std::pair<uint64_t, uint64_t>;
    
    struct ClawMachine
    {
        Point button_a;
        Point button_b;
        Point prize_location;
    };

    std::vector<ClawMachine> claw_machines;

    static std::optional<Point> TryWinPrize(const ClawMachine& claw_machine);
};


