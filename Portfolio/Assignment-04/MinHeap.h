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
