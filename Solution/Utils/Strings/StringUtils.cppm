export module StringHelper;

import <string>;
import <algorithm>;
import <map>;
import <vector>;

export template <typename T> bool IsVectorEntirelyN(const std::vector<T>& v, const T& n)
{
    return all_of(v.begin(), v.end(), [n](const T c){return c == n; });
}

export bool IsVectorEntirelyN(const std::string& v, const char& n);

export int CountOccurenceInString(const std::string& str, const char& c);

export bool ContainsSubstring(const std::string& str, const std::string& sub);

export std::vector<std::string> SplitLineByToken(const std::string& line, const char token);

export std::vector<std::string> SplitLineByToken(const std::string& line, const std::string& token);
export std::vector<std::string> SplitLineByToken(const std::string& line, const std::vector<std::string>& tokens);

export bool ContainsOnlyDigits(const std::string& str);

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

export enum Direction : uint8_t
{
    Up,
    Down,
    Left,
    Right,
    Diag_Up_Left,
    Diag_Up_Right,
    Diag_Down_Left,
    Diag_Down_Right
};

export std::map<Direction, std::optional<std::string>> BuildStringsFromGrid(
        const std::vector<std::vector<char>>& grid, std::pair<int, int> position, int length);

export std::map<Direction, std::optional<char>> GetSurroundingElements(
    const std::vector<std::vector<char>>& grid, std::pair<int, int> position);



