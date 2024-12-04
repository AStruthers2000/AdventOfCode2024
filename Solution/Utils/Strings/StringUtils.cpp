module;
#include <regex>
module StringHelper;

//import <fstream>;
//#include <sstream>
import <algorithm>;


int CountOccurenceInString(const std::string& str, const char& c)
{
    //static_assert(std::is_convertible_v<T, Target>, "Type is not convertable");
    //const char c_t = static_cast<char>('0' + c);
    const int count = static_cast<int>(std::count(str.begin(), str.end(), c));
    return count;
}

bool ContainsSubstring(const std::string& str, const std::string& sub)
{
    return str.find(sub) != std::string::npos;
}

bool IsVectorEntirelyN(const std::string& v, const char& n)
{
    const std::vector<char> v_t(v.begin(), v.end());
    return IsVectorEntirelyN(v_t, n);
}

std::vector<std::string> SplitLineByToken(const std::string& line, const char token)
{
    std::vector<std::string> result;

    // Use std::string_view for efficient splitting
    //std::string_view line_view = line;
    size_t start = 0;
    size_t end;

    // Split by the token
    while ((end = line.find(token, start)) != std::string_view::npos)
    {
        result.emplace_back(line.substr(start, end - start));
        start = end + 1;
    }

    // Add the last token (if any)
    result.emplace_back(line.substr(start));

    return result;
}

std::vector<std::string> SplitLineByToken(const std::string& line, const std::string& token)
{
    std::vector<std::string> result;
    size_t start = 0;
    size_t end;

    while ((end = line.find(token, start)) != std::string::npos) {
        result.emplace_back(line.substr(start, end - start));
        start = end + token.length();
    }

    // Add the last segment after the final token
    result.emplace_back(line.substr(start));
    
    return result;
}

std::string regexEscape(const std::string& str) {
    static const std::string regexSpecialChars = R"([.^$|(){}*+?\\])";
    std::string escaped;
    for (char c : str) {
        if (regexSpecialChars.find(c) != std::string::npos) {
            escaped += '\\'; // Escape special characters
        }
        escaped += c;
    }
    return escaped;
}

std::vector<std::string> SplitLineByToken(const std::string& line, const std::vector<std::string>& tokens)
{
    
    std::string regexPattern;
    for (size_t i = 0; i < tokens.size(); ++i) {
        regexPattern += regexEscape(tokens[i]);
        if (i != tokens.size() - 1) {
            regexPattern += "|";
        }
    }

    // Use regex to split the string
    std::regex tokenRegex(regexPattern);
    std::sregex_token_iterator iter(line.begin(), line.end(), tokenRegex, -1);
    std::sregex_token_iterator end;

    // Collect and return the results
    std::vector<std::string> result;
    for (; iter != end; ++iter) {
        if (!iter->str().empty()) {
            result.push_back(*iter);
        }
    }

    return result;
}

bool ContainsOnlyDigits(const std::string& str)
{
    return !str.empty() && std::ranges::all_of(str, ::isdigit);
}

std::map<Direction, std::optional<std::string>> BuildStringsFromGrid(
    const std::vector<std::vector<char>>& grid, std::pair<int, int> position, const int length)
{
    using std::optional;
    using std::string;

    std::map<Direction, optional<string>> result;

    const auto rows = static_cast<int>(grid.size());
    const auto cols = static_cast<int>(rows > 0 ? grid[0].size() : 0);

    // Lambda to check if a position is within grid bounds
    auto is_valid_position = [&](const int row, const int col)
    {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    };

    // Lambda to construct a string in a given direction
    auto constructString = [&](const int start_row, const int start_col, const int d_row, const int d_col) -> optional<string>
    {
        string constructed_string;
        for (int i = 0; i < length; ++i)
        {
            const int new_row = start_row + i * d_row;
            const int new_col = start_col + i * d_col;
            if (!is_valid_position(new_row, new_col))
            {
                return std::nullopt;
            }
            constructed_string.push_back(grid[new_row][new_col]);
        }
        return constructed_string;
    };

    // Define directional offsets
    const std::vector<std::pair<int, int>> directions = {
        {-1,  0}, // Up
        { 1,  0}, // Down
        { 0, -1}, // Left
        { 0,  1}, // Right
        {-1, -1}, // Diag_Up_Left
        {-1,  1}, // Diag_Up_Right
        { 1, -1}, // Diag_Down_Left
        { 1,  1}  // Diag_Down_Right
    };

    // Starting position
    const auto& [startRow, startCol] = position;

    // Iterate over all directions and build strings
    for (size_t dir = 0; dir < directions.size(); ++dir)
    {
        const auto& [d_row, d_col] = directions[dir];
        result[static_cast<Direction>(dir)] = constructString(startRow, startCol, d_row, d_col);
    }

    return result;
}

std::map<Direction, std::optional<char>> GetSurroundingElements(
    const std::vector<std::vector<char>>& grid, std::pair<int, int> position) 
{
    using std::optional;

    std::map<Direction, optional<char>> surrounding_elements;

    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(rows > 0 ? grid[0].size() : 0);

    // Lambda to check if a position is within grid bounds
    auto isValidPosition = [&](const int row, const int col)
    {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    };

    // Define directional offsets
    const std::vector<std::pair<int, int>> offsets = {
        {-1,  0}, // Up
        { 1,  0}, // Down
        { 0, -1}, // Left
        { 0,  1}, // Right
        {-1, -1}, // Diag_Up_Left
        {-1,  1}, // Diag_Up_Right
        { 1, -1}, // Diag_Down_Left
        { 1,  1}  // Diag_Down_Right
    };

    const auto& [start_row, start_col] = position;

    // Iterate over all directions
    for (size_t dir = 0; dir < offsets.size(); ++dir)
    {
        const auto& [d_row, d_col] = offsets[dir];
        int new_row = start_row + d_row;
        int new_col = start_col + d_col;

        if (isValidPosition(new_row, new_col))
        {
            surrounding_elements[static_cast<Direction>(dir)] = grid[new_row][new_col];
        }else
        {
            surrounding_elements[static_cast<Direction>(dir)] = std::nullopt;
        }
    }

    return surrounding_elements;
}