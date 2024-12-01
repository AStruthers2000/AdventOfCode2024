//import std;
import FileParsing;
import StringHelper;
import Math;

#include <iostream>
import <string>;
import <vector>;

int main(int argc, char* argv[])
{
    const std::string filename = "test.txt";
    auto lines = ReadFromFile(filename.c_str());

    const auto x = CountOccurenceInString("Hello world 2024, xxx!", '2');

    const auto AllX = IsVectorEntirelyN("hello world", 'x');
    const auto NowAllX = IsVectorEntirelyN("xxxxx", 'x');
    const auto whataboutnow = IsVectorEntirelyN({1,2,3,4,5}, 5);
    const auto definitely = IsVectorEntirelyN({4,4,4,4,4,4,4,4}, 4);

    const auto n64_t = gcd<uint64_t>(5, 20);
    const auto n = gcd(5, 20);
    const auto t = lcm(10, 91);
    const auto t_t = lcm(std::vector<int>{9, 10, 11});

    const auto split = SplitLineByToken("hello world this is a split up string", ' ');

    const auto is2 = IsNumberPowerOfTwo(2);
    const auto big120 = IsNumberPowerOfTwo<uint64_t>(128);
    const auto probablynot = IsNumberPowerOfTwo<unsigned long>(333333333);
    
    return 0;
}
