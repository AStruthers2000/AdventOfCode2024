#pragma once
#include "../Problem.h"

class Day09 : public Problem
{
public:
    Day09(const std::string_view& filename)
        : Problem(filename, "Year 2024 Day 9: Disk Fragmenter")
    {
    }

protected:
    void LoadProblem() override;
    std::optional<uint64_t> SolvePart1() override;
    std::optional<uint64_t> SolvePart2() override;

private:
    struct File
    {
        std::optional<int> id;
        int size;

        bool operator==(const File& other) const{return id == other.id && size == other.size;}
        bool operator<(const File& other) const
        {
            if(id == other.id)
            {
                return size < other.size;
            }
            
            return id < other.id;
        }
    };
    
    using Disk = std::vector<std::optional<int>>;

    Disk expanded_disk;
    std::vector<File> expanded_files;

    Disk SortIndividual();
    std::vector<File> SortFiles();
};


