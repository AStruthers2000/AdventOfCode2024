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

bool IsVectorEntirelyN(const std::string& v, const char& n)
{
    const std::vector<char> v_t(v.begin(), v.end());
    return IsVectorEntirelyN(v_t, n);
}

std::vector<std::string> SplitLineByToken(const std::string& line, const char token)
{
    std::vector<std::string> result;

    // Use std::string_view for efficient splitting
    std::string_view line_view = line;
    size_t start = 0;
    size_t end = 0;

    // Split by the token
    while ((end = line_view.find(token, start)) != std::string_view::npos)
    {
        result.emplace_back(line_view.substr(start, end - start));
        start = end + 1;
    }

    // Add the last token (if any)
    result.emplace_back(line_view.substr(start));

    return result;
}