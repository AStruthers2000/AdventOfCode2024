#include "Day13.h"

#include <iostream>
#include <ostream>
import StringHelper;
import <string>;
void Day13::LoadProblem()
{
    std::vector<std::vector<std::string>> machines;
    std::vector<std::string> machine_lines;
    for (const auto& line : _lines)
    {
        machine_lines.push_back(line);
        if (line.empty())
        {
            machines.push_back(machine_lines);
            machine_lines.clear();
        }
    }

    machines.push_back(machine_lines);

    for (const auto& machine : machines)
    {
        std::string button_a_line = machine[0];
        std::string button_b_line = machine[1];
        std::string prize_line = machine[2];

        /*//Less SplitLineByToken calls, but splitting on multiple tokens requires regex and that's apparently slower
        const auto better_button_a = SplitLineByToken(button_a_line, {": ", ", ", "+", " "});
        const auto better_button_b = SplitLineByToken(button_b_line, {": ", ", ", "+", " "});
        const auto better_prize = SplitLineByToken(prize_line, {": ", ", ", "=", " "});

        const uint64_t button_a_x = std::stoll(better_button_a[3]);
        const uint64_t button_a_y = std::stoll(better_button_a[5]);
        const uint64_t button_b_x = std::stoll(better_button_b[3]);
        const uint64_t button_b_y = std::stoll(better_button_b[5]);
        const uint64_t prize_x = std::stoll(better_prize[2]);
        const uint64_t prize_y = std::stoll(better_prize[4]);
        */

        //Old splitting method
        std::vector<std::string> button_a_split = SplitLineByToken(button_a_line, " ");
        std::vector<std::string> button_b_split = SplitLineByToken(button_b_line, " ");
        std::vector<std::string> prize_split = SplitLineByToken(prize_line, " ");

        const uint64_t button_a_x = std::stoll(SplitLineByToken(button_a_split[2], "+")[1]);
        const uint64_t button_a_y = std::stoll(SplitLineByToken(button_a_split[3], "+")[1]);
        const uint64_t button_b_x = std::stoll(SplitLineByToken(button_b_split[2], "+")[1]);
        const uint64_t button_b_y = std::stoll(SplitLineByToken(button_b_split[3], "+")[1]);
        const uint64_t prize_x = std::stoll(SplitLineByToken(prize_split[1], "=")[1]);
        const uint64_t prize_y = std::stoll(SplitLineByToken(prize_split[2], "=")[1]);
        

        ClawMachine claw{
            .button_a = std::make_pair(button_a_x, button_a_y),
            .button_b = std::make_pair(button_b_x, button_b_y),
            .prize_location = std::make_pair(prize_x, prize_y)
        };
        claw_machines.push_back(claw);
    }
}

std::optional<uint64_t> Day13::SolvePart1()
{
    uint64_t fewest_tokens = 0;
    for (const auto& machine : claw_machines)
    {
        //std::cout << "Button A: X+" << machine.button_a.first << ", Y+" << machine.button_a.second << "\n";
        //std::cout << "Button B: X+" << machine.button_b.first << ", Y+" << machine.button_b.second << "\n";
        //std::cout << "Prize: X=" << machine.prize_location.first << ", Y=" << machine.prize_location.second << "\n";
        //std::flush(std::cout);

        const auto result = TryWinPrize(machine);
        if (result.has_value())
        {
            const auto [a_press, b_press] = result.value();
            if (a_press >= 100 || b_press >= 100) continue;

            fewest_tokens += 3 * a_press + b_press;
        }
    }
    return fewest_tokens;
}

std::optional<uint64_t> Day13::SolvePart2()
{
    uint64_t fewest_tokens = 0;
    for (const auto& machine : claw_machines)
    {
        //lmao, silly elves
        auto better_machine = machine;
        better_machine.prize_location.first += 1e+13;
        better_machine.prize_location.second += 1e+13;

        const auto result = TryWinPrize(better_machine);
        if (result.has_value())
        {
            const auto [a_press, b_press] = result.value();
            fewest_tokens += 3 * a_press + b_press;
        }
    }
    return fewest_tokens;
}

std::optional<Day13::Point> Day13::TryWinPrize(const ClawMachine& claw_machine)
{
    //uses Cramer's Law to solve a system of linear equations
    //we know that the matrix is invertible and the system has exactly 0 or 1 solutions
    //because the person who made the puzzle inputs is nice
    
    const uint64_t a1 = claw_machine.button_a.first;
    const uint64_t a2 = claw_machine.button_a.second;
    const uint64_t b1 = claw_machine.button_b.first;
    const uint64_t b2 = claw_machine.button_b.second;
    const uint64_t c1 = claw_machine.prize_location.first;
    const uint64_t c2 = claw_machine.prize_location.second;

    //IMPORTANT: these numbers can be negative, so using uint is not a good idea
    const int64_t x_num = static_cast<int64_t>(c1 * b2 - b1 * c2);
    const int64_t y_num = static_cast<int64_t>(a1 * c2 - c1 * a2);
    const int64_t denom = static_cast<int64_t>(a1 * b2 - b1 * a2);

    //avoid divide by zero
    if (denom != 0)
    {
        const int64_t a_press = x_num / denom;
        const int64_t b_press = y_num / denom;

        //because integer division rounds, we also need to validate that we actually get the right prize location
        const uint64_t validate_x = a_press * claw_machine.button_a.first + b_press * claw_machine.button_b.first;
        const uint64_t validate_y = a_press * claw_machine.button_a.second + b_press * claw_machine.button_b.second;

        //if the number of a and b presses are valid, but they don't give us the correct prize location, we can't win
        if (validate_x != claw_machine.prize_location.first || validate_y != claw_machine.prize_location.second)
            return std::nullopt;

        //if the number of a or b presses is invalid, we can't win
        if (a_press < 0 || b_press < 0)
            return std::nullopt;
        
        return std::make_pair(a_press, b_press);
    }

    return std::nullopt;
}
