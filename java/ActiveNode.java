

public class ActiveNode
{

public Node m_pNode;
public boolean m_bImplicit;//�Ƿ�Ϊ�����ڵ�
public int m_nImplicitNodeEdge,m_nImplicitNodeOffsetInEdge;//�����ڵ�ߵı��

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
if(!m_bImplicit)//��ʾ�ڵ�
{
Edge pEdge=m_pNode.getChildEdge(edgeIndex);
//��ʾ����ʽ
if( pEdge.charSize()>1 || pEdge.getVirtualEndPos()==0)//���ȴ���1,���߶���ΪҶ�ӽڵ�
{
m_bImplicit=true;
m_nImplicitNodeEdge=edgeIndex;
m_nImplicitNodeOffsetInEdge=0;
}
//��ʾ����һ����ʾ
else//charSize==1
m_pNode=pEdge.getNextNode();
}
else
{
m_nImplicitNodeOffsetInEdge++;
if(getEdge().charSize() == m_nImplicitNodeOffsetInEdge+1)//getEdge().getEndPos()��û�м�����ô��ʱ,�õ�m_nEndPos�Ƿ����?
{
setExplicitNode(getEdge().getNextNode());
}
}
}}