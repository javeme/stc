

public class ActiveNode
{

public Node m_pNode;
public boolean m_bImplicit;//是否为隐含节点
public int m_nImplicitNodeEdge,m_nImplicitNodeOffsetInEdge;//隐含节点边的编号

//public int getImplicitPosition();
//public Edge getEdge();
//public void setExplicitNode(Node pNode);
//public void increaseImplicitNodeOffset( int edgeIndex);



int getImplicitPosition()
{
return getEdge().getStartPos()+m_nImplicitNodeOffsetInEdge;
}
Edge getEdge()
{
return m_pNode.getChildEdge(m_nImplicitNodeEdge);
}
void setExplicitNode(Node pNode)
{
m_bImplicit=false;
m_pNode=pNode;
}
void increaseImplicitNodeOffset( int edgeIndex)
{
if(!m_bImplicit)//显示节点
{
Edge pEdge=m_pNode.getChildEdge(edgeIndex);
//显示变隐式
if( pEdge.charSize()>1 || pEdge.getVirtualEndPos()==0)//长度大于1,或者儿子为叶子节点
{
m_bImplicit=true;
m_nImplicitNodeEdge=edgeIndex;
m_nImplicitNodeOffsetInEdge=0;
}
//显示变下一个显示
else//charSize==1
m_pNode=pEdge.getNextNode();
}
else
{
m_nImplicitNodeOffsetInEdge++;
if(getEdge().charSize() == m_nImplicitNodeOffsetInEdge+1)//getEdge().getEndPos()还没有加入那么多时,用到m_nEndPos是否合适?
{
setExplicitNode(getEdge().getNextNode());
}
}
}}