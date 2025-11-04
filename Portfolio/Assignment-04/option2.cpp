// Author: Douwe Berkeij
// Date: 04-11-2025
// AI use: for the making of this code there was made use of the GitHub Copilot AI tool.
// to assist with debugging and writing code faster.
// No full code was directly copied or generated with AI sources.

// example run comands:
// - "0" | & "C:\path\to\Portfolio\Assignment-04\Debug\Assignment-04.exe"
// - "Bergen" | & "C:\path\to\Portfolio\Assignment-04\Debug\Assignment-04.exe"

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>

#include "SharedLib.h"
#include "Graph.h"
#include "MinHeap.h"

static constexpr std::string_view AssignmentOption = "Option 2 (Advanced): Inter-city Logistics Router.";

// We'll keep a pointer to the graph so the C-style callbacks can populate it
static Graph* g_graph = nullptr;

// Callback used by readGraphFromFile to add nodes
static bool NodeReadCallback(const int aIndex, const int aTotalCount, const std::string& aNode)
{
	if (!g_graph) return false;
	g_graph->AddNode(aNode);
	return true;
}

// Callback used by readGraphFromFile to add edges (directed)
static bool EdgeReadCallback(const int aIndex, const int aTotalCount, const std::string& aFromNode, const std::string& aToNode, float aWeight)
{
	if (!g_graph) return false;
	g_graph->AddEdge(aFromNode, aToNode, aWeight);
	return true;
}

// Dijkstra using our MinHeap. Returns pair of distances and predecessors.
static void Dijkstra(const Graph& graph, int source, std::vector<float>& outDist, std::vector<int>& outPrev)
{
	const int n = graph.NodeCount();
	const float INF = std::numeric_limits<float>::infinity();
	outDist.assign(n, INF);
	outPrev.assign(n, -1);

	MinHeap heap;
	outDist[source] = 0.0f;
	heap.Push(source, 0.0f);

	while (!heap.Empty())
	{
		auto [u, d] = heap.Pop();
		// stale entry check
		if (d != outDist[u]) continue;

		for (auto& edge : graph.Adj(u))
		{
			int v = edge.first;
			float w = edge.second;
			float nd = d + w;
			if (nd < outDist[v])
			{
				outDist[v] = nd;
				outPrev[v] = u;
				heap.Push(v, nd); // insert improved distance
			}
		}
	}
}

int RunApp()
{
	std::cout << AssignmentOption << std::endl;

	// Try to use a relative path by default (adjust if your DATA folder is elsewhere)
	std::string filename = "DATA/city_graph.txt";
	std::cout << "Reading graph from file: " << filename << "\n\n";

	Graph graph;
	g_graph = &graph; // point callbacks to this graph

	// Read graph - nodes then edges
	readGraphFromFile(filename, NodeReadCallback, EdgeReadCallback);

	g_graph = nullptr; // done

	const int n = graph.NodeCount();
	if (n == 0)
	{
		std::cout << "Graph is empty or file not found/parsed. Check the filename/path.\n";
		return 1;
	}

	std::cout << "Loaded " << n << " cities:" << std::endl;
	for (int i = 0; i < n; ++i)
	{
		std::cout << "  [" << i << "] " << graph.GetName(i) << "\n";
	}

	// Ask user to select source by index or name
	std::cout << "\nEnter start city (index or exact name): ";
	std::string input;
	std::getline(std::cin, input);
	int source = -1;
	// try parse as index
	try {
		size_t pos = 0;
		int idx = std::stoi(input, &pos);
		if (pos == input.size() && idx >= 0 && idx < n) source = idx;
	} catch (...) {}
	if (source == -1)
	{
		// treat as name
		for (int i = 0; i < n; ++i)
			if (graph.GetName(i) == input) { source = i; break; }
	}
	if (source == -1)
	{
		std::cout << "Invalid source. Using 0 as default.\n";
		source = 0;
	}

	std::vector<float> dist;
	std::vector<int> prev;
	Dijkstra(graph, source, dist, prev);

	// Print routing table
	std::cout << "\nRouting table from: " << graph.GetName(source) << "\n";
	std::cout << std::left << std::setw(4) << "ID" << std::setw(30) << "City" << "Cost" << "\n";
	std::cout << std::string(50, '-') << "\n";
	for (int i = 0; i < n; ++i)
	{
		std::cout << std::left << std::setw(4) << i << std::setw(30) << graph.GetName(i);
		if (dist[i] == std::numeric_limits<float>::infinity())
			std::cout << "UNREACHABLE";
		else
			std::cout << dist[i];
		std::cout << "\n";
	}

	return 0;
}