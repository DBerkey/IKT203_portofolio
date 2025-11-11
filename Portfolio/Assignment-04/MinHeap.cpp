// Author: Douwe Berkeij
// Date: 04-11-2025
// AI use: for the making of this code there was made use of the GitHub Copilot AI tool.
// to assist with debugging and writing code faster.
// No full code was directly copied or generated with AI sources.

#include "MinHeap.h"
#include <utility>

void MinHeap::Push(int key, float priority)
// Inserts a new element with the given key and priority into the min-heap.
{
    m_data.emplace_back(key, priority);
    HeapifyUp((int)m_data.size() - 1);
}

std::pair<int,float> MinHeap::Pop()
// Removes and returns the element with the smallest priority from the min-heap.
{
    if (m_data.empty()) return {-1, 0.0f};
    auto top = m_data.front();
    m_data[0] = m_data.back();
    m_data.pop_back();
    if (!m_data.empty()) HeapifyDown(0);
    return top;
}

void MinHeap::HeapifyUp(int idx)
// Moves the element at index idx up to restore the heap property.
{
    while (idx > 0)
    {
        int parent = (idx - 1) / 2;
        if (m_data[parent].second <= m_data[idx].second) break;
        std::swap(m_data[parent], m_data[idx]);
        idx = parent;
    }
}

void MinHeap::HeapifyDown(int idx)
// Moves the element at index idx down to restore the heap property.
{
    int n = (int)m_data.size();
    while (true)
    {
        int left = idx * 2 + 1;
        int right = idx * 2 + 2;
        int smallest = idx;
        if (left < n && m_data[left].second < m_data[smallest].second) smallest = left;
        if (right < n && m_data[right].second < m_data[smallest].second) smallest = right;
        if (smallest == idx) break;
        std::swap(m_data[idx], m_data[smallest]);
        idx = smallest;
    }
}
