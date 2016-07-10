#ifndef ActiveNode_h
#define ActiveNode_h

#include "Node.h"
#include "Edge.h"

class ActiveNode
{
public:
	Node *m_pNode;
	bool m_bImplicit;//�Ƿ�Ϊ�����ڵ�
	unsigned int m_nImplicitNodeEdge,m_nImplicitNodeOffsetInEdge;//�����ڵ�ߵı��	
public:
	unsigned int getImplicitPosition();
	Edge* getEdge();
	void setExplicitNode(Node *pNode);
	void increaseImplicitNodeOffset(unsigned int edgeIndex);
};

#endif