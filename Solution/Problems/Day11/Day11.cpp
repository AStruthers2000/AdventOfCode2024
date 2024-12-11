#include "Day11.h"

#include <execution>
#include <iostream>
import <string>;
#include <unordered_map>
import StringHelper;

void Day11::LoadProblem()
{
    std::string rocks = _lines[0];
    const auto rocks_list = SplitLineByToken(rocks, " ");
    for (const auto& rock : rocks_list)
    {
        initial_stones.push_back(std::stoll(rock));
    }
}

std::optional<uint64_t> Day11::SolvePart1()
{
    return blink_stones(25);
}

std::optional<uint64_t> Day11::SolvePart2()
{
    return blink_stones(75);
}

uint64_t Day11::blink_stones(int n)
{
    std::unordered_map<uint64_t, uint64_t> stone_counts;
    for (uint64_t num : initial_stones) {
        stone_counts[num]++;
    }
    
    for (int i = 0; i < n; ++i)
    {
        stone_counts = blink_all(stone_counts);
    }

    uint64_t sum = 0;
    for (const auto& count : stone_counts | std::views::values)
    {
        sum += count;
    }
    return sum;
}

std::unordered_map<uint64_t, uint64_t> Day11::blink_all(const std::unordered_map<uint64_t, uint64_t>& input_stones)
{
    std::unordered_map<uint64_t, uint64_t> new_stone_counts;

    std::ranges::for_each(input_stones, [&](const auto& stone_entry)
    {
        const uint64_t stone = stone_entry.first;
        uint64_t count = stone_entry.second;
        for (const auto& blink_stone : blink_stone(stone))
        {
            new_stone_counts[blink_stone] += count;
        }
    });
    
    return new_stone_counts;
}

std::vector<uint64_t> Day11::blink_stone(uint64_t stone)
{
    if (stones_map.contains(stone)) return stones_map[stone];
    
    std::string stone_string = std::to_string(stone);
    std::vector<uint64_t> new_stones;

    if (stone == 0)
    {
        new_stones.push_back(1);
    }
    else if (stone_string.size() % 2 == 0)
    {
        uint64_t left_stone = std::stoll(stone_string.substr(0, stone_string.size() / 2));
        uint64_t right_stone = std::stoll(stone_string.substr(stone_string.size() / 2));
        new_stones.push_back(left_stone);
        new_stones.push_back(right_stone);
    }
    else
    {
        new_stones.push_back(stone * 2024);
    }

    stones_map[stone] = new_stones;
    return new_stones;
}


