export module Math;

export import :DiscreteMath;

export template <std::integral T> bool IsNumberPowerOfTwo(const T n)
{
    return (n & n - 1) == 0 && n != 0;
}

export template <std::integral T> struct Distance
{
    T distance;
    int sign;
};

export template <std::integral T> Distance<T> UnsignedDistance(T x, T y)
{
    Distance<T> dist;
    dist.distance = static_cast<T>(std::abs(static_cast<int>(x - y)));
    dist.sign = 0;

    return dist;
}

export template <std::integral T> Distance<T> SignedDistance(T x, T y)
{
    auto dist = UnsignedDistance(x, y);
    dist.sign = x < y ? 1 : -1;

    return dist;
}