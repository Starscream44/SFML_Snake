#include "Records.h"
#include <algorithm>
#include <fstream>

bool RecordsTable::Load(const std::string& filename)
{
    m_entries.clear();

    std::ifstream in(filename);
    if (!in.is_open())
        return false;

    RecordEntry e;
    while (in >> e.name >> e.score)
    {
        if (e.score < 0) e.score = 0;
        m_entries.push_back(e);
    }

    SortDesc();
    return true;
}

bool RecordsTable::Save(const std::string& filename) const
{
    std::ofstream out(filename, std::ios::trunc);
    if (!out.is_open())
        return false;

    for (const auto& e : m_entries)
        out << e.name << " " << e.score << "\n";

    return true;
}

void RecordsTable::Add(const std::string& name, int score, std::size_t maxCount)
{
    RecordEntry e;
    e.name = name.empty() ? "XYZ" : name;
    e.score = std::max(0, score);

    m_entries.push_back(e);
    SortDesc();

    if (m_entries.size() > maxCount)
        m_entries.resize(maxCount);
}

bool RecordsTable::IsHighScore(int score, std::size_t maxCount) const
{
    if (score <= 0) return false;

    if (m_entries.size() < maxCount)
        return true;


    return score > m_entries.back().score;
}

void RecordsTable::SortDesc()
{
    std::sort(m_entries.begin(), m_entries.end(),
        [](const RecordEntry& a, const RecordEntry& b)
        {
            return a.score > b.score;
        });
}