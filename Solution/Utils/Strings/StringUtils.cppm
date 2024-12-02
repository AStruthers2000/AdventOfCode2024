export module StringHelper;

import <string>;
import <algorithm>;
import <vector>;

export template <typename T> bool IsVectorEntirelyN(const std::vector<T>& v, const T& n)
{
    return all_of(v.begin(), v.end(), [n](const T c){return c == n; });
}

export bool IsVectorEntirelyN(const std::string& v, const char& n);

export int CountOccurenceInString(const std::string& str, const char& c);

export std::vector<std::string> SplitLineByToken(const std::string& line, const char token);

//export template <std::integral T> std::vector<T> ConvertStringVectorToIntegral(const std::vector<std::string>& v);

export template <std::integral T>
std::optional<std::vector<T>> ConvertStringVectorToIntegral(const std::vector<std::string>& v)
{
    std::vector<T> numbers;
    for (const auto& token : v)
    {
        try
        {
            const auto number = static_cast<T>(std::stoi(token));
            numbers.emplace_back(number);
        }catch ([[maybe_unused]] std::exception& e)
        {
            continue;
        }
    }
    return numbers;
} 



