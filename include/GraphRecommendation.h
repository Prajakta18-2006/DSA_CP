#ifndef GRAPHRECOMMENDATION_H
#define GRAPHRECOMMENDATION_H

#include <vector>
#include <unordered_map>

/*
 * ============================================
 *      GRAPH RECOMMENDATION SYSTEM
 * ============================================
 *
 * DSA USAGE: Graph (Adjacency List) for BOOK RECOMMENDATIONS
 *
 * WHY Graph?
 *   - Books have "related-to" relationships (not hierarchical)
 *   - Adjacency list efficiently stores sparse connections
 *   - Given a book, we can find all related books in O(degree)
 *   - Models real-world recommendation networks
 *
 * STRUCTURE:
 *   Adjacency List: unordered_map<int, vector<int>>
 *   Key = Book ID, Value = list of recommended Book IDs
 *
 * OPERATIONS:
 *   addEdge()            → Connect two books (bidirectional)
 *   getRecommendations() → Get all neighbors of a book node
 *   hasRecommendations() → Check if book has any connections
 *
 * EXAMPLE:
 *   addEdge(1, 2) means "Data Structures" recommends "Algorithms"
 *   and vice versa (bidirectional edge)
 */

class GraphRecommendation {
private:
    std::unordered_map<int, std::vector<int>> adjList;

public:
    void addEdge(int bookA, int bookB, bool bidirectional = true);
    std::vector<int> getRecommendations(int bookId) const;
    bool hasRecommendations(int bookId) const;
    int totalEdges() const;
    int totalNodes() const;
    void displayGraph() const;
};

#endif
