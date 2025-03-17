using namespace std;
#include "kruskals.h"

Graph::Graph(int V, int E){
    this->V = V;
    this->E = E;
}

void Graph::addEdge(int u, int v, int w){
    edges.push_back({w, {u, v}});
}


// make-set
DisjointSets::DisjointSets(int n){
    this->n = n;

    // initializing int arrays
    parent = new int[n+1];
    rank = new int[n+1];

    // for each vertice in the set, set the rank to 0, and the parent as itself
    for(int i = 0; i < n; ++i){
        rank[i] = 0;
        parent[i] = i;
    }

    printRankAndParent();
}

void DisjointSets::printRankAndParent(){
    cout << "Rank: ";;
    for(int i = 0; i < n; ++i){
        cout << i << ": " << rank [i] << " ";

    }
    cout << "\n";

    cout << "Parent: ";;
    for(int i = 0; i < n; ++i){
        cout << i << ": " << parent [i] << " ";

    }
    cout << "\n";
}

// finds the "representative" of the set
int DisjointSets::findSet(int u){
    if(u != parent[u]){
        parent[u] = findSet(parent[u]);
    }

    return parent[u];
}

// joins two sets depending on their rank
void DisjointSets::makeUnion(int x, int y){
    x = findSet(x);
    y = findSet(y);

    if(rank[x] > rank[y]){
        parent[y] = x;
    }
    else{
        parent[x] = y;
    }

    if(rank[x] == rank[y]){
        ++rank[y];
    }
}

void DisjointSets::printSets(){
    cout << "Current Disjoined Sets:\n";
    unordered_map<int, vector<int>> sets;

    for(int i = 0; i < n; ++i){
        sets[findSet(i)].push_back(i);
    }

    for(const auto &set : sets){
        cout << set.first << ": ";
        cout << "{ ";
        for(int v : set.second){
            cout << v << " ";
        }
        cout << "}\n";
    }

}

int Graph::kruskalMST(int k){
    // check for k - klusters that k would not exceed the amount of vertices in the graph
    if(k < 1 || k > this->V){
        cout << "Invalid cluster size \n" << endl; 
    }

    bool clustering = (k == 1 ? false : true);
  
    // initialize weight
    int mst_weight = 0;

    // sort edges in increasing order
    sort(edges.begin(), edges.end());

    cout << "Sorted edges:\n";
    for (auto &edge : edges) {
        cout << "(" << edge.second.first << ", " << edge.second.second << ") - Weight: " << edge.first << endl;
    }
    cout << "------------------------\n";
    

    // create disjoint sets
    DisjointSets disjoined_sets(V);

    vector<pair<int, verticePair>>::iterator it;
    disjoined_sets.printSets();
    cout << "----------------------------\n";

    for(it = edges.begin(); it != edges.end(); ++it){
        // initilize u and v as the elemnts of the secont pair of vector (two vertices)
        int u = it->second.first;
        int v = it->second.second;

        // findSet the parent of u and v
        int set_u = disjoined_sets.findSet(u);
        int set_v = disjoined_sets.findSet(v);

        cout << "Set " << u << ": " << set_u << "\n";
        cout << "Set " << v << ": " << set_v << "\n";
        cout << u << " - " << v << endl;

        // if they are not from the same set (dont have the same parent)
        if(set_u != set_v){

            // add the edge to mst (increase the final weigth)
            mst_weight += it->first;

            // join two sets
            disjoined_sets.makeUnion(set_u, set_v);

            disjoined_sets.printSets();

            cout << "Set " << u << ": " << disjoined_sets.findSet(u) << "\n";
            cout << "Set " << v << ": " << disjoined_sets.findSet(v) << "\n";
            cout << "----------------------------\n";

          
            // stop if there's only one set left (MST found)
            unordered_map<int, vector<int>> sets;
            for (int i = 0; i < V; ++i) {
                sets[disjoined_sets.findSet(i)].push_back(i);
            }

            if (sets.size() == 1) {
                cout << "Only one disjoint set remains, MST found!" << endl;
                break;
            }

            if(clustering){
                if (static_cast<int>(sets.size()) == k) {
                    cout << k << "-clustering found." << endl;
                    mst_weight = 0;
                    break;
                }
            }

        }
        else{
            cout << "Vertices are in the same sets, hence form a cycle. Continue to next smallest edge\n"; 
            cout << "----------------------------\n";

        }
        

    }

    return mst_weight;
}


int main(){
    int V = 11, E = 16; 
    Graph g(V, E); 
  
    g.addEdge(0, 1, 4);
    g.addEdge(0, 5, 9);
    g.addEdge(0, 4, 10);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 9, 10);
    g.addEdge(2, 8, 12);
    g.addEdge(2, 10, 13);
    g.addEdge(3, 8, 2);
    g.addEdge(3, 5, 11);
    g.addEdge(4, 6, 11);
    g.addEdge(5, 6, 3);
    g.addEdge(5, 10, 1);
    g.addEdge(6, 7, 12);
    g.addEdge(7, 8, 13);
    g.addEdge(9, 10, 7);

    int mst_wt = g.kruskalMST(3); 
 
    if(mst_wt != 0){
            cout << "\nWeight of MST is " << mst_wt << "\n"; 
    }
  
  
    return 0; 
}

