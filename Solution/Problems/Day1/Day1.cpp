#include "Day1.h"

#include <algorithm>
#include <iostream>
#include <string>
import StringHelper;

std::optional<uint64_t> Day1::SolvePart1()
{
    ReadAndSort();
    uint64_t dist_sum = 0;
    for(size_t i = 0; i < left_list.size(); i++)
    {
        const uint64_t left = left_list[i];
        const uint64_t right = right_list[i];

        const auto dist = std::abs(static_cast<int>(left - right));
        dist_sum += dist;
    }
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
    for(const auto& line : lines)
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
