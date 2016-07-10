#ifndef Edge_h
#define Edge_h

#include <vector>
using namespace std;

class Node;
class SuffixTree;

class Edge
{
private:
	//unsigned int dataId;
	unsigned int start,end;
	Node *m_pFrontNode,*m_pNextNode;
	//��ʽ�ڵ�λ�ñ��
	vector<unsigned int> implicitPosOffsetArray;
	//��׺��ָ��,����Ҷ�ڵ��ѯ���һ���ַ�λ��
	SuffixTree *m_pTree;
public:
	Edge();
	Edge(unsigned int start,unsigned int end,Node* pFrontNode,SuffixTree* pTree);
	~Edge();
public:
	void setPosition(unsigned int start,unsigned int end);
	void setFrontNode(Node* pFrontNode);
	void setNextNode(Node* pNextNode);
	void updateEndPosition(unsigned int end);
	//void setDataId(unsigned int dataId);

	Node* getNextNode();
	Node* getFrontNode();
	unsigned int charSize();
	unsigned int getStartPos();
	unsigned int getEndPos();
	unsigned int getVirtualEndPos();
	void addImplicitPosOffset(unsigned int offset);
	unsigned int getImplicitPosition(unsigned int index);
	unsigned int getImplicitNodeNum();
};

#endif
