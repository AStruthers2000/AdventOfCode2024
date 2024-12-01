#include "Day1.h"

#include <algorithm>
#include <execution>
#include <iostream>
#include <string>
import StringHelper;

std::optional<uint64_t> Day1::SolvePart1()
{
    ReadAndSort();

    std::vector<uint64_t> distances (left_list.size());
    std::transform(std::execution::par_unseq, left_list.begin(), left_list.end(),
        right_list.begin(), distances.begin(),
        [](const uint64_t left, const uint64_t right)
        {
            return static_cast<uint64_t>(std::abs(static_cast<int>(left - right)));
        });
    
    uint64_t dist_sum = std::reduce(std::execution::par_unseq, distances.begin(), distances.end(), static_cast<uint64_t>(0));

    return dist_sum;
}

std::optional<uint64_t> Day1::SolvePart2()
{
    uint64_t running_sum = 0;
    for(const auto& left_num : left_list)
    {
        uint64_t num_count = 0;
        for(const auto& right_num : right_list)
        {
            if(left_num == right_num)
            {
                ++num_count;
            }
            if(right_num > left_num)
            {
                running_sum += num_count * left_num;
                break;
            }
        }
    }
    return running_sum;
}

void Day1::ReadAndSort()
{
    for(const auto& line : _lines)
    {
        const auto split = SplitLineByToken(line, ' ');
        const uint64_t left_entry = std::stoi(split[0]);
        const uint64_t right_entry = std::stoi(split[split.size()-1]);
        left_list.push_back(left_entry);
        right_list.push_back(right_entry);
    }

    std::ranges::sort(left_list);
    std::ranges::sort(right_list);
}
