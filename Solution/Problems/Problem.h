#pragma once
#include <optional>
#include <string_view>
#include <vector>

class Problem
{
public:
    virtual ~Problem() = default;
    Problem(std::string_view file_name, const std::optional<std::string_view>& problem_name);

    void Solve(int mode);

protected:
    virtual void LoadProblem() = 0;
    virtual std::optional<uint64_t> SolvePart1() = 0;
    virtual std::optional<uint64_t> SolvePart2() = 0;

    std::vector<std::string> _lines;

private:
    std::string_view _problem_name;
};
