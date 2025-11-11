// Author: Douwe Berkeij
// Date: 04-11-2025
// AI use: for the making of this code there was made use of the GitHub Copilot AI tool.
// to assist with debugging and writing code faster.
// No full code was directly copied or generated with AI sources.

#pragma once
#include <vector>
#include <utility>

// Simple min-heap storing pairs (key=index, priority=dist)
class MinHeap
{
public:
    MinHeap() = default;
    void Push(int key, float priority);
    bool Empty() const { return m_data.empty(); }
    std::pair<int,float> Pop();

private:
    std::vector<std::pair<int,float>> m_data; // binary heap
    void HeapifyUp(int idx);
    void HeapifyDown(int idx);
};
