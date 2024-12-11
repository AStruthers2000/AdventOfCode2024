#pragma once
#include <map>
#include <unordered_map>

#include "../Problem.h"

class Day11 : public Problem
{
public:
    Day11(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 11: Plutonian Pebbles")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    std::vector<uint64_t> initial_stones;

    std::map<uint64_t, std::vector<uint64_t>> stones_map;
    uint64_t blink_stones(int n);
    std::vector<uint64_t> blink_stone(uint64_t stone);
    std::unordered_map<uint64_t, uint64_t> blink_all(const std::unordered_map<uint64_t, uint64_t>& input_stones);
};



