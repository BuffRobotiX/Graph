//David Buff
//Compiles, runs, works great. Should work for any data type, even classes.
//Extra Credit: EC1 done, all the data is stored in a vector called data.
//EC2 done, the shortest weights to the vertices from the origin are correct.
//EC3 attempted, the path is not correct for most of the vertices

#pragma warning( disable: 4290 ) //disables warning about use of throw in the header files

#include <iostream>
#include "Graph.h"

using namespace std;

template<class ItemType>
void printBFS(Graph<ItemType> &aGraph);

template<class ItemType>
void printPrimsAlgorithm(Graph<ItemType> &aGraph, const ItemType &v);

template<class ItemType>
void printShortestPath(Graph<ItemType> &aGraph, const ItemType &v);
int main()
{
    cout << "Graphs based on Figure 20-22 in text\n\nint graph representation with maximum number of vertices equal to 9:\n\n";
    Graph<int> graph(9);

    graph.add(0, 1, 6);
    graph.add(0, 5, 4);
    graph.add(0, 8, 2);

    graph.add(1, 2, 7);
    graph.add(1, 4, 9);

    graph.add(2, 3, 4);
    graph.add(2, 4, 3);

    graph.add(3, 6, 5);
    graph.add(3, 7, 1);

    graph.add(4, 6, 8);

    graph.add(5, 6, 2);

    cout << graph;

    printBFS<int>(graph);

    cout << "\n\nMinimum Spanning Tree for integer graph:\n";
    printPrimsAlgorithm<int>(graph, 0);

    cout << "\n\nShortest path from vertex 0. Vertex - weight.\n";
    printShortestPath<int>(graph, 0);

    cout << "\n\nAttempt to remove an edge with existing vertices:\n";
    try
    {
        if (graph.remove(Edge<int>(0, 5, 0)))
            cout << "Edge ( 0, 5, 0 ) has been removed from the graph.";
        else
            cout << "Edge ( 0, 5, 0 ) has NOT been removed from the graph.";
    }
    catch (PrecondViolatedExcep e)
    {
        cout << endl << endl << e.what();
    }

    cout << "\n\nAttempt to remove a non-existant edge with existing vertices:\n";
    try
    {
        if (graph.remove(Edge<int>(0, 6, 0)))
            cout << "Edge ( 0, 6, 0 ) has been removed from the graph.";
        else
            cout << "Edge ( 0, 6, 0 ) has NOT been removed from the graph.";
    }
    catch (PrecondViolatedExcep e)
    {
        cout << endl << e.what();
    }

    cout << "\n\nAttempt to remove a non-existant edge with non-existant vertices:\n";
    try
    {
        if (graph.remove(Edge<int>(0, 20, 0)))
            cout << "Edge ( 0, 20, 0 ) has been removed from the graph.";
        else
            cout << "Edge ( 0, 20, 0 ) has NOT been removed from the graph.";
    }
    catch (PrecondViolatedExcep e)
    {
        cout << endl << e.what();
    }
    
    cout << "\n\nchar graph representation with maximum number of vertices equal to 9:\n\n";
    Graph<char> graphChar(9);

    graphChar.add('a', 'b', 6);
    graphChar.add('a', 'f', 4);
    graphChar.add('a', 'i', 2);

    graphChar.add('b', 'c', 7);
    graphChar.add('b', 'e', 9);

    graphChar.add('c', 'd', 4);
    graphChar.add('c', 'e', 3);

    graphChar.add('d', 'g', 5);
    graphChar.add('d', 'h', 1);

    graphChar.add('e', 'g', 8);

    graphChar.add('f', 'g', 2);

    cout << graphChar;
   
    printBFS<char>(graphChar);

    cout << "\n\nMinimum Spanning Tree for character graph:\n";
    printPrimsAlgorithm<char>(graphChar, 'a');

    cout << "\n\nShortest path from vertex 'a'. Vertex - weight.\n";
    printShortestPath<char>(graphChar, 'a');

    cout << "\n\nAttempt to remove an edge with existing vertices:\n";
    try
    {
        if (graphChar.remove(Edge<char>('a', 'b', 0)))
            cout << "Edge ( 'a', 'b', 0 ) has been removed from the graph.";
        else
            cout << "Edge ( 'a', 'b', 0 ) has NOT been removed from the graph.";
    }
    catch (PrecondViolatedExcep e)
    {
        cout << endl << endl << e.what();
    }

    cout << "\n\nAttempt to remove a non-existant edge with existing vertices:\n";
    try
    {
        if (graphChar.remove(Edge<char>('a', 'c', 0)))
            cout << "Edge ( 'a', 'c', 0 ) has been removed from the graph.";
        else
            cout << "Edge ( 'a', 'c', 0 ) has NOT been removed from the graph.";
    }
    catch (PrecondViolatedExcep e)
    {
        cout << endl << e.what();
    }

    cout << "\n\nAttempt to remove a non-existant edge with non-existant vertices:\n";
    try
    {
        if (graphChar.remove(Edge<char>('a', 'z', 0)))
            cout << "Edge ( 'a', 'z', 0 ) has been removed from the graph.";
        else
            cout << "Edge ( 'a', 'z', 0 ) has NOT been removed from the graph.";
    }
    catch (PrecondViolatedExcep e)
    {
        cout << endl << e.what();
    }

    cout << "\n\nint graph representation with maximum number of vertices equal to 9\n and values are negative:\n\n";
    Graph<int> graphNeg(9);

    graphNeg.add(0, -1, 6);
    graphNeg.add(0, -5, 4);
    graphNeg.add(0, -8, 2);

    graphNeg.add(-1, -2, 7);
    graphNeg.add(-1, -4, 9);

    graphNeg.add(-2, -3, 4);
    graphNeg.add(-2, -4, 3);

    graphNeg.add(-3, -6, 5);
    graphNeg.add(-3, -7, 1);

    graphNeg.add(-4, -6, 8);

    graphNeg.add(-5, -6, 2);

    cout << graphNeg;

    printBFS<int>(graphNeg);

    cout << "\n\nMinimum Spanning Tree for integer graph:\n";
    printPrimsAlgorithm<int>(graphNeg, 0);

    cout << "\n\nShortest path from vertex 0. Vertex - weight.\n";
    printShortestPath<int>(graphNeg, 0);

    cout << "\n\nAttempt to remove an edge with existing vertices:\n";
    try
    {
        if (graphNeg.remove(Edge<int>(0, -5, 0)))
            cout << "Edge ( 0, -5, 0 ) has been removed from the graph.";
        else
            cout << "Edge ( 0, -5, 0 ) has NOT been removed from the graph.";
    }
    catch (PrecondViolatedExcep e)
    {
        cout << endl << endl << e.what();
    }

    cout << "\n\nAttempt to remove a non-existant edge with existing vertices:\n";
    try
    {
        if (graphNeg.remove(Edge<int>(0, -6, 0)))
            cout << "Edge ( 0, -6, 0 ) has been removed from the graph.";
        else
            cout << "Edge ( 0, -6, 0 ) has NOT been removed from the graph.";
    }
    catch (PrecondViolatedExcep e)
    {
        cout << endl << e.what();
    }

    cout << "\n\nAttempt to remove a non-existant edge with non-existant vertices:\n";
    try
    {
        if (graphNeg.remove(Edge<int>(0, 20, 0)))
            cout << "Edge ( 0, 20, 0 ) has been removed from the graph.";
        else
            cout << "Edge ( 0, 20, 0 ) has NOT been removed from the graph.";
    }
    catch (PrecondViolatedExcep e)
    {
        cout << endl << e.what();
    }


    cout << "\n\nProgram Over\n\nPress enter to end --> ";
    cin.get();
    return 0;
}

template<class ItemType>
void printBFS(Graph<ItemType> &aGraph)
{
    cout << "BFS serach result is:\n";
    map<ItemType, int> bfs = aGraph.BFS();
    for (map<ItemType, int>::iterator iter = bfs.begin(); iter != bfs.end(); iter++)
    {
        cout << iter->first << ".  " << iter->second << endl;
    }
}

template<class ItemType>
void printPrimsAlgorithm(Graph<ItemType> &aGraph, const ItemType &v)
{
    vector<Edge<ItemType> > mst = aGraph.primsAlgorithm(v);
    for (size_t i = 0; i < mst.size(); i++)
    {
        cout << mst[i].getFirst() << "   " << mst[i].getSecond() << "  " << mst[i].getWeight() << endl;
    }
}

template<class ItemType>
void printShortestPath(Graph<ItemType> &aGraph, const ItemType &v)
{
    tuple<vector<ItemType>, vector<vector<ItemType> >, vector<int> > result = aGraph.shortestPath(v); //vertices, path vector, weights
    vector<ItemType> data = get<0>(result);
    vector<vector<ItemType> > path = get<1>(result);
    vector<int> weights = get<2>(result);
    for (size_t i = 0; i < data.size(); i++)
    {
        cout << data[i] << ". ";
        for (size_t k = 0; k < path[i].size(); k++)
        {
            //cout << path[i][k] << ", ";
        }
        cout << "- " << weights[i] << endl;
    }
}