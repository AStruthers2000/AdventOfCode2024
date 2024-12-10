#include "Day09.h"

#include <algorithm>
#include <execution>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>

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
        if (space > 0)
            expanded_files.emplace_back(number, space);

        reading_file = !reading_file;
    }
    int x = 0;
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
    const auto sorted_files = SortFiles();

    Disk sorted_disk;
    for (const auto& file : sorted_files)
    {
        for (int i = 0; i < file.size; ++i)
        {
            sorted_disk.push_back(file.id);
        }
    }

    /*std::cout << "Final: ";
    for (const auto& file : sorted_files)
    {
        std::string val;
        if (file.id.has_value()) val = std::to_string(file.id.value());
        else val = ".";

        std::cout << "(" << val << ", " << file.size << "), ";
    }
    std::cout << '\n';*/

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

std::vector<Day09::File> Day09::SortFiles()
{
    std::vector<File> sorted_file{expanded_files.begin(), expanded_files.end()};

    std::vector<File> reverse_files;
    std::ranges::reverse_copy(sorted_file, std::back_inserter(reverse_files));
    for (const auto& read_file : reverse_files)
    {
        if (read_file.id == std::nullopt) continue;
        
        //find the first open position on the left that has size for this file
        const auto write_pos = std::find_if(std::execution::par_unseq, sorted_file.begin(), sorted_file.end(),
            [&](const File& write_file)
            {
                return write_file.size >= read_file.size && !write_file.id.has_value();
            });

        if (write_pos != sorted_file.end())
        {
            //we found a place for the file to go
            const auto empty = *write_pos;
            File empty_consumed{.id = std::nullopt, .size = 0};
            File empty_remaining{.id = std::nullopt, .size = 0};
            
            //the new file will split the empty space
            empty_consumed.size = read_file.size;
            empty_remaining.size = empty.size - empty_consumed.size;

            const auto read_pos = std::find(std::execution::par_unseq, sorted_file.begin(), sorted_file.end(), read_file);
            int write_index = static_cast<int>(std::distance(sorted_file.begin(), write_pos));
            int read_index = static_cast<int>(std::distance(sorted_file.begin(), read_pos));

            if (write_index < read_index)
            {
                sorted_file[write_index] = read_file;
                sorted_file[read_index] = empty_consumed;
                sorted_file.insert(sorted_file.begin() + write_index + 1, empty_remaining);
            }
            
            /* we actually don't need to do this... for some reason. not sure exactly why. 
            //we should combine any adjacent empty spaces and remove any size 0 empty spaces
            std::vector<File> cleaned_files;
            for (size_t i = 0; i < sorted_file.size(); ++i)
            {
                if (sorted_file[i].id.has_value())
                {
                    cleaned_files.push_back(sorted_file[i]);
                }
                else if (!sorted_file[i].id.has_value() && sorted_file[i].size > 0)
                {
                    File empty_space{.id = std::nullopt, .size = sorted_file[i].size};
                    //merge all empty spaces to the right of i together
                    size_t j = i + 1;
                    for (; j < sorted_file.size(); ++j)
                    {
                        if (!sorted_file[j].id.has_value())
                        {
                            empty_space.size += sorted_file[j].size;
                        }
                        else
                        {
                            break;
                        }
                    }
                    i = j - 1;
                    cleaned_files.push_back(empty_space);
                }
            }
            sorted_file = cleaned_files;*/
        }
    }
    
    return sorted_file;
}

