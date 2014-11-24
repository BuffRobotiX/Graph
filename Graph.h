//David Buff
#ifndef _GRAPH
#define _GRAPH

#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <limits>
#include <iostream>
#include <sstream>
#include <tuple>
#include "Edge.h"
#include "PrecondViolatedExcep.h"

using namespace std;

/** An adjacency list representation of an undirected,
 * weighted graph. */
template<class ItemType>
class Graph
{
    template<class ItemType>
    friend ostream &operator<<( ostream &, Graph<ItemType> & );
private:
   int numVertices;   /** Number of vertices in the graph. */
   int numEdges;      /** Number of edges in the graph. */

   /** Adjacency list representation of the graph;
    * the map pair consists of the second vertex (key)
    * and the edge weight (value). */
   vector<map<int, int> > adjList;


   //maps data to indices
   map<ItemType, int> indexList; //this is the trick to the whole thing. You can get a vertex's index from the data, which is the key.
   //data is stored here
   vector<ItemType> data;

public:
   /** Constructor.
    * @pre The graph is empty.
    * @post The graph is initialized to hold n vertices. */
   Graph(int n);

   /** Determines the number of vertices in the graph.
    * @pre None.
    * @post None.
    * @return The number of vertices in the graph. */
   int getNumVertices() const;

   /** Determines the number of edges in the graph.
    * @pre None.
    * @post None.
    * @return The number of edges in the graph. */
   int getNumEdges() const;

   /** Determines the weight of an edge.
    * @pre The edge exists in the graph.
    * @post None.
    * @return The weight of the edge parameter. */
   int getWeight(Edge<ItemType> e) const;

   /** Creates an edge in the graph.
    * @pre The vertices exist in the graph.
    * @post Adds to both v and w's list. */
   void add(Edge<ItemType> e);

   void add(ItemType, ItemType, int);

   /** Removes an edge from the graph.
    * @pre The vertices exist in the graph.
    * @post Removes edges from both v and w's list. */
   bool remove(Edge<ItemType> e) throw(PrecondViolatedExcep);

   /** Finds the edge connecting v and w.
    * @pre The edge exists.
    * @post None.
    * @return An iterator to map key w in vector[v]. */
   map<int, int>::iterator findEdge(ItemType v, ItemType w) throw(PrecondViolatedExcep);

   map<ItemType, int> BFS();

   vector<Edge<ItemType> > primsAlgorithm(ItemType);

   tuple<vector<ItemType>, vector<vector<ItemType> >, vector<int> > shortestPath(ItemType);

}; // end Graph
// End of header file
#include "Graph.cpp"
#endif 
