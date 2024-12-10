#include "Day08.h"

#include <execution>
#include <iostream>
#include <ranges>

void Day08::LoadProblem()
{
    for (size_t i = 0; i < _lines.size(); i++)
    {
        for (size_t j = 0; j < _lines[i].size(); j++)
        {
            const char possible_antenna = _lines[i][j];
            if (possible_antenna != '.')
            {
                antenna_map[possible_antenna].emplace_back(static_cast<int>(i), static_cast<int>(j));
            }
        }
    }
}

std::optional<uint64_t> Day08::SolvePart1()
{
    const auto antinodes = FindAllAntinodes(1);

    int antinode_count = 0;
    for (const auto& line : antinodes)
    {
        for (const auto& c : line)
        {
            if (c == '#') ++antinode_count;
        }
    }
    return antinode_count;
}

std::optional<uint64_t> Day08::SolvePart2()
{
    const auto antinodes = FindAllAntinodes(static_cast<int>(_lines.size()));

    int antinode_count = 0;
    for (const auto& line : antinodes)
    {
        for (const auto& c : line)
        {
            if (c == '#') ++antinode_count;
        }
    }
    return antinode_count;
}

Day08::Grid Day08::FindAllAntinodes(int n)
{
    Grid antinodes;

    for (const auto& line : _lines)
    {
        std::vector antinode_row(line.size(), '.');
        antinodes.push_back(antinode_row);
    }

    const int grid_x = static_cast<int>(_lines.size());
    const int grid_y = static_cast<int>(_lines[0].size());
    
    for (const auto& antennas : antenna_map | std::views::values)
    {
        for (const auto& antenna : antennas)
        {
            for (const auto& other_antenna : antennas)
            {
                if (antenna != other_antenna)
                {
                    bool on_grid = true;
                    int antinode_count = 1;
                    while (on_grid && antinode_count <= n)
                    {
                        //calculate the distance
                        const std::pair distance = {other_antenna.first - antenna.first, other_antenna.second - antenna.second};
                        const std::pair double_dist = {distance.first * 2, distance.second * 2};
                        
                        int antinode_x; int antinode_y;
                        if (n == 1)
                        {
                            antinode_x = antenna.first + double_dist.first;
                            antinode_y = antenna.second + double_dist.second;
                        }
                        else
                        {
                            antinode_x = antenna.first + (distance.first * antinode_count);
                            antinode_y = antenna.second + (distance.second * antinode_count);
                        }
                        
                        if (antinode_x >= 0 && antinode_x < grid_x && antinode_y >= 0 && antinode_y < grid_y)
                        {
                            antinodes[antinode_x][antinode_y] = '#';
                            ++antinode_count;
                        }
                        else
                        {
                            on_grid = false;
                        }
                    }
                }
            }
        }
    }


    /* Another cool and parallel solution that isn't faster due to parallelism overhead
    const auto antenna_map_values = antenna_map | std::views::values;
    std::for_each(std::execution::par_unseq, antenna_map_values.begin(), antenna_map_values.end(),
        [&](const auto& antennas)
        {
            std::for_each(std::execution::par, antennas.begin(), antennas.end(),
                [&](const auto& antenna)
                {
                    std::for_each(std::execution::par_unseq, antennas.begin(), antennas.end(),
                        [&](const auto& other_antenna)
                        {
                            if (antenna != other_antenna)
                            {
                                bool on_grid = true;
                                int antinode_count = 1;
                                while (on_grid && antinode_count <= n)
                                {
                                    //calculate the distance
                                    const std::pair distance = {other_antenna.first - antenna.first, other_antenna.second - antenna.second};
                                    const std::pair double_dist = {distance.first * 2, distance.second * 2};
                        
                                    int antinode_x; int antinode_y;
                                    if (n == 1)
                                    {
                                        antinode_x = antenna.first + double_dist.first;
                                        antinode_y = antenna.second + double_dist.second;
                                    }
                                    else
                                    {
                                        antinode_x = antenna.first + (distance.first * antinode_count);
                                        antinode_y = antenna.second + (distance.second * antinode_count);
                                    }
                        
                                    if (antinode_x >= 0 && antinode_x < grid_x && antinode_y >= 0 && antinode_y < grid_y)
                                    {
                                        antinodes[antinode_x][antinode_y] = '#';
                                        ++antinode_count;
                                    }
                                    else
                                    {
                                        on_grid = false;
                                    }
                                }
                            }
                        });
                });
        });
        */
    return antinodes;
}
