//An adjacency list representation of an undirected, weighted graph.

//David Buff

#include "Graph.h"

template<class ItemType>
Graph<ItemType>::Graph(int n)
{
   map<int, int> element;
   adjList.assign(n, element);
   numVertices = n;
   numEdges = 0;
}  // end constructor

template<class ItemType>
int Graph<ItemType>::getNumVertices() const
{
   return numVertices;
}  // end getNumVertices

template<class ItemType>
int Graph<ItemType>::getNumEdges() const
{
   return numEdges;
}  // end getNumEdges

template<class ItemType>
int Graph<ItemType>::getWeight(Edge<ItemType> e) const
{
   return e.weight;
}  // end getWeight

template<class ItemType>
void Graph<ItemType>::add(Edge<ItemType> e)
{
   ItemType v = e.getFirst(),
       w = e.getSecond();
   int weight = e.getWeight();

   if(indexList.find(v) == indexList.end()) //if v is not already in the list, give it an index
    {
        data.push_back(v);
        indexList.insert(make_pair(v, data.size()-1)); //pairs the data of v and it's index in data
        if(indexList.find(w) == indexList.end())
        {
            data.push_back(w);
            indexList.insert(make_pair(w, data.size()-1));
            adjList[indexList.at(w)].insert(make_pair(indexList.at(v), weight));
        }
        else
        {
            adjList[indexList.at(w)].insert(make_pair(indexList.at(v), weight));
        }
        adjList[indexList.at(v)].insert(make_pair(indexList.at(w), weight)); //stores the index of w instead of w
    }
    else //use v's already existent index
    {
        if(indexList.find(w) == indexList.end())
        {
            data.push_back(w);
            indexList.insert(make_pair(w, data.size()-1));
            adjList[indexList.at(w)].insert(make_pair(indexList.at(v), weight));
        }
        else
        {
            adjList[indexList.at(w)].insert(make_pair(indexList.at(v), weight));
        }
        adjList[indexList.at(v)].insert(make_pair(indexList.at(w), weight));
    }
    numEdges++;
}  // end add

template<class ItemType>
void Graph<ItemType>::add(ItemType v, ItemType w, int weight)
{
    add(Edge<ItemType>(v, w, weight));
}  // end add

template<class ItemType>
bool Graph<ItemType>::remove(Edge<ItemType> e) throw(PrecondViolatedExcep)
{
   ItemType v = e.getFirst(),
       w = e.getSecond();
   int weight = e.getWeight();

   try //first check if the vertices exist
   {
       indexList.at(v);
       indexList.at(w);
   }
   catch (out_of_range e)
   {
       throw PrecondViolatedExcep("Vertex does not exist.");
       return false;
   }
   try //then check if the edge exists
   {
        map<int, int>::iterator it = findEdge(v, w);
        map<int, int>::iterator it2 = findEdge(w, v);
        adjList[indexList.at(v)].erase(w);
        adjList[indexList.at(w)].erase(v);
        numEdges--;
        return true;
   }
   catch (PrecondViolatedExcep e)
   {
       return false;
   }
}  // end remove

template<class ItemType>
map<int, int>::iterator Graph<ItemType>::findEdge(ItemType v, ItemType w) throw(PrecondViolatedExcep)
{
    map<int, int> m = adjList.at(indexList.at(v));
    map<int, int>::iterator iter = m.find(indexList.at(w));
    if (iter!=m.end())
        return iter;
    else
    {
        stringstream s;
        s << "Unable to find edge with vertices " << v << " and " << w << ".";
        throw PrecondViolatedExcep(s.str());
    }
}  // end findEdge

template<class ItemType>
map<ItemType, int> Graph<ItemType>::BFS()
{
    int count = 0;
    vector<int> mark(getNumVertices(), -1);
    vector<int> parents(getNumVertices(), 0);
    map<ItemType, int> bfs;
    int pos = 1;

    for (int v = 0; v < getNumVertices(); v++)
    {
      if (mark[v] == -1)
      {
          Edge<ItemType> e(data[v], data[v], 0);
          // create a queue to push edges
          queue<Edge<ItemType> > q;

          map<int, int> m;    // holds adjacency list of current vertex
          map<int, int>::iterator iter;

          q.push(e);
          while (!q.empty())
          {
             // get the edge at the front if the queue
             e = q.front();

             // pop the edge off the queue
             q.pop();

             // if the vertex w has not visited yet, visit it
             if (mark[indexList.at(e.getSecond())] == -1)
             {
                ItemType v = e.getFirst(),
	               w = e.getSecond();
	            int weight = e.getWeight();
                mark[indexList.at(w)] = count++;  // mark w visited
                parents[indexList.at(w)] = indexList.at(v);     // store w's parent
                
                bfs.insert(make_pair(w, pos)); //store the value and the number it was found in a map
                pos++;

                // go through adjacency list of w
                m = adjList[indexList.at(w)];
                for (iter = m.begin(); iter != m.end(); iter++)
                   // if w's neighbor vertices have not been visited,
                   // push the edge on the queue
                   if (mark[iter->first] == -1)
                      q.push(Edge<ItemType>(w, data[iter->first], iter->second));
             }  // end if
          }  // end while
       }
    }
    return bfs;
}

template<class ItemType>
vector<Edge<ItemType> > Graph<ItemType>::primsAlgorithm(ItemType v)
{
    vector<Edge<ItemType> > minSpanTree;
    vector<bool> mark(getNumVertices(), false);
    vector<int> possibilityList(getNumVertices(), INT_MAX); //a list of the vertices least costs
    stack<int> s;
    map<int, int> m;
    map<int, int>::iterator iter;
    int w = indexList.at(v);

    s.push(w);
    while (!s.empty())
    {
        w = s.top();
        m = adjList[w];
        int leastCost = INT_MAX;
        int leastCostIndex = m.begin()->first;

        for (iter = m.begin(); iter != m.end(); iter++) //find the least cost adjacent vertex
        {
            if (iter->second < possibilityList[iter->first])
                possibilityList[iter->first] = iter->second; //put each adjacesnt vertex's least cost in the possibility list
            if (iter->second < leastCost && !mark[iter->first])
            {
                leastCost = iter->second;
                leastCostIndex = iter->first;
            }
        } //leastCostIndex is now the vertex with the least cost to get to
        if (!mark[leastCostIndex] && leastCost <= possibilityList[leastCostIndex]) //if it hasn't been marked yet push it on the stack
        { //the possibiltyList makes sure even though we might be able to connect a vertex now, there is a shorter edge available. like e->b 9 should be a->b 6.
            minSpanTree.push_back(Edge<ItemType>(data[w], data[leastCostIndex], leastCost));
            s.push(leastCostIndex);
        }
        else
            s.pop(); //otherwise all of the adjacent vertices of w have been marked, pop w
        mark[w] = true;
    }
    return minSpanTree;
}

template<class ItemType>
tuple<vector<ItemType>, vector<vector<ItemType> >, vector<int> > Graph<ItemType>::shortestPath(ItemType origin)
{
    vector<map<ItemType, int> > sp; //a vector of maps of data and weights
    vector<bool> mark(getNumVertices(), false); //if the vertex has been included or not
    vector<int> weights(getNumVertices(), INT_MAX); //holds the weights from v to i
    vector<ItemType> vertices = data; //vertices
    vector<vector<ItemType> > path(getNumVertices(), vector<ItemType>()); //path to the corresponding vertex

    int v = indexList.at(origin);
    weights[v] = 0; //the distance from v to v is 0
    map<int, int> m;
    map<int, int>::iterator iter;
    stack<int> s;

    s.push(v);
    while (!s.empty())
    {
        v = s.top();
        m = adjList[v];
        int leastCost = INT_MAX;
        int leastCostIndex = 0;
        for (iter = m.begin(); iter != m.end(); iter++) //find all adjacent vertices
        {
            if (weights[iter->first] > iter->second + weights[v]) //if the distance from the origin to v + the distance from v to i is less than the stored weight for i
            {
                weights[iter->first] = iter->second + weights[v];

                path.at(leastCostIndex).clear();
                stack<int> d(s);
                while (!d.empty())
                {
                    path.at(leastCostIndex).push_back(data[d.top()]);
                    d.pop();
                }
                reverse(path.at(leastCostIndex).begin(), path.at(leastCostIndex).end());
            }
            if (iter->second < leastCost && !mark[iter->first]) //find the closest adjacent vertex
            {
                leastCost = iter->second;
                leastCostIndex = iter->first;
            }
        } //leastCostIndex is now the vertex with the least cost to get to
        if (!mark[leastCostIndex])
        {
            s.push(leastCostIndex);
        }
        else
            s.pop();
        mark[v] = true;
    }
    return tuple<vector<ItemType>, vector<vector<ItemType> >, vector<int> >(data, path, weights);
}

template<class ItemType>
ostream & operator << ( ostream & output, Graph<ItemType> & aGraph)
{
    for (map<ItemType, int>::iterator iter = aGraph.indexList.begin(); iter != aGraph.indexList.end(); iter++)
    {
        output << iter->first << endl;
        for (map<int, int>::iterator iter2 = aGraph.adjList[iter->second].begin(); iter2 != aGraph.adjList[iter->second].end(); iter2++)
        {
            output << aGraph.data[iter2->first] << "   " << iter2->second << endl;
        }
        output << endl;
    }
    return output;
}