#pragma once
#include "../Problem.h"

class Day25 : public Problem
{
public:
    Day25(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 25: Code Chronicle")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    struct Key
    {
        std::vector<int> key_heights;
    };

    struct Lock
    {
        std::vector<int> lock_heights;
    };

    std::vector<Key> keys;
    std::vector<Lock> locks;

    void process_input_lines(const std::vector<std::string>& lines);
    int count_occurrences_in_column(const std::vector<std::string>& strings, char target, size_t column);
    int count_overlaps(Key key, Lock lock) const;
};


