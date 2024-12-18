#include "Day18.h"

#include <filesystem>
#include <iostream>
#include <map>
#include <queue>
#include <set>
import StringHelper;
import <string>;

constexpr int grid_size = 71; //grid_size = 7 for test, grid_size = 71 for full
constexpr int fallen_bytes = 1024; //fallen_bytes = 12 for test, fallen_bytes = 1024 for full

void Day18::LoadProblem()
{
    empty_grid.resize(grid_size);
    for (auto i = 0; i < grid_size; ++i)
    {
        empty_grid[i].resize(grid_size);
    }

    for (const auto& line : _lines)
    {
        const auto split = SplitLineByToken(line, ",");
        const int x = std::stoi(split[0]);
        const int y = std::stoi(split[1]);
        corrupted_points.emplace_back(x, y);
    }
}

std::optional<uint64_t> Day18::SolvePart1()
{
    auto grid = SimulateFallenBytes(fallen_bytes);
    const auto path = PathfindThroughGrid(grid);

    return path.size() - 1;
}

std::optional<uint64_t> Day18::SolvePart2()
{
    int current_bit = static_cast<int>(corrupted_points.size()) / 2;
    int left = 0;
    int right = static_cast<int>(corrupted_points.size()) - 1;
    
    //a little bit of binary search to prevent doing linear search through the entire list of corrupted points
    while (true)
    {
        //std::cout << "Left: " << left << ",\tCurrent: " << current_bit << ",\t\tRight: " << right  << "\n";
        
        //simulate both the current bit and the previous bit grids
        const auto [grid_previous,
            grid_current] = SimulateThisAndPrevious(current_bit);

        //find path through both grids
        auto path_previous = PathfindThroughGrid(grid_previous);
        auto path_current = PathfindThroughGrid(grid_current);

        //if the previous path isn't empty but the current path is, the current bit breaks the pathfinding
        if (!path_previous.empty() && path_current.empty()) break;
        
        //we are too far in the bit order, so we want to move the right to current_bit (binary search left)
        if (path_current.empty())
        {
            right = current_bit;
        }
        //we are not far enough in the bit order, so we move the left to current_bit (binary search right)
        else
        {
            left = current_bit;
        }
        
        //set current_bit to the midpoint in our binary search
        current_bit = (left + right) / 2;
    }

    const auto broken_bit = corrupted_points.at(current_bit);
    
    std::cout << "Broken bit position: " << broken_bit.first << ", " << broken_bit.second << "\n";
    return std::nullopt;
}

Day18::Grid Day18::SimulateFallenBytes(const int num_bytes) const
{
    Grid simulated_grid = empty_grid;
    int bytes_fallen = 0;
    for (const auto& byte : corrupted_points)
    {
        if (bytes_fallen >= num_bytes) break;

        const auto [x, y] = byte;
        simulated_grid[y][x] = {.obstacle = Obstacle, .position = {x, y}};
        ++bytes_fallen;
    }
    return simulated_grid;
}

std::pair<Day18::Grid, Day18::Grid> Day18::SimulateThisAndPrevious(int num_bytes) const
{
    auto grid_previous = SimulateFallenBytes(num_bytes - 1);
    auto grid_current = grid_previous;
    const auto [x, y] = corrupted_points.at(num_bytes);
    grid_current[y][x] = {.obstacle = Obstacle, .position = {x, y}};

    return {grid_previous, grid_current};
}

std::vector<Day18::Point> Day18::PathfindThroughGrid(const Grid& grid) const
{
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    const std::pair start = std::make_pair(0, 0);
    const std::pair finish = std::make_pair(rows - 1, cols - 1);

    std::queue<Point> q;
    std::map<Point, Point> parent;
    std::set<Point> visited;

    q.push(start);
    visited.insert(start);

    const std::vector<std::pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if (std::make_pair(x, y) == finish)
        {
            std::vector<Point> path;
            for (auto at = finish; parent.contains(at); at = parent[at])
            {
                path.emplace_back(at);
            }
            path.push_back(start);
            std::ranges::reverse(path);
            return path;
        }

        for (const auto& direction : directions)
        {
            const int new_x = x + direction.first;
            const int new_y = y + direction.second;

            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols)
            {
                const GridObject empty = {.obstacle = Empty, .position = {new_x, new_y}};
                const auto tile = grid[new_x][new_y].value_or(empty);
                if (!visited.contains({ new_x, new_y }) && tile.obstacle != Obstacle)
                {
                    q.emplace(new_x, new_y);
                    visited.insert({ new_x, new_y });
                    parent[{new_x, new_y}] = {x, y};
                }
            }
        }
    }

    return {};
}
