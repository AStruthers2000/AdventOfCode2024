#pragma once
#include <optional>
#include <string_view>
#include <vector>

class Problem
{
public:
    Problem(std::string_view filename);

    void Solve();

protected:
    virtual std::optional<uint64_t> SolvePart1() = 0;
    virtual std::optional<uint64_t> SolvePart2() = 0;

    std::vector<std::string> lines;
};
