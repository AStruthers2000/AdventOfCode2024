#include "Day04.h"

#include <execution>
#include <iostream>
import StringHelper;

void Day04::LoadProblem()
{
    for (const auto& line : _lines)
    {
        std::vector temp(line.begin(), line.end());
        grid.push_back(temp);
    }
}

std::optional<uint64_t> Day04::SolvePart1()
{
    
    /*
    //tried to parallelize it, and it *does* work, but silly over overhead makes it slower than the boring sequential way
    std::vector<std::pair<int, int>> flattened_grid;
    for (int x = 0; x < static_cast<int>(grid.size()); x++)
    {
        for (int y = 0; y < static_cast<int>(grid[x].size()); y++)
        {
            flattened_grid.push_back(std::make_pair(x, y));
        }
    }

    std::atomic counter(0);
    std::for_each(std::execution::par,
        flattened_grid.begin(), flattened_grid.end(),
        [&](const std::pair<int, int>& index)
        {
            if (grid[index.first][index.second] == 'X')
            {
                const auto test = BuildStringsFromGrid(grid, index, 4);
                for (const auto& word : test | std::views::values)
                {
                    if (word.has_value() && word.value() == "XMAS")
                    {
                        ++counter;
                    }
                }
            }
        });

    return counter;
    */
    
    for (int x = 0; x < static_cast<int>(grid.size()); x++)
    {
        for (int y = 0; y < static_cast<int>(grid[x].size()); y++)
        {
            const char c = grid[x][y];
            if (c == 'X')
            {
                const auto test = BuildStringsFromGrid(grid, {x, y}, 4);
                for (const auto& [direction, word] : test)
                {
                    if (word.has_value() && word.value() == "XMAS")
                    {
                        xmas_instances.emplace_back(std::make_pair(x, y), direction);
                    }
                }
            }
        }
    }
    
    return xmas_instances.size();
}

std::optional<uint64_t> Day04::SolvePart2()
{
    for (int x = 0; x < static_cast<int>(grid.size()); x++)
    {
        for (int y = 0; y < static_cast<int>(grid[x].size()); y++)
        {
            char c = grid[x][y];
            if (c == 'A')
            {
                const auto test = GetSurroundingElements(grid, {x, y});

                const auto up_left = test.at(Diag_Up_Left);
                const auto up_right = test.at(Diag_Up_Right);
                const auto down_left = test.at(Diag_Down_Left);
                const auto down_right = test.at(Diag_Down_Right);
                
                //if all four diagonal elements surrounding this 'A' have values, we know we have a *chance* of finding x-mas
                if (up_left.has_value() && up_right.has_value() && down_left.has_value() && down_right.has_value())
                {
                    /*
                     * Four combinations: up_left == 'M', up_right == 'S', down_left == 'M', down_right == 'S'
                     *                    up_left == 'M', up_right == 'M', down_left == 'S', down_right == 'S'
                     *                    up_left == 'S', up_right == 'M', down_left == 'S', down_right == 'M'
                     *                    up_left == 'S', up_right == 'S', down_left == 'M', down_right == 'M'
                     */

                    const bool rot_1 = up_left.value() == 'M' && up_right.value() == 'S' && down_left.value() == 'M' && down_right.value() == 'S';
                    const bool rot_2 = up_left.value() == 'M' && up_right.value() == 'M' && down_left.value() == 'S' && down_right.value() == 'S';
                    const bool rot_3 = up_left.value() == 'S' && up_right.value() == 'M' && down_left.value() == 'S' && down_right.value() == 'M';
                    const bool rot_4 = up_left.value() == 'S' && up_right.value() == 'S' && down_left.value() == 'M' && down_right.value() == 'M';
                    if (rot_1 || rot_2 || rot_3 || rot_4)
                    {
                        x_mas_instances.push_back(std::make_pair(x, y));
                    }
                }
            }
        }
    }
    
    return x_mas_instances.size();
}

