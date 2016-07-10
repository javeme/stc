#include "SuffixTree.h"

#define Debug

//#undef Debug
#ifdef Debug
	//#define add_node
	bool for_search=0;
#endif

SuffixTree::SuffixTree(string data)
{
	m_pRoot=new Node(NULL);
	m_activeNode.setExplicitNode(m_pRoot);
	m_pOldNode=NULL;//??
	m_nEndPosition=0;
	this->addText(data);
}
SuffixTree::~SuffixTree()
{
	deleteAllNode();
}
void SuffixTree::deleteAllNode()
{
	Node *pNode=NULL;
	Edge *pEdge=NULL;
	unsigned int i,j,edgeNum;
	queue<Node*> nodeQueue;
	nodeQueue.push(this->m_pRoot);
	printf("delete nodes...\n");
	//��ȱ���
	while(nodeQueue.size()>0)
	{
		//����
		pNode=nodeQueue.front();
		nodeQueue.pop();

		edgeNum=pNode->getChildNum();
		
		//�������б�
		for(i=0;i<edgeNum;i++)
		{
			pEdge=pNode->getChildEdge(i);
			//���
			nodeQueue.push(pEdge->getNextNode());
			delete pEdge;
		}
		delete pNode;
	}
	printf("end of delete\n");
}
unsigned int SuffixTree::getEndPosition()
{
	return this->m_nEndPosition;
}
void SuffixTree::addText(string data)
{
	//Ԥ�����ı�,����־��
	if(data.length()==0)
		return;

	this->addToTree(data);
}

void SuffixTree::addToTree(string& data)
{	
	//this->dataMap.insert(map<unsigned int,string>::value_type(dataMap.size(),data));	
	unsigned int i;	
	unsigned int size=data.length();
	unsigned int totalOffset=m_nEndPosition+size;
	dataArray.push_back(data);//����ԭʼ���ݵ�����
	
	//����ÿ����ǰ׺
	for(i=m_nEndPosition;i<totalOffset;i++)
	{
		//ȡǰ׺�����һ���ַ�,����
		m_nEndPosition++;//ע��:Ҷ�ӽڵ㲻��Ҫ�ٸ���,���ڴ���Ҷ�ӽڵ�ʱ����λ������Ϊm_nEndPosition��
		updateTree(i);		
	}	
}
//��startλ�õ��ַ����뵽����
void SuffixTree::updateTree(unsigned int start)
{	
	Node *pTmpNode;
	Edge *pEdge, *pTmpEdge;
	unsigned int i,edgeNum;
	unsigned int matchePos=0;//Ҫƥ���λ��	
	bool bMatched=false;
	m_pOldNode=NULL;

	#ifdef Debug
		#ifdef add_node 
			printf("<<<<<<<<<<<<<< '%s' >>>>>>>>>>>>>>>>\n",subData(start,1).c_str());
		#endif
	#endif
	//�����ڵ��Ƿ�����������ַ�
	while(!bMatched)
	{			
		//��ڵ�:�����ڵ�Ϊ����ڵ�,���߱���Ϊ����ڵ�
		//ע���ڵ��Ƿ�Ҷ�ڵ�
		//1.ƥ��������׺,�������ڵ�
		//����������ڵ�
		if(m_activeNode.m_bImplicit)
		{
			matchePos=m_activeNode.getImplicitPosition()+1;
			if(isDataEqual(start,matchePos))
			{
				bMatched=true;//�˳�,��Ϊ���̵ĺ�׺Ҳ�϶���ƥ���
			}
		}
		//��ʾ�ڵ�
		else
		{			
			edgeNum=m_activeNode.m_pNode->getChildNum();
			for(i=0;i<edgeNum;i++)
			{
				matchePos=m_activeNode.m_pNode->getChildEdge(i)->getStartPos();
				if(isDataEqual(start,matchePos))
				{
					bMatched=true;
					break;
				}			
			}
		}		
		if(bMatched)
		{
			//���¼���ڵ�
			m_activeNode.increaseImplicitNodeOffset(i);//������������?
		}
		//����ַ���ƥ��
		else
		{
			//2.��ʽ�ڵ�,��ֽڵ�,�����Ҷ�ڵ�
			if(m_activeNode.m_bImplicit)
			{
				//���:				
				pEdge=m_activeNode.getEdge();//�����
				//���1���ڵ�
				pTmpNode=new Node(pEdge);//�м�ڵ�
				//���Ϊ2����
				pTmpEdge=new Edge(matchePos,pEdge->getVirtualEndPos(),pTmpNode,this);//�����

				pEdge->updateEndPosition(matchePos);//����Ҷ�ӽڵ�ʱ,�Ӵ˰���Ҷ�ӽڵ�
				pTmpEdge->setNextNode(pEdge->getNextNode());
				pEdge->getNextNode()->setFrontEdge(pTmpEdge);//�ָ�ʱ���˰��ӽڵ�ĸ��ױ߸�Ϊ�����!!!
				pEdge->setNextNode(pTmpNode);				
				pTmpNode->addEdge(pTmpEdge);
				
				//��ʽ�ڵ����ʾ�ڵ�,����Ϊ����ڵ�(�е�ǣǿ?)
				m_activeNode.setExplicitNode(pTmpNode);
				//��׺����
				if(m_pOldNode!=NULL)
					m_pOldNode->setNextSuffixPointer(m_activeNode.m_pNode);
				m_pOldNode=m_activeNode.m_pNode;

				#ifdef Debug
					#ifdef add_node 
						printf("\nsplit:\n %d,%d,%d [%s]\n %d,%d [%s--%s] \n",pEdge->getStartPos(),pEdge->getEndPos(),pTmpEdge->getEndPos(),
								subData(pEdge->getStartPos(),pTmpEdge->getEndPos()-pEdge->getStartPos()).c_str(),start,start+1,
								subData(pEdge->getStartPos(),pEdge->getEndPos()-pEdge->getStartPos()).c_str(),subData(start,1).c_str());
					#endif
				#endif			
			}
			//3.��ʾ�ڵ�,������ʾ�ڵ�������Ҷ�ӽڵ�
			//��ʾ�ڵ�������Ҷ�ӽڵ�(��������ʽ����ʾ�Ľڵ�)	
			pTmpEdge=new Edge(start,0,m_activeNode.m_pNode,this);//endΪ0ʱ��ʾҶ�ӽڵ� 
			m_activeNode.m_pNode->addEdge(pTmpEdge);
			
			#ifdef Debug
				#ifdef add_node 
					int endPos=0;
					if(m_activeNode.m_bImplicit)
						endPos=m_activeNode.getEdge()->getEndPos();
					else if(m_activeNode.m_pNode!=m_pRoot)
						endPos=m_activeNode.m_pNode->getFrontEdge()->getEndPos();
					printf("\nnew:\n %d-(%d,%d '%s'--'%s')\n\n",endPos,
						start,start+1,subData(endPos-1,1).c_str(),subData(pTmpEdge->getStartPos(),pTmpEdge->charSize()).c_str());
				#endif
			#endif

			//ƥ����̵ĺ�׺
			//�жϺ�׺ָ���Ƿ����
			if(m_activeNode.m_pNode->hasNextSuffixPointer())
			{
				m_activeNode.setExplicitNode(m_activeNode.m_pNode->getNextSuffix());
			}
			//�����������ֶ�������һ�����̺�׺
			else	
			{	
				//4.��ǰ��׺�Ѿ�Ϊ���ڵ�(������),�˳�
				if(m_activeNode.m_pNode==m_pRoot)//!!!
					bMatched=true;
				else
				{
					CharPosition pos;
					pTmpNode=m_activeNode.m_pNode;
					//Ҫ���ҵĸ��̺�׺
					string str;
					/*������δ�ʱm_activeNodeΪ��ʾ�ڵ�
					//(��ʼ���Ǹ��ڵ��µ�)�����ڵ�
					if(m_activeNode.m_bImplicit)//pTmpEdge==NULL
					{
						pTmpEdge=m_activeNode.getEdge();
						str=subData(pTmpEdge->getStartPos(),m_activeNode.m_nImplicitNodeOffsetInEdge);
					}//*/
					while( (pTmpEdge=pTmpNode->getFrontEdge()) != NULL )
					{
						str.insert(0,subData(pTmpEdge->getStartPos(),pTmpEdge->charSize()));
						pTmpNode=pTmpEdge->getFrontNode();
						if(pTmpNode==m_pRoot)//�ҵ����ڵ�����ı�
						{
							break;
						}
					}
					str.erase(0,1);
					//������ʱ�������!!!
					//str=this->subData(pTmpEdge->getStartPos()+1,matchePos-(pTmpEdge->getStartPos()+1));

					if(str.length()==0)//��ʾû�и��̵ĺ�׺��,�����ڵ���Ϊ����ڵ�
					{
						m_activeNode.setExplicitNode(m_pRoot);
					}
					else if(search(str,pTmpNode,pos))//�ض����ҵ�,���ҵ������,��ʽ�ڵ㷵��ֵpTmpNodeΪ���ڵ�ָ��
					{
						m_activeNode.m_pNode=pTmpNode;
						m_activeNode.m_nImplicitNodeEdge=pos.edgeIndex;
						m_activeNode.m_bImplicit=pos.bImplicit;
						m_activeNode.m_nImplicitNodeOffsetInEdge=pos.charIndex;
					
					}
					else
					{
						if(str.length()>20)
							str=str.substr(0,10)+"..."+str.substr(str.length()-10);
						printf("-------------- error: when search '%s' -----------\n",str.c_str());	

						m_activeNode.setExplicitNode(m_pRoot);
					}
				}
			}		
		}//end of else
	}//end of while
}
/*����
 *����ֵpParentNodeΪ�ҵ��ڵ�ĸ��ڵ�
 *����ֵfoundPosΪ�ҵ��ִ��ڱ��е�λ��*/
bool SuffixTree::search(string& strToSearch,Node*& pParentNode,CharPosition& foundPos)
{
	Edge *pEdge=NULL;
	pParentNode=m_pRoot;

	unsigned int i,j,charLen,edgeNum;				
	unsigned int matchNum=strToSearch.length();//end-start;
	bool bToMatchNextNode=false;
	foundPos.matchedPos=0;//�ܹ�ƥ���ַ���
	
	//����ƥ��
	while(pParentNode!=NULL)
	{
		edgeNum=pParentNode->getChildNum();
		//1.��Ҷ�ӽڵ㻹δ�ҵ�
		if(edgeNum==0)
		{
			return false;
		}
		//�������б�(���Ż�Ϊ���ַ�)
		for(i=0;i<edgeNum;i++)
		{
			pEdge=pParentNode->getChildEdge(i);
			#ifdef Debug
				if(for_search)
				{
					if(bToMatchNextNode)
						printf(">>>>>>>>>>>>> to match next... >>>>>>>>>>>>>\n");
					else
						printf("/******************************************/\n");
					printf("edge-head: positon=%d,value='%s'\n",pEdge->getStartPos(),subData(pEdge->getStartPos(),1).c_str());
				}
			#endif
			bToMatchNextNode=false;		
			//ƥ����������ַ�
			charLen=pEdge->charSize();
			for(j=0;j<charLen && foundPos.matchedPos<matchNum;j++)
			{
				if(!isDataEqual(strToSearch.substr(foundPos.matchedPos,1),pEdge->getStartPos()+j))//strToSearch[j]
				{
					break;
				}
				else
					foundPos.matchedPos++;
			}
			if(j!=0)
			{
				foundPos.charIndex=j-1;//�ڸñߵ�ƫ��
				foundPos.edgeIndex=i;//�߱��
				//4.�Ѱ���,���ҵ�
				if(foundPos.matchedPos==matchNum)
				{
					if(j==charLen)
					{
						pParentNode=pEdge->getNextNode();
						foundPos.bImplicit=false;
					}
					else
						foundPos.bImplicit=true;
					return true;
				}
				//2.û��ƥ�䵽������,�����߲�����ƥ��,���Զ϶�������
				if(j!=charLen)
				{	
					return false;
				}
				else//j==charLen
				{
					pParentNode=pEdge->getNextNode();//ƥ����һ���ڵ�
					bToMatchNextNode=true;
					break;
				}
			}
			//else if(j==0) ƥ�䱾�ڵ���һ����
		}
		//3.û��ƥ�䵽�κα�,�¼ӽڵ�
		if(!bToMatchNextNode)
		{
			return false;
		}
	}
	return false;
}
//����ָ��Ӹ��ı��н�ȡ�Ӵ�
string SuffixTree::subData(unsigned int start,unsigned int num)
{
	unsigned int end=num+start;
	if(start==end)
		return "";	
	string str="",value;
	unsigned int i,totalOffset=0;
	unsigned int offset,size;
	for(i=0; i<dataArray.size(); i++)
	{
		value=dataArray[i];
		totalOffset+=value.length();
		if(start<totalOffset)
		{
			if(end>totalOffset)//��Խ����������
			{
				if(start < (totalOffset-value.length()) )//��������
					str.append(value);
				else
				{
					str.append( value.substr( value.length()-(totalOffset-start) ) );
				}
			}
			else
			{
				if(start < (totalOffset-value.length()) )//��Խ�ĺ��沿��
				{
					offset=0;
					size=end-(totalOffset-value.length());
				}
				else//ͬһ��
				{
					offset=start-(totalOffset-value.length());
					size=end-start;					
				}
				if((value.substr(offset+size,1)[0] & 0x80)>0)
				{	
					//��ascll��
					//printf("%s,%s\n",value.substr(offset+size,1).c_str(),value.substr(offset+size,2).c_str());
					//size+=1;
				}
				str+=value.substr( offset, size);
				break;
			}
		}
	}	
	return str;
}
//�ж�����λ�õ��ַ��Ƿ����
bool SuffixTree::isDataEqual(unsigned int pos1,unsigned int pos2,unsigned int totalOffset)
{
	if(pos1==pos2)
		return true;
	return (subData(pos1,totalOffset)==subData(pos2,totalOffset));
}
bool SuffixTree::isDataEqual(string str,unsigned int pos,unsigned int offset)
{	
	string str2=subData(pos,offset);
	if(str2.length()==0)
	{
		printf("get data null:%d\n",pos);
		return false;
	}
	#ifdef Debug
		if(for_search)
			printf("compare : '%s'=='%s'\n",str.c_str(),str2.c_str());
	#endif

	return (str==str2);
}
void SuffixTree::printNode(Node *pParent)
{
	Node *pNode=NULL;
	Edge *pEdge=NULL;
	unsigned int i,j,charLen,edgeNum;
	queue<Node*> nodeQueue;
	nodeQueue.push(pParent);
	printf("node:\n");
	//��ȱ���
	while(nodeQueue.size()>0)
	{
		//����
		pNode=nodeQueue.front();
		nodeQueue.pop();

		edgeNum=pNode->getChildNum();
		
		//�������б�
		for(i=0;i<edgeNum;i++)
		{
			pEdge=pNode->getChildEdge(i);
			printf("[%s]\n",subData(pEdge->getStartPos(), pEdge->getEndPos()-pEdge->getStartPos()).c_str());
			//���
			nodeQueue.push(pEdge->getNextNode());
		}
	}
	printf("\n");
}
void SuffixTree::printTree()
{
	this->printNode(this->m_pRoot);
}
int SuffixTree::positionOfSubstring(string value)
{	
#ifdef Debug
	for_search=1;
#endif
	CharPosition foundPos;
	Node* pNode;
	long pos=-1;
	bool isFind=this->search(value,pNode,foundPos);
	if(isFind)//�ҵ�
	{		
		if(foundPos.bImplicit)//���ڵ�
			pos=pNode->getChildEdge(foundPos.edgeIndex)->getStartPos()+foundPos.charIndex-value.length();
		else//����
			pos=pNode->getFrontEdge()->getEndPos()-value.length();
	}
	return pos;
}