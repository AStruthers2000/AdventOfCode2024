#include "Day25.h"

#include <iostream>
#include <algorithm>
#include <execution>
import StringHelper;
void Day25::LoadProblem()
{
    std::vector<std::string> input_lines;
   for (const auto& line : _lines)
   {
       if (line.empty())
       {
           process_input_lines(input_lines);
           input_lines.clear();
       }
       else
       {
           input_lines.push_back(line);
       }
   }
    process_input_lines(input_lines);
    input_lines.clear();
}

std::optional<uint64_t> Day25::SolvePart1()
{
    uint64_t valid_fits = 0;
    //for (const auto& lock : locks)
    std::ranges::for_each(locks, [&](auto& lock)
    {
        std::ranges::for_each(keys, [&](auto& key)
        {
            const auto overlaps = count_overlaps(key, lock);
            if (overlaps == 0)
            {
                ++valid_fits;
            }
        });
    });
    return valid_fits;
}

std::optional<uint64_t> Day25::SolvePart2()
{
    // TODO: Implement SolvePart2 logic
    return std::nullopt;
}

void Day25::process_input_lines(const std::vector<std::string>& lines)
{
    bool is_lock = IsVectorEntirelyN(lines[0], '#');
    std::vector<int> heights;
    for (size_t i = 0; i < lines[0].size(); ++i)
    {
        heights.push_back(count_occurrences_in_column(lines, '#', i) - 1);
    }
    is_lock ? locks.push_back({.lock_heights = heights}) : keys.push_back({.key_heights = heights});
}

int Day25::count_occurrences_in_column(const std::vector<std::string>& strings, const char target, const size_t column)
{
    int count = 0;

    // Check if the column index is valid
    if (strings.empty() || column >= strings[0].size()) {
        std::cerr << "Invalid column index." << std::endl;
        return -1; // Return -1 to indicate an error
    }

    for (const auto& str : strings) {
        // Ensure all strings are of equal length
        if (str.size() != strings[0].size()) {
            std::cerr << "Strings are not of equal length." << std::endl;
            return -1; // Return -1 to indicate an error
        }

        if (str[column] == target) {
            ++count;
        }
    }

    return count;
}

int Day25::count_overlaps(Key key, Lock lock) const
{
    int overlaps = 0;
    for (int i = 0; i < static_cast<int>(key.key_heights.size()); ++i)
    {
        const auto key_height = key.key_heights[i];
        const auto lock_height = lock.lock_heights[i];

        if (key_height + lock_height > 5) ++overlaps;
    }

    return overlaps;
}
