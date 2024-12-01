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




