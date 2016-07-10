#ifndef Node_h
#define Node_h

#include <vector>
using namespace std;

#include "Edge.h"

class Node
{
private:
	//Ç°ºó±ß
	Edge *m_pFrontEdge;
	vector<Edge*> m_nextEdges;
	Node* m_pNextSuffixPointer;
private:
	void init(Edge *pFrontEdge);
public:
	Node(Edge *pFrontEdge);
public:
	unsigned int getChildNum();
	void setFrontEdge(Edge* pEdge);
	Edge* getFrontEdge();
	unsigned int addEdge(Edge* pNewEdge);
	Edge* getChildEdge(unsigned int index);
	void setNextSuffixPointer(Node* pNextSuffix);
	Node* getNextSuffix();
	bool hasNextSuffixPointer();
};

#endif