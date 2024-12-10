#pragma once
#include <map>

#include "../Problem.h"

class Day10 : public Problem
{
public:
    Day10(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 10: Hoof It")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;


private:
    struct TrailheadEvaluation
    {
        int score;
        int rank;
    };
    std::vector<std::vector<int>> grid;
    std::map<std::pair<int, int>, TrailheadEvaluation> trailheads;

    int bfs_find_score(std::pair<int, int> start);
    int bfs_find_rank(std::pair<int, int> start);
};

