


public class Node
{

//Ç°ºó±ß
private Edge m_pFrontEdge;
private ArrayList<Edge> m_nextEdges;
private Node m_pNextSuffixPointer;

//private void init(Edge pFrontEdge);

//public Node(Edge pFrontEdge);

//public int getChildNum();
//public void setFrontEdge(Edge pEdge);
//public Edge getFrontEdge();
//public int addEdge(Edge pNewEdge);
//public Edge getChildEdge( int index);
//public void setNextSuffixPointer(Node pNextSuffix);
//public Node getNextSuffix();
//public boolean hasNextSuffixPointer();



Node(Edge pFrontEdge)
{
init(pFrontEdge);
}
void init(Edge pFrontEdge)
{
m_pFrontEdge=pFrontEdge;
m_pNextSuffixPointer=null;
}
int getChildNum()
{
return this.m_nextEdges.size();
}
int addEdge(Edge pNewEdge)
{
m_nextEdges.push_back(pNewEdge);
return getChildNum();
}
Edge getChildEdge( int index)
{
if(index<0 || index>getChildNum())
return null;
return m_nextEdges[index];
}
void setFrontEdge(Edge pEdge)
{
this.m_pFrontEdge=pEdge;
}
Edge getFrontEdge()
{
return this.m_pFrontEdge;
}
void setNextSuffixPointer(Node pNextSuffix)
{
m_pNextSuffixPointer = pNextSuffix;
}
Node getNextSuffix()
{
return m_pNextSuffixPointer;
}
boolean hasNextSuffixPointer()
{
return m_pNextSuffixPointer!=null;
}
}