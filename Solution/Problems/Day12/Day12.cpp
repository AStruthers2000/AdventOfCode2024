#include "Day12.h"

#include <execution>
#include <iostream>
#include <queue>

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
            /*
            int interior_corners = 0;

            enum PerimeterPiece : uint8_t {Edge, Corner, Plant};
            std::map<Point, PerimeterPiece> pieces;
            std::map<Point, int> edge_counts;
            for (const auto& p : perimeter)
            {
                const Point pt = p.first;
                edge_counts[pt]++;
                
                //if (pieces.contains(pt) && pieces[pt] == Edge)
                //{
                //    pieces[pt] = Corner;
                //}
                //else
                //{
                    pieces[pt] = Edge;
                //}

                
                switch (p.second)
                {
                case above:
                case below:
                    if (!pieces.contains({pt.first, pt.second - 1})) pieces[{pt.first, pt.second - 1}] = Corner;
                    if (!pieces.contains({pt.first, pt.second + 1})) pieces[{pt.first, pt.second + 1}] = Corner;
                    break;
                case left:
                case right:
                    if (!pieces.contains({pt.first - 1, pt.second })) pieces[{pt.first - 1, pt.second}] = Corner;
                    if (!pieces.contains({pt.first + 1, pt.second })) pieces[{pt.first + 1, pt.second}] = Corner;
                    break;
                }
                
            }

            for (const auto& p : plot)
            {
                pieces[p] = Plant;
            }

            int exterior_corners = static_cast<int>(std::ranges::count_if(pieces, [&](const std::pair<Point, PerimeterPiece>& piece) {return piece.second == Corner;}));
            //corners += interior_corners;
            int edges = exterior_corners;
            */
            //total_cost += area * edges;
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

    
        //{1, 0}, {0, -1}, {-1, 0}};

    //int perimeter = 0;
    std::set<std::pair<Point, Direction>> perimeter;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        //for (const auto& dir : directions)
        std::ranges::for_each(directions, [&](const auto& direction)
        {
            int new_x = x + direction.first.first;
            int new_y = y + direction.first.second;

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
                //++perimeter;
                perimeter.emplace(std::make_pair(new_x, new_y), direction.second);
            }
        });
    }

    //std::cout << "Perimeter for plot " << plant_type << " is " << perimeter.size() << std::endl;

    const GardenPlot plot = {visited, perimeter};
    return {visited, perimeter};
}
