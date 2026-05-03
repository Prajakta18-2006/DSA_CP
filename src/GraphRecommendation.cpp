#include "GraphRecommendation.h"
#include <iostream>
#include <algorithm>

/*
 * GRAPH RECOMMENDATION IMPLEMENTATION
 * ====================================
 * Uses Adjacency List representation.
 *
 * Original C++ code used:
 *   unordered_map<int, vector<int>> g;
 *   g[a].push_back(b);  → directed edge
 *
 * This version supports bidirectional edges for better
 * recommendations (if A recommends B, B recommends A).
 */

// ADD EDGE: Connect two books in the recommendation graph
void GraphRecommendation::addEdge(int bookA, int bookB, bool bidirectional) {
    // Check for duplicate edge before adding
    auto& neighborsA = adjList[bookA];
    if (std::find(neighborsA.begin(), neighborsA.end(), bookB) == neighborsA.end()) {
        neighborsA.push_back(bookB);
    }

    if (bidirectional) {
        auto& neighborsB = adjList[bookB];
        if (std::find(neighborsB.begin(), neighborsB.end(), bookA) == neighborsB.end()) {
            neighborsB.push_back(bookA);
        }
    }
}

/*
 * GET RECOMMENDATIONS: Return all neighbors of a book node
 * Time Complexity: O(degree of node) — very fast for sparse graphs
 * This mirrors recommend() from the original code:
 *   for (int x : g[id]) { cout << books[x].name; }
 */
std::vector<int> GraphRecommendation::getRecommendations(int bookId) const {
    auto it = adjList.find(bookId);
    if (it != adjList.end()) {
        return it->second;
    }
    return {};  // No recommendations found
}

bool GraphRecommendation::hasRecommendations(int bookId) const {
    auto it = adjList.find(bookId);
    return (it != adjList.end() && !it->second.empty());
}

int GraphRecommendation::totalEdges() const {
    int count = 0;
    for (const auto& pair : adjList) {
        count += static_cast<int>(pair.second.size());
    }
    return count / 2;  // bidirectional, so divide by 2
}

int GraphRecommendation::totalNodes() const {
    return static_cast<int>(adjList.size());
}

void GraphRecommendation::displayGraph() const {
    std::cout << "\n  Recommendation Graph (Adjacency List):\n";
    std::cout << "  +----------+-------------------------------+\n";
    std::cout << "  | Book ID  | Recommends (Book IDs)         |\n";
    std::cout << "  +----------+-------------------------------+\n";

    for (const auto& pair : adjList) {
        std::cout << "  | " << std::left;
        std::cout.width(9);
        std::cout << pair.first << "| ";

        std::string neighbors = "";
        for (size_t i = 0; i < pair.second.size(); i++) {
            neighbors += std::to_string(pair.second[i]);
            if (i < pair.second.size() - 1) neighbors += ", ";
        }
        std::cout.width(30);
        std::cout << std::left << neighbors << "|\n";
    }
    std::cout << "  +----------+-------------------------------+\n";
}
