export module Math;

export import :DiscreteMath;

export template <std::integral T> bool IsNumberPowerOfTwo(const T n)
{
    return (n & n - 1) == 0 && n != 0;
}
