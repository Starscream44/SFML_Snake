#pragma once
#include <string>
#include <vector>

struct RecordEntry
{
    std::string name;
    int score = 0;
};

class RecordsTable
{
public:
    bool Load(const std::string& filename);
    bool Save(const std::string& filename) const;

   
    void Add(const std::string& name, int score, std::size_t maxCount);

   
    bool IsHighScore(int score, std::size_t maxCount) const;

    const std::vector<RecordEntry>& Get() const { return m_entries; }

private:
    void SortDesc();

private:
    std::vector<RecordEntry> m_entries;
};