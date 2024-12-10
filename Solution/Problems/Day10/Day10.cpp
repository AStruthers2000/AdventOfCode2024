#include "Day10.h"

#include <queue>
#include <set>
#include <string>

void Day10::LoadProblem()
{
    for (const auto& line : _lines)
    {
        std::vector<int> row;
        for (const auto& c : line)
        {
            row.push_back(c - '0');
        }
        grid.push_back(row);
    }

    for (size_t i = 0; i < grid.size(); ++i)
    {
        for (size_t j = 0; j < grid[i].size(); ++j)
        {
            if (grid[i][j] == 0)
            {
                const auto trail_score = bfs_find_score({i, j});
                const auto trail_rank = bfs_find_rank({i, j});

                //const auto trailhead_rank = static_cast<int>(mountaintops.size());
                trailheads[{i, j}] = {.score = trail_score, .rank = trail_rank};
            }
        }
    }
}

std::optional<uint64_t> Day10::SolvePart1()
{
    int trailhead_ranks = 0;

    for (const auto& trailhead_rank : trailheads | std::views::values)
    {
        trailhead_ranks += trailhead_rank.score;
    }
    
    return trailhead_ranks;
}

std::optional<uint64_t> Day10::SolvePart2()
{
    int trailhead_ranks = 0;

    for (const auto& trailhead_rank : trailheads | std::views::values)
    {
        trailhead_ranks += trailhead_rank.rank;
    }
    
    return trailhead_ranks;
}

int Day10::bfs_find_score(std::pair<int, int> start)
{
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    if (start.first < 0 || start.second >= rows || start.first >= cols || start.second < 0)
    {
        return {};
    }

    std::queue<std::pair<int, int>> q;
    std::set<std::pair<int, int>> visited;

    q.push(start);
    visited.insert(start);

    int target_value = 9;
    int count_targets = 0;

    const std::vector<std::pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if (grid[x][y] == target_value)
        {
            ++count_targets;
            continue;
        }
        
        for (const auto& dir : directions)
        {
            int new_x = x + dir.first;
            int new_y = y + dir.second;

            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols)
            {
                if (!visited.contains({new_x, new_y}) && grid[new_x][new_y] == grid[x][y] + 1)
                {
                    q.push({new_x, new_y});
                    visited.insert({new_x, new_y});
                }
            }
        }
    }
    return count_targets;
}

int Day10::bfs_find_rank(std::pair<int, int> start)
{
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    if (start.first < 0 || start.second >= rows || start.first >= cols || start.second < 0)
    {
        return {};
    }

    std::queue<std::pair<std::pair<int, int>, std::vector<int>>> q;
    std::set<std::pair<int, int>> visited;

    std::vector<std::pair<int, int>> mountaintops;

    q.push({start, {grid[start.first][start.second]}});
    visited.insert(start);

    int target_value = 9;
    int count_targets = 0;

    const std::vector<std::pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!q.empty())
    {
        auto [current, path] = q.front();
        auto [x, y] = current;
        q.pop();

        if (grid[x][y] == target_value)
        {
            mountaintops.emplace_back(x, y);
            ++count_targets;
            continue;
        }
        
        for (const auto& dir : directions)
        {
            int new_x = x + dir.first;
            int new_y = y + dir.second;

            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols)
            {
                if (grid[new_x][new_y] == grid[x][y] + 1)
                {
                    std::vector<int> new_path = path;
                    new_path.push_back(grid[new_x][new_y]);
                    q.push({{new_x, new_y}, new_path});
                }
            }
        }
    }
    return static_cast<int>(mountaintops.size());
}

