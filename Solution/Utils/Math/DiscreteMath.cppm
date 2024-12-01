export module Math:DiscreteMath;
import <cstdint>;
import <vector>;

export template <std::integral T> T gcd(T a, T b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

export template <std::integral T> T lcm(T a, T b)
{
    return a * b / gcd(a, b);
}

export template <std::integral T> T lcm(const std::vector<T>& nums)
{
    if (nums.empty()) return 0;

    T result = nums[0];
    for (size_t i = 1; i < nums.size(); ++i)
    {
        result = lcm(result, nums[i]);
    }
    return result;
}


//export template int lcm(const std::vector<int>& nums);
//export template unsigned int lcm(const std::vector<unsigned int>& nums);
//export template uint64_t lcm(const std::vector<uint64_t>& nums);


