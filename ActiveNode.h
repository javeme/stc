#ifndef ActiveNode_h
#define ActiveNode_h

#include "Node.h"
#include "Edge.h"

class ActiveNode
{
public:
	Node *m_pNode;
	bool m_bImplicit;//是否为隐含节点
	unsigned int m_nImplicitNodeEdge,m_nImplicitNodeOffsetInEdge;//隐含节点边的编号	
public:
	unsigned int getImplicitPosition();
	Edge* getEdge();
	void setExplicitNode(Node *pNode);
	void increaseImplicitNodeOffset(unsigned int edgeIndex);
};

#endif