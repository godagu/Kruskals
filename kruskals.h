#ifndef KRUSKALS_H_INCLUDED
#define KRUSKALS_H_INCLUDED

#include <bits/stdc++.h>

// a pair of vertices represent an edge
typedef pair<int, int> verticePair; 

// graph structure, holds the number of vertices and edges, vectore of edges and ther weights
struct Graph{
    int V, E;
    vector<pair<int, verticePair>> edges; 
    Graph(int V, int E);
    void addEdge(int u, int v, int w);

    // k argument is for k-clusterization. if not specified, it assumes an MST needs to be found
    int kruskalMST(int k = 1);
};

// dijoint sets structure for implementing kruskal's algorithm
struct DisjointSets{
    // storing the parent and the rank of the set
    int *parent, *rank; 
    int n;

    DisjointSets(int n);

    // find the parent of the node u. make all the vertices parent the immediate root (flatens out the tree, more efficient)
    // path compression
    int findSet(int u);

    // union by rank, set with a lower rank is joined with a set of a higher rank
    void makeUnion(int x, int y);

    // helper functions
    void printSets();
    void printRankAndParent();
};


#endif // KRUSKALS_H_INCLUDED