﻿#pragma once
#include "../Problem.h"

class Day23 : public Problem
{
public:
    Day23(const std::string_view& filename)
        : Problem(filename, std::nullopt)
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;
    
};


