#ifndef SuffixTree_h
#define SuffixTree_h

#include <queue>
#include <vector>
#include <string>
using namespace std;
typedef basic_string<char> String;//basic_string<short>

#include "Node.h"
#include "ActiveNode.h"
#include "CharPosition.h"

#define ERROR 100
#define APPEND_TO_LEAF 1
#define	NEW_LEAF 2
#define SPLIT_NODE 3
#define CONTAINED_NODE 4

class SuffixTree
{
private:
	//unsigned int m_nDataId;
	//map<unsigned int,String> dataMap;//nDataId,strData
	vector<String> dataArray;
	Node *m_pRoot,*m_pOldNode;
	ActiveNode m_activeNode;
	unsigned int m_nEndPosition;
private:
	void addToTree(String& data);
	//void deleteNode(Node *pParent);
	void deleteAllNode();
	//void updateTree(Node *pNode,int type);
	void updateTree(unsigned int start);
	//int getType(unsigned int start,unsigned int end,Node*& pNode,CharPosition& splitPos);
	bool search(String& strToSearch,Node*& pParentNode,CharPosition& foundPos);
	String subData(unsigned int start,unsigned int num);
	
	bool isDataEqual(unsigned int pos1,unsigned int pos2,unsigned int offset=1);
	bool isDataEqual(String str,unsigned int pos,unsigned int offset=1);//char ch
	void printNode(Node *pParent);
public:
	SuffixTree(String data="");
	~SuffixTree();

public:
	void addText(String data);
	int positionOfSubstring(String value);
	void printTree();
	unsigned int getEndPosition();
};

#endif