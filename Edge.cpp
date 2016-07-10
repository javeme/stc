#include "Edge.h"
#include "Node.h"
#include "SuffixTree.h"

Edge::Edge()
{
	this->setPosition(-1,-1);
	this->setFrontNode(NULL);
	this->setNextNode(new Node(this));
}

Edge::Edge(unsigned int start,unsigned int end,Node* pFrontNode,SuffixTree *pTree)
{
	m_pTree=pTree;
	this->setPosition(start,end);
	this->setNextNode(new Node(this));
	this->setFrontNode(pFrontNode);
}
Edge::~Edge()
{
	//if()m_pFrontNode,*m_pNextNode;
	;
}
void Edge::setPosition(unsigned int start,unsigned int end)
{
	this->start=start;
	this->end=end;
}
void Edge::setFrontNode(Node* pFrontNode)
{
	this->m_pFrontNode=pFrontNode;
}
void Edge::setNextNode(Node* pNextNode)
{
	m_pNextNode=pNextNode;
}
void Edge::updateEndPosition(unsigned int end)
{
	this->end=end;
}/*
//设置字符串对应的id
void Edge::setDataId(unsigned int dataId)
{
	this->dataId=dataId;
}*/
unsigned int Edge::charSize()
{
	return (getEndPos()-start);
}
unsigned int Edge::getStartPos()
{
	return start;
}
unsigned int Edge::getEndPos()
{
	if(end==0)//表示叶节点
		return m_pTree->getEndPosition();
	return end;
}
//直接返回end,即使是0也不经过转换
unsigned int Edge::getVirtualEndPos()
{
	return end;
}
Node* Edge::getNextNode()
{
	return this->m_pNextNode;
}
Node* Edge::getFrontNode()
{
	return this->m_pFrontNode;
}
void Edge::addImplicitPosOffset(unsigned int offset)
{
	this->implicitPosOffsetArray.push_back(offset);
}
unsigned int Edge::getImplicitPosition(unsigned int index)
{
	return implicitPosOffsetArray[index]+start;
}
unsigned int Edge::getImplicitNodeNum()
{
	return implicitPosOffsetArray.size();
}