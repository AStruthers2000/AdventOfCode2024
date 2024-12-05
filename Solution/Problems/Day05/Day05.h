#pragma once
#include <map>

#include "../Problem.h"

class Day05 : public Problem
{
public:
    Day05(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 5: Print Queue")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    using UpdateRules = std::map<int, std::vector<int>>;
    using Update = std::vector<int>;

    UpdateRules rules;
    
    std::vector<Update> updates;
    std::vector<Update> ordered_updates;
    std::vector<Update> unorderd_updates;

    bool IsUpdateInOrder(const Update& update) const;
    bool IsPageInOrder(const Update& update, int page_index) const;
    
};




