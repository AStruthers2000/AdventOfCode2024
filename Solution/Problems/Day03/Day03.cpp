#include "Day03.h"

import StringHelper;
#include <execution>
import <string>;

void Day03::LoadProblem()
{
    bool can_multiply = true;
    for (const auto& line : _lines)
    {
        const auto good_split = SplitLineByToken(line, std::vector<std::string>{"mul(", ")"});
        for (const auto& token : good_split)
        {
            //since we now have a candidate string that exists between a "mul(" and ")", we want to try and split this
            //string by ',', since all *valid* command numbers are going to be in the form "xxx,yyy" at this point
            const auto hopeful_mul = SplitLineByToken(token, ",");

            //if we have exactly two elements (i.e. not "xxx,yyy,zzz" or "xxx"), and the left element and right elements
            //contain only digits (i.e. not "12a3,456" or "abc,!@#"), then we have two valid numbers between "mul(" and ")"
            if (hopeful_mul.size() == 2 && ContainsOnlyDigits(hopeful_mul[0]) && ContainsOnlyDigits(hopeful_mul[1]))
            {
                //convert these numbers to ints, and add the pair of them to mul_pairs vector
                const auto left_val = std::stoi(hopeful_mul[0]);
                const auto right_val = std::stoi(hopeful_mul[1]);
                mul_pairs.push_back(std::make_pair(left_val, right_val));

                //if we are currently able to multiply, add the pair of them to the enabled_mul_pairs vector
                if (can_multiply)
                {
                    enabled_mul_pairs.push_back(std::make_pair(left_val, right_val));
                }
            }
            //this piece of logic happens at the END of checking for valid "mul(xxx,yyy)" sequences, because we 
            //guarantee that "do" or "don't" are contained as the LAST characters in each token string
            //(see above outside for loop for the reasoning). we also must check to see if the token contains "don't"
            //first, because the substring "do" is contained in the substring "don't" lol
            else if (token.ends_with("do("))
            {
                can_multiply = true;
            }
            else if (token.ends_with("don't("))
            {
                can_multiply = false;
            }
            
        }

        /*
        //split into groups by the token () so that we can get a separate string for each "do()" or "don't()"
        //because only the command "do()" or "don't()" is valid, not something like "do( )" or "don't(_123)"
        //splitting on "()" will also inherently make each token in peren_split have "do" or "don't" as the last characters
        const auto peren_split = SplitLineByToken(line, "()");
        for (const auto& token : peren_split)
        {
            //find each token that starts with "mul(", because this is the first condition that must be true to have a valid
            //multiply command
            for (const auto& mul_token : SplitLineByToken(token, "mul("))
            {
                //shear off any characters to the "right" of the close peren, because we don't care about those
                const auto split2 = SplitLineByToken(mul_token, ')');
    
                //the element in index 0 will be whatever substring is contained between "mul(" and ")" in our string
                const auto first = split2[0];
    
                //since we now have a candidate string that exists between a "mul(" and ")", we want to try and split this
                //string by ',', since all valid command numbers are going to be in the form "xxx,yyy" at this point
                const auto hopeful_mul = SplitLineByToken(first, ",");
    
                //if we have exactly two elements (i.e. not "xxx,yyy,zzz" or "xxx"), and the left element and right elements
                //contain only digits (i.e. not "12a3,456" or "abc,!@#"), then we have two valid numbers between "mul(" and ")"
                if (hopeful_mul.size() == 2 && ContainsOnlyDigits(hopeful_mul[0]) && ContainsOnlyDigits(hopeful_mul[1]))
                {
                    //convert these numbers to ints, and add the pair of them to mul_pairs vector
                    const auto left_val = std::stoi(hopeful_mul[0]);
                    const auto right_val = std::stoi(hopeful_mul[1]);
                    mul_pairs.push_back(std::make_pair(left_val, right_val));
    
                    //if we are currently able to multiply, add the pair of them to the enabled_mul_pairs vector
                    if (can_multiply)
                    {
                        enabled_mul_pairs.push_back(std::make_pair(left_val, right_val));
                    }
                }
            }
    
            //this piece of logic happens at the END of checking for valid "mul(xxx,yyy)" sequences, because we 
            //guarantee that "do" or "don't" are contained as the LAST characters in each token string
            //(see above outside for loop for the reasoning). we also must check to see if the token contains "don't"
            //first, because the substring "do" is contained in the substring "don't" lol
            if (ContainsSubstring(token, "don't"))
            {
                can_multiply = false;
            }
            else if (ContainsSubstring(token, "do"))
            {
                can_multiply = true;
            }
        }
        */
    }
}

std::optional<uint64_t> Day03::SolvePart1()
{
    /*int sum = 0;
    for (const auto& mul : mul_pairs)
    {
        sum += mul.first * mul.second;
    }*/

    /*std::vector<int> result(mul_pairs.size());
    std::transform(std::execution::par_unseq, mul_pairs.begin(), mul_pairs.end(), result.begin(), [](auto pair){return pair.first * pair.second;});*/

    /*auto result = mul_pairs | std::ranges::views::transform([](auto pair){return pair.first * pair.second;});
    auto sum = std::ranges::fold_left(result, 0, [](const int acc, const int x){return acc + x;});*/

    std::vector<int> result(mul_pairs.size());
    std::ranges::transform(mul_pairs, result.begin(), [](auto pair){return pair.first * pair.second;});
    auto sum = std::ranges::fold_left(result, 0, [](const int acc, const int x){return acc + x;});

    return sum;
}

std::optional<uint64_t> Day03::SolvePart2()
{
    /*int sum = 0;
    for (const auto& mul : enabled_mul_pairs)
    {
        sum += mul.first * mul.second;
    }*/
    
    /*std::vector<int> result(mul_pairs.size());
    std::transform(std::execution::par_unseq, enabled_mul_pairs.begin(), enabled_mul_pairs.end(), result.begin(), [](auto pair){return pair.first * pair.second;});
    auto sum = std::reduce(std::execution::par_unseq, result.begin(), result.end(), 0);*/

    std::vector<int> result(enabled_mul_pairs.size());
    std::ranges::transform(enabled_mul_pairs, result.begin(), [](auto pair){return pair.first * pair.second;});
    auto sum = std::ranges::fold_left(result, 0, [](const int acc, const int x){return acc + x;});

    return sum;
}
