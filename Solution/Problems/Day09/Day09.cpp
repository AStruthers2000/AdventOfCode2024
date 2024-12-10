#include "Day09.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <ranges>
#include <stacktrace>

void Day09::LoadProblem()
{
    //there's only 1 line in this problem
    std::string disk = _lines[0];

    bool reading_file = true;
    int file_number = 0;
    for (const auto& c : disk)
    {
        int space = c - '0';
        std::optional<int> number = std::nullopt;
        if (reading_file)
        {
            number = file_number;
            ++file_number;
        }
        
        for (int i = 0; i < space; ++i)
        {
            expanded_disk.emplace_back(number);
        }

        reading_file = !reading_file;
    }
}

std::optional<uint64_t> Day09::SolvePart1()
{
    const auto sorted_disk = SortIndividual();

    uint64_t checksum = 0;
    for (size_t i = 0; i < sorted_disk.size(); ++i)
    {
        if (sorted_disk[i].has_value())
        {
            checksum += static_cast<uint64_t>(i) * sorted_disk[i].value_or(0);
        }
    }
    return checksum;
}

std::optional<uint64_t> Day09::SolvePart2()
{
    // TODO: Implement SolvePart2 logic
    return std::nullopt;
}

Day09::Disk Day09::SortIndividual()
{
    Disk sorted_disk{expanded_disk.begin(), expanded_disk.end()};

    auto write_pos = sorted_disk.begin();
    auto read_pos = sorted_disk.end() - 1;

    while (read_pos > sorted_disk.begin())
    {
        if (read_pos->has_value())
        {
            while (write_pos->has_value()) ++write_pos;
            if (write_pos > read_pos) break;
            
            std::swap(*write_pos, *read_pos);
        }
        --read_pos;
    }

    return sorted_disk;
}
