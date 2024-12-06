#include "Day06.h"

#include <algorithm>
#include <ios>
#include <iostream>
#include <set>
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
        grid[guard_location.first][guard_location.second] = 'X';

        bool loop_detected = false;
        //if there is an obstacle to my right, let's try and place an obstacle directly in front of me
            //and see if I end up at loop_detect_location traveling in the direction of loop_detect_direction TWICE
            auto paused_grid = grid;
            auto paused_location = guard_location;
            auto paused_direction = guard_direction;

            std::pair<int, int> obstacle_location = guard_location;
            GetTileInFront(obstacle_location, guard_direction);
            if (IsValidLocation(obstacle_location))
            {
                grid[obstacle_location.first][obstacle_location.second] = '#';

                std::set<std::tuple<std::pair<int, int>, Direction>> guard_positions;
                guard_positions.insert(std::make_tuple(guard_location, guard_direction));
                bool simulated_guard_in_grid = true;
                while (simulated_guard_in_grid)
                {
                    StepThroughGrid(guard_direction);
                    simulated_guard_in_grid = IsValidLocation(guard_location);
                    if (!simulated_guard_in_grid) break;
                    //grid[guard_location.first][guard_location.second] = 'X';

                    /*
                    if (guard_location == loop_detect_location && guard_direction == loop_detect_direction)
                    {
                        been_there_count++;
                    }
                    */
                    if (guard_positions.contains(std::make_tuple(guard_location, guard_direction)))
                    {
                        loop_detected = true;
                        break;
                    }
                    
                    guard_positions.insert(std::make_tuple(guard_location, guard_direction));
                }

                if (loop_detected)
                {
                    ++loops_detected;
                    //std::cout << loops_detected << "\n";
                }
            }

            grid = paused_grid;
            guard_location = paused_location;
            guard_direction = paused_direction;

        /*
        Direction look_direction = RotateDirection(guard_direction);
        auto temp_location = guard_location;
        auto prev_temp_location = temp_location;;
        
        bool loop_detected = false;
        bool wall_to_right = false;
        char tile = GetTileInFront(temp_location, look_direction);
        while (tile != '\0')
        {
            if (tile == '#')
            {
                wall_to_right = true;
                break;
            }
            prev_temp_location = temp_location;
            tile = GetTileInFront(temp_location, look_direction);
        }

        if (wall_to_right)
        {
            auto loop_detect_location = prev_temp_location;
            auto loop_detect_direction = look_direction;
            int been_there_count = 0;

            //if there is an obstacle to my right, let's try and place an obstacle directly in front of me
            //and see if I end up at loop_detect_location traveling in the direction of loop_detect_direction TWICE
            auto paused_grid = grid;
            auto paused_location = guard_location;
            auto paused_direction = guard_direction;

            std::pair<int, int> obstacle_location = guard_location;
            GetTileInFront(obstacle_location, guard_direction);
            if (IsValidLocation(obstacle_location))
            {
                grid[obstacle_location.first][obstacle_location.second] = '#';

                std::set<std::tuple<std::pair<int, int>, Direction>> guard_positions;
                guard_positions.insert(std::make_tuple(guard_location, guard_direction));
                bool simulated_guard_in_grid = true;
                while (simulated_guard_in_grid)
                {
                    StepThroughGrid(guard_direction);
                    simulated_guard_in_grid = IsValidLocation(guard_location);
                    if (!simulated_guard_in_grid) break;
                    //grid[guard_location.first][guard_location.second] = 'X';

                    if (guard_positions.contains(std::make_tuple(guard_location, guard_direction)))
                    {
                        loop_detected = true;
                        break;
                    }
                    
                    guard_positions.insert(std::make_tuple(guard_location, guard_direction));
                }

                if (loop_detected)
                {
                    ++loops_detected;
                    //std::cout << loops_detected << "\n";
                }
            }

            grid = paused_grid;
            guard_location = paused_location;
            guard_direction = paused_direction;
        }
        */

        /*
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
        char second_prev = '\0';
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
            second_prev = prev_tile;
            prev_tile = tile;
            tile = GetTileInFront(temp_location, look_direction);
        }
        if (tile == '\0' && second_prev == 'X')
        {
            loop_detected = true;
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
        */

        
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
