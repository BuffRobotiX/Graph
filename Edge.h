//An Edge class for graph implementations.

template<class ItemType>
class Edge
{
private:
   ItemType v, w;
   int weight;
public:
   Edge(ItemType firstVertex, ItemType secondVertex, int edgeWeight)
   {
      v = firstVertex;
      w = secondVertex;
      weight = edgeWeight;
   }  // end constructor
   ItemType getFirst()
   {
       return v;
   }
   ItemType getSecond()
   {
       return w;
   }
   int getWeight()
   {
       return weight;
   }
}; // end Edge
// End of header file
