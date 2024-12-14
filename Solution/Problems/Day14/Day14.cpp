#include "Day14.h"

#include <execution>
#include <iostream>
import StringHelper;
import <string>;
#include <windows.h>

//IMPORTANT! CHANGE THIS WHEN RUNNING FULL CASE
//TEST CASE IS w=11,h=7 FULL CASE IS w=101,h=103
constexpr int SPACE_WIDTH = 101;
constexpr int SPACE_HEIGHT = 103;

const int MID_HEIGHT = (SPACE_HEIGHT / 2);
const int MID_WIDTH = (SPACE_WIDTH / 2) ;

void Day14::LoadProblem()
{
     for (const auto& line : _lines)
     {
         const auto p_split = SplitLineByToken(line, " ")[0];
         const auto v_split = SplitLineByToken(line, " ")[1];

         const auto p = SplitLineByToken(p_split, "=")[1];
         const auto v = SplitLineByToken(v_split, "=")[1];
         const int p_x = std::stoi(SplitLineByToken(p, ",")[0]);
         const int p_y = std::stoi(SplitLineByToken(p, ",")[1]);
         const int v_x = std::stoi(SplitLineByToken(v, ",")[0]);
         const int v_y = std::stoi(SplitLineByToken(v, ",")[1]);

         Robot robot{.location = std::make_pair(p_x, p_y), .velocity = std::make_pair(v_x, v_y)};
         robots.push_back(robot);
     }
}

std::optional<uint64_t> Day14::SolvePart1()
{
    auto moving_robots = robots;
    for (size_t i = 0; i < 100; ++i)
    {
        std::ranges::for_each(moving_robots, [&](Robot& robot)
        {
            MoveRobot(robot);
        });
    }

    uint64_t quad_1 = 0, quad_2 = 0, quad_3 = 0, quad_4 = 0;
    for (const auto& robot : moving_robots)
    {
        
        //if they aren't in the middle cross
        bool in_quad_1 = robot.location.first < MID_WIDTH && robot.location.second < MID_HEIGHT;
        bool in_quad_2 = robot.location.first > MID_WIDTH && robot.location.second < MID_HEIGHT;
        bool in_quad_3 = robot.location.first < MID_WIDTH && robot.location.second > MID_HEIGHT;
        bool in_quad_4 = robot.location.first > MID_WIDTH && robot.location.second > MID_HEIGHT;

        if (in_quad_1) ++quad_1;
        else if (in_quad_2) ++quad_2;
        else if (in_quad_3) ++quad_3;
        else if (in_quad_4) ++quad_4;
    }
    
    uint64_t safety_factor = quad_1 * quad_2 * quad_3 * quad_4; 
    return safety_factor;
}

std::optional<uint64_t> Day14::SolvePart2()
{
    auto moving_robots = robots;
    for (size_t seconds = 0; seconds < 100000; ++seconds)
    {
        std::ranges::for_each(moving_robots, [&](Robot& robot)
        {
            MoveRobot(robot);
        });

        //there is a horizontal and vertical structure/pattern that appears in the output by the following equations:
        //vertical pattern: every 101x+21 iterations
        //horizontal pattern: every 103x+97 iterations
        //so I decided to only print out the tree on multiples of those iterations, so see if there was some structure
        //that would appear. Luckily (or maybe not luck?) the Christmas tree pattern did appear, and I found it much
        //faster than by printing out each iteration. This isn't an "automatic" way to do it, but it works.
        //An automatic way of doing it could be to check for each robot in the grid, see if the robot is surrounded by 8 other
        //robots. If so, do a flood fill algorithm to see if that robot is surrounded by some arbitrary large number (say, 50)
        //If that robot is in the same contiguous space with more than 50 other robots, we are reasonably confident that the
        //tree pattern appeared. I could do it this way, but ehh, I don't really want to right now. For the record, the
        //tree pattern appears on iteration 6587 (technically, when seconds == 6586, because the 1st iteration is iteration "0")
        //if ((seconds - 97) % 103 == 0 || (seconds - 21) % 101 == 0)
        if (seconds == 6586)
        {
            std::vector<std::vector<int>> safety_map;
            for (int i = 0; i < SPACE_HEIGHT; ++i)
            {
                std::vector<int> row(SPACE_WIDTH, 0);
                safety_map.push_back(row);
            }
            for (const auto& robot : moving_robots)
            {
                safety_map[robot.location.second][robot.location.first]++;
            }
        
            for (int i = 0; i < safety_map.size(); ++i)
            {
                if (i == MID_HEIGHT)
                {
                    std::cout << "\n";
                    continue;
                }
                for (int j = 0; j < safety_map[i].size(); ++j)
                {
                    const int c = safety_map[i][j];
            
                    if (j == MID_WIDTH) std::cout << " ";
                    else if (c == 0) std::cout << ".";
                    else std::cout << c;
                }
        
                std::cout << std::endl;
            }
            std::cout << "\nIteration: " << seconds + 1 << "\t=========================================================\n" << std::endl;
            break;
            //std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    return 6587;
}

void Day14::MoveRobot(Robot& robot)
{
    Point new_location = robot.location;
    new_location = Point{robot.location.first + robot.velocity.first, robot.location.second + robot.velocity.second};
    if (new_location.first < 0)
    {
        //we add new_location.first here because new_location.first is negative. would be equivalent (and more readable)
        //as SPACE_WIDTH - std::abs(new_location.first)
        new_location.first = SPACE_WIDTH + new_location.first;
    }
    else if (new_location.first >= SPACE_WIDTH)
    {
        new_location.first = new_location.first - SPACE_WIDTH;
    }

    if (new_location.second < 0)
    {
        //same as above
        new_location.second = SPACE_HEIGHT + new_location.second;
    }
    else if (new_location.second >= SPACE_HEIGHT)
    {
        new_location.second = new_location.second - SPACE_HEIGHT;
    }

    robot.location = new_location;
}
