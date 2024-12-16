#include "Day16.h"

#include <iostream>
#include <map>
#include <queue>

void Day16::LoadProblem()
{
    for (size_t i = 0; i < _lines.size(); ++i)
    {
        std::vector<Tile> row;
        for (size_t j = 0; j < _lines[i].size(); ++j)
        {
            const auto t = _lines[i][j];
            Tile tile;
            tile.position = std::make_pair(static_cast<int>(i), static_cast<int>(j));
            switch (t)
            {
            case '.':
                tile.tile = Empty;
                break;
            case '#':
                tile.tile = Wall;
                break;
            case 'S':
                tile.tile = Start;
                start = tile;
                break;
            case 'E':
                tile.tile = Finish;
                finish = tile;
                break;
            default: break;
            }
            
            row.push_back(tile);
        }
        map.push_back(row);
    }
}

std::optional<uint64_t> Day16::SolvePart1()
{
    const auto path = GetPathThroughMap(start.position);

    int cost = path.second;
    const auto tiles = path.first;
    
    //pathfinding doesn't appropriately account for the starting rotation, so we need to check to see if the first tile
    //in the path is above us, or to the right of us
    const auto first_tile = path.first.begin();
    const auto delta = std::make_pair(first_tile->position.first - start.position.first, first_tile->position.second - start.position.second);
    if (delta == std::make_pair(0, 1))
    {
        cost -= 1000;
    }
        
    
    
    //PrintMap();
    return cost;
}

std::optional<uint64_t> Day16::SolvePart2()
{
    // TODO: Implement SolvePart2 logic
    return std::nullopt;
}

std::pair<std::vector<Day16::Tile>, int> Day16::GetPathThroughMap(std::pair<int, int> start_position)
{
    const int rows = static_cast<int>(map.size());
    const int cols = static_cast<int>(map[0].size());

    if (start_position.first < 0 || start_position.second >= rows || start_position.first >= cols || start_position.second < 0)
    {
        return {};
    }

    const int TURN_COST = 1000;
    const int MOVE_COST = 1;

    std::priority_queue<PathfindingState, std::vector<PathfindingState>, std::greater<>> pq;
    std::map<std::pair<int, int>, int> min_cost;
    int new_cost = 0;
    //std::queue<std::pair<int, int>> q;
    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    //std::set<Tile> visited;

    pq.push({start_position, 0, {0, 1}});
    min_cost[start_position] = 0;
    parent[start_position] = {-1, -1};
    //visited.insert(map[start_position.first][start_position.second]);

    const std::vector<std::pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::pair<int, int> finish_position{-1, -1};
    while (!pq.empty())
    {
        auto [current_position, current_cost, current_direction] = pq.top();
        auto [x, y] = current_position;
        pq.pop();

        if (map[x][y].tile == Finish)
        {
            finish_position = current_position;
            break;
        }

        //std::ranges::for_each(directions, [&](const auto& direction)
        for (const auto& direction : directions)
        {
            const int next_x = x + direction.first;
            const int next_y = y + direction.second;

            if (next_x >= 0 && next_x < rows && next_y >= 0 && next_y < cols)
            {
                const Tile& next_tile = map[next_x][next_y];
                if (next_tile.tile == Wall) continue;

                new_cost = current_cost + MOVE_COST;
                if (current_direction != std::pair(0, 0) && current_direction != direction)
                {
                    new_cost += TURN_COST;
                }

                //only update if the new cost is better
                if (!min_cost.contains({next_x, next_y}) || new_cost < min_cost[{next_x, next_y}])
                {
                    min_cost[{next_x, next_y}] = new_cost;
                    pq.push({{next_x, next_y}, new_cost, direction});
                    parent[{next_x, next_y}] = {x, y};
                }
            }
        }
    }

    //no path found to the finish
    if (finish_position == std::make_pair(-1, -1))
    {
        return {};
    }

    std::vector<Tile> path;
    for (auto at = finish_position; at != std::pair(-1, -1); at = parent[at])
    {
        //std::cout << at.first << " " << at.second << std::endl;
        path.push_back(map[at.first][at.second]);
        map[at.first][at.second].tile = Path;
    }
    path.pop_back();
    std::ranges::reverse(path);

    return {path, new_cost};
}

void Day16::PrintMap()
{
    for (const auto& row : map)
    {
        for (const auto& tile : row)
        {
            switch (tile.tile)
            {
            case Wall:
                std::cout << "#";
                break;
            case Start:
                std::cout << "S";
                break;
            case Finish:
                std::cout << "E";
                break;
            case Empty:
                std::cout << ".";
                break;
            case Path:
                std::cout << "^";
                break;
            }
        }
        std::cout << "\n";
    }
}