#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Graph
{
public:
    Graph() = default;

    // Add a node by name. Returns its index (existing index if already present)
    int AddNode(const std::string& name);

    // Add directed edge from -> to with weight
    void AddEdge(const std::string& from, const std::string& to, float weight);

    int NodeCount() const { return (int)m_names.size(); }
    const std::string& GetName(int idx) const { return m_names[idx]; }
    const std::vector<std::pair<int,float>>& Adj(int idx) const { return m_adj[idx]; }

private:
    std::vector<std::string> m_names;
    std::unordered_map<std::string,int> m_nameToIndex;
    std::vector<std::vector<std::pair<int,float>>> m_adj; // pair<to,weight>
};
