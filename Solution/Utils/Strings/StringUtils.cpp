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
    size_t end = 0;

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

bool ContainsOnlyDigits(const std::string& str)
{
    return !str.empty() && std::ranges::all_of(str, ::isdigit);
}
