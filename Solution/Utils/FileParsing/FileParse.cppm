export module FileParsing;

import <fstream>;
import <optional>;
import <vector>;
import <string>;

export std::vector<std::string> ReadFromFile(const std::optional<std::string_view>& file_name) {
    std::vector<std::string> lines;
    std::ifstream file((std::string(file_name.value_or("test.txt")))); // Convert string_view to string
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + std::string(file_name.value_or("test.txt")));
    }

    std::string line;

    // Read each line from the file
    while (std::getline(file, line))
    {
        // Add the line to the vector
        lines.push_back(line);         
    }

    file.close();

    return lines;
}
