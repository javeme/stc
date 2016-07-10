#include "ActiveNode.h"

unsigned int ActiveNode::getImplicitPosition()
{
	return getEdge()->getStartPos()+m_nImplicitNodeOffsetInEdge;
}
Edge* ActiveNode::getEdge()
{
	return m_pNode->getChildEdge(m_nImplicitNodeEdge);
}
void ActiveNode::setExplicitNode(Node *pNode)
{
	m_bImplicit=false;
	m_pNode=pNode;
}
void ActiveNode::increaseImplicitNodeOffset(unsigned int edgeIndex)
{
	if(!m_bImplicit)//��ʾ�ڵ�
	{
		Edge* pEdge=m_pNode->getChildEdge(edgeIndex);
		//��ʾ����ʽ
		if( pEdge->charSize()>1 || pEdge->getVirtualEndPos()==0)//���ȴ���1,���߶���ΪҶ�ӽڵ�
		{		
			m_bImplicit=true;
			m_nImplicitNodeEdge=edgeIndex;
			m_nImplicitNodeOffsetInEdge=0;
		}
		//��ʾ����һ����ʾ
		else//charSize==1
			m_pNode=pEdge->getNextNode();
	}
	else
	{
		m_nImplicitNodeOffsetInEdge++;
		if(getEdge()->charSize() == m_nImplicitNodeOffsetInEdge+1)//getEdge()->getEndPos()��û�м�����ô��ʱ,�õ�m_nEndPos�Ƿ����?
		{
			setExplicitNode(getEdge()->getNextNode());
		}
	}
}