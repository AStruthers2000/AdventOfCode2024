#include "Day06.h"

#include <algorithm>
#include <ios>
#include <iostream>
import StringHelper;

void Day06::LoadProblem()
{
    int row = 0;
    for (const auto& line : _lines)
    {
        std::vector temp(line.begin(), line.end());
        const auto has_carrot = std::ranges::find(temp, '^');
        if (has_carrot != std::ranges::end(temp))
        {
            initial_guard_location = std::make_pair(row, static_cast<int>(has_carrot - temp.begin()));
        }
            
        initial_grid.push_back(temp);
        ++row;
    }
}

std::optional<uint64_t> Day06::SolvePart1()
{
    ResetGrid();
    
    int tiles_walked = 1;
    Direction guard_direction = Up;
    bool guard_in_grid = true;
    while (guard_in_grid)
    {
        if (StepThroughGrid(guard_direction)) ++tiles_walked;

        /*
        for (const auto& line : grid)
        {
            for (const auto& c : line)
                std::cout << c;
            std::cout << "\n";
        }
        std::cout << "=================================\n";
        */

        guard_in_grid = IsValidLocation(guard_location);
    }
    
    return tiles_walked;
}

std::optional<uint64_t> Day06::SolvePart2()
{
    ResetGrid();
    grid[initial_guard_location.first][initial_guard_location.second] = 'X';
    
    int loops_detected = 0;
    Direction guard_direction = Up;
    bool guard_in_grid = true;
    while (guard_in_grid)
    {
        StepThroughGrid(guard_direction);
        guard_in_grid = IsValidLocation(guard_location);
        if (!guard_in_grid) break;
        //grid[guard_location.first][guard_location.second] = 'X';
        
        //now we have made a step, and we know it was a valid step
        //what we want to do now is:
        //1. check the tile in the grid to our right (from the direction we are currently facing)
        //2. if that tile is an 'X', we have already walked on that tile before (possible loop incoming)
        //3. if 2 is true, AND we look "in that direction", if we see a '#', we know that if we turned right, right now,
        //      we would enter a loop. if we don't see a '#', we wouldn't loop
        //4. if a loop was detected, increment the counter by 1 and continue stepping (we don't want to actually loop forever)
        Direction look_direction = RotateDirection(guard_direction);
        auto temp_location = guard_location;

        bool loop_detected = false;
        char tile = GetTileInFront(temp_location, look_direction);
        char prev_tile = grid[guard_location.first][guard_location.second];
        while (tile != '\0')
        {
            if (tile == '#')
            {
                if (prev_tile == 'X')
                {
                    loop_detected = true;
                }
                break;
            }
            prev_tile = tile;
            tile = GetTileInFront(temp_location, look_direction);
        }

        if (loop_detected)
        {
            
            auto obstacle_location = guard_location;
            GetTileInFront(obstacle_location, guard_direction);
            const auto non_tile = grid[obstacle_location.first][obstacle_location.second];
            grid[obstacle_location.first][obstacle_location.second] = 'O';
            
            for (const auto& line : grid)
            {
                for (const auto& c : line)
                    std::cout << c;
                std::cout << "\n";
            }
            std::cout << "=================================\n";
            grid[obstacle_location.first][obstacle_location.second] = non_tile;
            
            ++loops_detected;
        }

        
    }
    return loops_detected;
}

bool Day06::StepThroughGrid(Direction& current_direction)
{
    bool stepped_on_new_tile = false;
    std::pair<int, int> new_guard_location = guard_location;
    const char next_char = GetTileInFront(new_guard_location, current_direction);

    if (IsValidLocation(new_guard_location))
    {
        if (next_char == '#')
        {
            current_direction = RotateDirection(current_direction);
        }
        else
        {
            if (grid[guard_location.first][guard_location.second] != 'X')
            {
                stepped_on_new_tile = true;
            }
            grid[guard_location.first][guard_location.second] = 'X';
            guard_location = new_guard_location;
        }
    }

    if (!IsValidLocation(new_guard_location))
    {
        guard_location = new_guard_location;
    }

    return stepped_on_new_tile;
}

char Day06::GetTileInFront(std::pair<int, int>& location, const Direction current_direction) const
{
    switch (current_direction)
    {
    case Up:
        location = std::make_pair(location.first - 1, location.second);
        break;
    case Down:
        location = std::make_pair(location.first + 1, location.second);
        break;
    case Right:
        location = std::make_pair(location.first, location.second + 1);
        break;
    case Left:
        location = std::make_pair(location.first, location.second - 1);
        break;
    default: break;
    }

    if (IsValidLocation(location))
    {
        return grid[location.first][location.second];
    }
    
    return '\0';
}

bool Day06::IsValidLocation(const std::pair<int, int> location) const
{
    const int x = location.first;
    const int y = location.second;

    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
    {
        return false;
    }

    return true;
}

Direction Day06::RotateDirection(Direction current_direction)
{
    switch (current_direction)
    {
    case Up:
        current_direction = Right;
        break;
    case Down:
        current_direction = Left;
        break;
    case Right:
        current_direction = Down;
        break;
    case Left:
        current_direction = Up;
        break;
    default: break;
    }
    return current_direction;;
}
