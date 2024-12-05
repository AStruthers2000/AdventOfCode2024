#include "Day05.h"

#include <iostream>
#include <ranges>
import StringHelper;
import <string>;
import <algorithm>;

void Day05::LoadProblem()
{
    bool reading_rules = true;
    for (const auto& line : _lines)
    {
        if (line.empty())
        {
            reading_rules = false;
        }
        else if (reading_rules)
        {
            std::vector<std::string> tokens = SplitLineByToken(line, '|');
            rules[std::stoi(tokens[0])].push_back(std::stoi(tokens[1]));
        }
        else
        {
            std::vector<std::string> tokens = SplitLineByToken(line, ',');
            Update pages;
            for (const auto& token : tokens)
            {
                pages.emplace_back(std::stoi(token));
            }
            updates.push_back(pages);
        }
    }
}

std::optional<uint64_t> Day05::SolvePart1()
{
    for (const auto& update : updates)
    {
        if (IsUpdateInOrder(update))
        {
            ordered_updates.emplace_back(update);
        }
    }

    int middle_sum = 0;
    for (const auto& update : ordered_updates)
    {
        const int mid_index = static_cast<int>(update.size()) / 2;
        middle_sum += update[mid_index];
    }
    
    return middle_sum;
}

std::optional<uint64_t> Day05::SolvePart2()
{
    int middle_sum = 0;
    
    for (const auto& update : updates)
    {
        if (!IsUpdateInOrder(update))
        {
            Update unsorted_update(update.begin(), update.end());
            
            //sort the update with the given rules
            std::ranges::sort(unsorted_update, [this, unsorted_update](const int& page1, const int& page2)
            {
                const auto page1_index = *std::ranges::find(unsorted_update, page1);
                const auto page2_index = *std::ranges::find(unsorted_update, page2);

                //if there are rules showing which pages need to be to the right of page 1
                if (rules.contains(page1))
                {
                    const auto left_page_rules = rules.at(page1);

                    //if page 2 is in page 1's rules,
                    if (std::ranges::find(left_page_rules, page2) != std::ranges::end(left_page_rules))
                        //page 1 should be before page 2
                        return true;
                }

                //if there are rules showing which pages need to be to the right of page 2
                if (rules.contains(page2))
                {
                    const auto right_page_rules = rules.at(page2);

                    //if page 1 is in page 2's rules
                    if (std::ranges::find(right_page_rules, page1) != std::ranges::end(right_page_rules))
                        //page 2 should be before page 1
                        return false;
                }

                //if neither of the above have returned yet, we keep the page's ordered the way that they are currently
                return page1_index < page2_index;
            });

            const int mid_index = static_cast<int>(unsorted_update.size()) / 2;
            middle_sum += unsorted_update[mid_index];
        }
    }
    
    return middle_sum;
}

bool Day05::IsUpdateInOrder(const Update& update) const
{
    bool update_in_order = true;
    for (int index = 0; index < update.size(); ++index)
    {
        if (!IsPageInOrder(update, index))
        {
            update_in_order = false;
            break;
        }
    }

    return update_in_order;
}

bool Day05::IsPageInOrder(const Update& update, const int page_index) const
{
    bool page_in_order = true;
    if (rules.contains(update[page_index]))
    {
        for (const auto& other_page : rules.at(update[page_index]))
        {
            const auto other_page_index = std::ranges::find(update, other_page);
            if (other_page_index != std::ranges::end(update))
            {
                auto other_index = other_page_index - update.begin();
                if (other_index < page_index)
                {
                    page_in_order = false;
                }
            }
        }
    }
    return page_in_order;
}