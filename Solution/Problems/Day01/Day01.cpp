#include "Day01.h"

#include <algorithm>
#include <execution>
#include <iostream>
#include <string>
import StringHelper;
import Math;

void Day01::LoadProblem()
{
    for(const auto& line : _lines)
    {
        const auto split = SplitLineByToken(line, ' ');
        const auto int_split = ConvertStringVectorToIntegral<uint64_t>(split);
        if (int_split.has_value())
        {
            const uint64_t left_entry = int_split.value()[0];
            const uint64_t right_entry = int_split.value()[1];
            left_list.push_back(left_entry);
            right_list.push_back(right_entry);
        }
    }

    std::ranges::sort(left_list);
    std::ranges::sort(right_list);
}

//Parallel solution is technically slower, even though it is more interesting. #overhead
std::optional<uint64_t> Day01::SolvePart1()
{
    /*
    uint64_t dist_sum = 0;
    for(size_t i = 0; i < left_list.size(); i++)
    {
        const uint64_t left = left_list[i];
        const uint64_t right = right_list[i];

        //const auto dist = std::abs(static_cast<int>(left - right));
        dist_sum += UnsignedDistance(left, right).distance;
    }
    */
    
    std::vector<uint64_t> distances (left_list.size());
    std::transform(std::execution::par_unseq, left_list.begin(), left_list.end(),
        right_list.begin(), distances.begin(),
        [](const uint64_t left, const uint64_t right)
        {
            return UnsignedDistance(left, right).distance;
        });
    
    uint64_t dist_sum = std::reduce(std::execution::par_unseq, distances.begin(), distances.end(), static_cast<uint64_t>(0));
    
    return dist_sum;
}

std::optional<uint64_t> Day01::SolvePart2()
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
