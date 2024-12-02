#include "Day02.h"

#include <ranges>
import StringHelper;
import <string>;
import <algorithm>;

void Day02::LoadProblem()
{
    for (const auto& line : _lines)
    {
        const auto split = SplitLineByToken(line, ' ');
        std::vector<uint64_t> numbers;
        for (const auto& token : split)
        {
            numbers.emplace_back(std::stoi(token));
        }
        report_levels.emplace(numbers, 999);
    }
    CalculateSafetyFactor();
}

std::optional<uint64_t> Day02::SolvePart1()
{
    int safety_count = 0;
    for (const auto& report_level : report_levels | std::ranges::views::values)
    {
        if (report_level == 0)
        {
            ++safety_count;
        }
    }
    return safety_count;
}

std::optional<uint64_t> Day02::SolvePart2()
{
    int safety_count = 0;
    for (const auto& report_level : report_levels | std::ranges::views::values)
    {
        if (report_level == 0 || report_level == 1)
            ++safety_count;
    }
    return safety_count;
}

void Day02::CalculateSafetyFactor()
{
    for (const auto& report : report_levels | std::ranges::views::keys)
    {
        if (CheckSafety(report))
        {
            report_levels[report] = 0;
        }
        else
        {
            for (size_t i = 0; i < report.size(); ++i)
            {
                auto new_report = report;
                new_report.erase(new_report.begin() + i);
                if (CheckSafety(new_report))
                {
                    report_levels[report] = 1;
                    break;
                }
            }
        }
    }
}

bool Day02::CheckSafety(const std::vector<uint64_t>& safety_factors)
{
    auto report_ascending = safety_factors;
    auto report_descending = safety_factors;
    //could have done the copying this way as well (slower but probably safer):
    //std::ranges::copy(safety_factors, std::back_inserter(report_ascending));
    //std::ranges::copy(safety_factors, std::back_inserter(report_descending));
    
    std::ranges::sort(report_ascending, std::less<>());
    std::ranges::sort(report_descending, std::greater<>());

    if (std::ranges::equal(safety_factors, report_ascending)
        || std::ranges::equal(safety_factors, report_descending))
    {
        for (size_t i = 0; i < safety_factors.size() - 1; ++i)
        {
            const auto elem_dist = std::abs(static_cast<int>(safety_factors[i] - safety_factors[i + 1]));
            if (elem_dist < 1 || elem_dist > 3)
            {
                return false;
            }
        }
        return true;
    }

    return false;
}
