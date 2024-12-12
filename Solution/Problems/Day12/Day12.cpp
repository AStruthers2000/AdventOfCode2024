#include "Day12.h"

#include <execution>
#include <iostream>
#include <queue>
#include <unordered_map>

void Day12::LoadProblem()
{
    for (const auto& line : _lines)
    {
        std::vector<char> garden_row;
        for (const auto& c : line)
        {
            garden_row.push_back(c);
        }
        garden.push_back(garden_row);
    }

    std::set<std::pair<int, int>> plants_already_analyzed;

    for (int i = 0; i < static_cast<int>(garden.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(garden[i].size()); ++j)
        {
            if (!plants_already_analyzed.contains({i, j}))
            {
                const char plant_type = garden[i][j];
                const auto garden_plot = flood_fill({i, j}, plant_type);
                if (!plots[plant_type].contains(garden_plot))
                {
                    plots[plant_type].insert(garden_plot);
                    plants_already_analyzed.insert_range(garden_plot.first);
                }
            }
        }
    }
}

std::optional<uint64_t> Day12::SolvePart1()
{
    uint64_t total_cost = 0;
    for (const auto& plot_set : plots | std::views::values)
    {
        for (const auto& [plot, perimeter] : plot_set)
        {
            const auto area = plot.size();
            total_cost += area * perimeter.size();
        }
    }
    return total_cost;
}

std::optional<uint64_t> Day12::SolvePart2()
{
    uint64_t total_cost = 0;
    for (const auto& plot_set : plots | std::views::values)
    {
        for (const auto& [plot, perimeter] : plot_set)
        {
            const auto area = plot.size();

            int side_count = 0;

            //check every side in the perimeter. if there is a valid side directly to the relative "left" of this side,
            //then this side shouldn't be counted in the side_count, because this side is part of a contiguous group of sides
            //however, if there isn't a valid side directly to the relative "left" of this side, this is the "leftmost"
            //side of group of one or more contiguous edges, so we increment the side_count counter
            for (const auto& [side, direction] : perimeter)
            {
                //get the relative "left" of the current side's direction
                const auto look_dir = direction;
                auto left_dir = look_dir;
                --left_dir;

                //calculate where the relative "left" would be, if it were to exist
                const auto left_side = std::make_pair(side.first + directions_map[left_dir].first, side.second + directions_map[left_dir].second);

                //check to see if the relative "left" exists in the perimeter. if it doesn't exist, we are on the "leftmost"
                //edge of a group of one or more contiguous edges
                if (!perimeter.contains({left_side, direction}))
                    ++side_count;
            }

            //cost per plot is the area * the side count
            total_cost += area * side_count;
        }
    }
    return total_cost;
}

Day12::GardenPlot Day12::flood_fill(Point start, char plant_type)
{
    int rows = static_cast<int>(garden.size());
    int cols = static_cast<int>(garden[0].size());

    if (start.first < 0 || start.first >= rows || start.second < 0 || start.second >= cols)
    {
        return {};
    }

    std::queue<Point> q;
    std::set<Point> visited;

    q.push(start);
    visited.insert(start);
    
    std::set<std::pair<Point, Plant_Direction>> perimeter;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        std::ranges::for_each(directions_map, [&](const std::pair<Plant_Direction, Point>& direction)
        {
            auto [dir, vec] = direction;
            int new_x = x + vec.first;
            int new_y = y + vec.second;

            bool cant_visit = true;
            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols)
            {
                if (garden[new_x][new_y] == plant_type)
                {
                    cant_visit = false;
                    if (!visited.contains({ new_x, new_y }))
                    {
                        q.emplace(new_x, new_y);
                        visited.insert({ new_x, new_y });
                    }
                }
            }
            
            if (cant_visit)
            {
                perimeter.emplace(std::make_pair(new_x, new_y), dir);
            }
        });
    }
    
    const GardenPlot plot = {visited, perimeter};
    return {visited, perimeter};
}