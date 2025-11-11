#include "Graph.h"
#include <algorithm>

int Graph::AddNode(const std::string& name)
{
    auto it = m_nameToIndex.find(name);
    if (it != m_nameToIndex.end()) return it->second;

    int idx = (int)m_names.size();
    m_names.push_back(name);
    m_nameToIndex[name] = idx;
    m_adj.emplace_back();
    return idx;
}

void Graph::AddEdge(const std::string& from, const std::string& to, float weight)
{
    int u = AddNode(from);
    int v = AddNode(to);
    // Add directed edge u -> v
    m_adj[u].push_back({v, weight});
}
