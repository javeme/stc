#include "Node.h"

Node::Node(Edge *pFrontEdge)
{
	init(pFrontEdge);
}
void Node::init(Edge *pFrontEdge)
{
	m_pFrontEdge=pFrontEdge;
	m_pNextSuffixPointer=NULL;
}
unsigned int Node::getChildNum()
{
	return this->m_nextEdges.size();
}
unsigned int Node::addEdge(Edge* pNewEdge)
{
	m_nextEdges.push_back(pNewEdge);
	return getChildNum();
}
Edge* Node::getChildEdge(unsigned int index)
{
	if(index<0 || index>getChildNum())
		return NULL;
	return m_nextEdges[index];
}
void Node::setFrontEdge(Edge* pEdge)
{
	this->m_pFrontEdge=pEdge;
}
Edge* Node::getFrontEdge()
{
	return this->m_pFrontEdge;
}
void Node::setNextSuffixPointer(Node* pNextSuffix)
{
	m_pNextSuffixPointer = pNextSuffix;
}
Node* Node::getNextSuffix()
{
	return m_pNextSuffixPointer;
}
bool Node::hasNextSuffixPointer()
{
	return m_pNextSuffixPointer!=NULL;
}
