//David Buff
template<class ItemType>
class Vertex
{
private:
    ItemType data;
    int id;
    static int numVertices;
public:
   Vertex(ItemType info)
   {
      data = info;
      numVertices++;
      id = numVertices;
   }
   ItemType getData()
   {
       return data;
   }
   int getId()
   {
       return id;
   }
};
//template<class ItemType>
//int Vertex<ItemType>::numVertices = 0;
int numVertices = 0;