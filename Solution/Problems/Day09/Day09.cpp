#include "Day09.h"

#include <algorithm>
#include <ranges>

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
    int x =0;
}

std::optional<uint64_t> Day09::SolvePart1()
{
    // TODO: Implement SolvePart1 logic
    const auto disk = SortIndividual();
    return std::nullopt;
}

std::optional<uint64_t> Day09::SolvePart2()
{
    // TODO: Implement SolvePart2 logic
    return std::nullopt;
}

Day09::Disk Day09::SortIndividual()
{
    Disk sorted_disk = expanded_disk;

    /*
    //const auto write_pos = std::ranges::find_if(sorted_disk,
    //                                              [](const std::optional<int>& entry){return entry == std::nullopt;});
    const auto write_pos = std::find(sorted_disk.begin(), sorted_disk.end(), std::nullopt);
    const auto read_pos = std::ranges::find_if(std::ranges::reverse_view(sorted_disk), [](const std::optional<int>& entry){return entry != std::nullopt;});

    //if the disk is full, we have a problem
    //if (first_empty == sorted_disk.end()) return {};


    while (read_pos.base() != sorted_disk.begin())
    {
        if (read_pos->has_value())
        {
            std::optional<int> entry = *read_pos;
            sorted_disk.insert(write_pos, entry);
            sorted_disk.insert(read_pos.base(), std::nullopt);
        }

        --read_pos.base();
    }
    */

    int write_pos = 0;

    // Find the first nullopt position for writing
    while (write_pos < sorted_disk.size() && sorted_disk[write_pos].has_value()) {
        ++write_pos;
    }

    // Traverse the vector from the end
    for (int read_pos = sorted_disk.size() - 1; read_pos >= 0; --read_pos) {
        if (sorted_disk[read_pos].has_value() && write_pos < read_pos) {
            // Move the element
            sorted_disk[write_pos] = sorted_disk[read_pos];
            sorted_disk[read_pos] = std::nullopt;

            // Find the next nullopt position
            do {
                ++write_pos;
            } while (write_pos < sorted_disk.size() && sorted_disk[write_pos].has_value());
        }
    }

    return sorted_disk;
}
