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
	//广度遍历
	while(nodeQueue.size()>0)
	{
		//出队
		pNode=nodeQueue.front();
		nodeQueue.pop();

		edgeNum=pNode->getChildNum();
		
		//遍历所有边
		for(i=0;i<edgeNum;i++)
		{
			pEdge=pNode->getChildEdge(i);
			//入队
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
	//预处理文本,比如分句等
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
	dataArray.push_back(data);//保存原始数据到数组
	
	//加入每个新前缀
	for(i=m_nEndPosition;i<totalOffset;i++)
	{
		//取前缀的最后一个字符,更新
		m_nEndPosition++;//注意:叶子节点不需要再更新,由于创建叶子节点时结束位置设置为m_nEndPosition了
		updateTree(i);		
	}	
}
//将start位置的字符插入到树中
void SuffixTree::updateTree(unsigned int start)
{	
	Node *pTmpNode;
	Edge *pEdge, *pTmpEdge;
	unsigned int i,edgeNum;
	unsigned int matchePos=0;//要匹配的位置	
	bool bMatched=false;
	m_pOldNode=NULL;

	#ifdef Debug
		#ifdef add_node 
			printf("<<<<<<<<<<<<<< '%s' >>>>>>>>>>>>>>>>\n",subData(start,1).c_str());
		#endif
	#endif
	//搜索节点是否包含待加入字符
	while(!bMatched)
	{			
		//活动节点:隐含节点为激活节点,或者本身为激活节点
		//注意活动节点是非叶节点
		//1.匹配整个后缀,即结束节点
		//如果是隐含节点
		if(m_activeNode.m_bImplicit)
		{
			matchePos=m_activeNode.getImplicitPosition()+1;
			if(isDataEqual(start,matchePos))
			{
				bMatched=true;//退出,因为更短的后缀也肯定是匹配的
			}
		}
		//显示节点
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
			//更新激活节点
			m_activeNode.increaseImplicitNodeOffset(i);//可能显隐互变?
		}
		//最后字符不匹配
		else
		{
			//2.隐式节点,拆分节点,并添加叶节点
			if(m_activeNode.m_bImplicit)
			{
				//拆分:				
				pEdge=m_activeNode.getEdge();//上面边
				//添加1个节点
				pTmpNode=new Node(pEdge);//中间节点
				//拆分为2条边
				pTmpEdge=new Edge(matchePos,pEdge->getVirtualEndPos(),pTmpNode,this);//下面边

				pEdge->updateEndPosition(matchePos);//若是叶子节点时,从此摆脱叶子节点
				pTmpEdge->setNextNode(pEdge->getNextNode());
				pEdge->getNextNode()->setFrontEdge(pTmpEdge);//分割时忘了把子节点的父亲边改为下面边!!!
				pEdge->setNextNode(pTmpNode);				
				pTmpNode->addEdge(pTmpEdge);
				
				//隐式节点变显示节点,并作为激活节点(有点牵强?)
				m_activeNode.setExplicitNode(pTmpNode);
				//后缀链接
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
			//3.显示节点,仅在显示节点下新增叶子节点
			//显示节点下新增叶子节点(含上面隐式变显示的节点)	
			pTmpEdge=new Edge(start,0,m_activeNode.m_pNode,this);//end为0时表示叶子节点 
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

			//匹配更短的后缀
			//判断后缀指针是否存在
			if(m_activeNode.m_pNode->hasNextSuffixPointer())
			{
				m_activeNode.setExplicitNode(m_activeNode.m_pNode->getNextSuffix());
			}
			//若不存在则手动搜索下一个更短后缀
			else	
			{	
				//4.当前后缀已经为根节点(非隐含),退出
				if(m_activeNode.m_pNode==m_pRoot)//!!!
					bMatched=true;
				else
				{
					CharPosition pos;
					pTmpNode=m_activeNode.m_pNode;
					//要查找的更短后缀
					string str;
					/*无论如何此时m_activeNode为显示节点
					//(开始就是根节点下的)隐含节点
					if(m_activeNode.m_bImplicit)//pTmpEdge==NULL
					{
						pTmpEdge=m_activeNode.getEdge();
						str=subData(pTmpEdge->getStartPos(),m_activeNode.m_nImplicitNodeOffsetInEdge);
					}//*/
					while( (pTmpEdge=pTmpNode->getFrontEdge()) != NULL )
					{
						str.insert(0,subData(pTmpEdge->getStartPos(),pTmpEdge->charSize()));
						pTmpNode=pTmpEdge->getFrontNode();
						if(pTmpNode==m_pRoot)//找到根节点下面的边
						{
							break;
						}
					}
					str.erase(0,1);
					//不连续时会出问题!!!
					//str=this->subData(pTmpEdge->getStartPos()+1,matchePos-(pTmpEdge->getStartPos()+1));

					if(str.length()==0)//表示没有更短的后缀了,将根节点作为激活节点
					{
						m_activeNode.setExplicitNode(m_pRoot);
					}
					else if(search(str,pTmpNode,pos))//必定能找到,查找到结果后,隐式节点返回值pTmpNode为父节点指针
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
/*查找
 *返回值pParentNode为找到节点的父节点
 *返回值foundPos为找到字串在边中的位置*/
bool SuffixTree::search(string& strToSearch,Node*& pParentNode,CharPosition& foundPos)
{
	Edge *pEdge=NULL;
	pParentNode=m_pRoot;

	unsigned int i,j,charLen,edgeNum;				
	unsigned int matchNum=strToSearch.length();//end-start;
	bool bToMatchNextNode=false;
	foundPos.matchedPos=0;//总共匹配字符数
	
	//搜索匹配
	while(pParentNode!=NULL)
	{
		edgeNum=pParentNode->getChildNum();
		//1.到叶子节点还未找到
		if(edgeNum==0)
		{
			return false;
		}
		//搜索所有边(可优化为二分法)
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
			//匹配边上所有字符
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
				foundPos.charIndex=j-1;//在该边的偏移
				foundPos.edgeIndex=i;//边编号
				//4.已包含,即找到
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
				//2.没有匹配到整条边,其它边不可能匹配,所以断定不存在
				if(j!=charLen)
				{	
					return false;
				}
				else//j==charLen
				{
					pParentNode=pEdge->getNextNode();//匹配下一个节点
					bToMatchNextNode=true;
					break;
				}
			}
			//else if(j==0) 匹配本节点下一条边
		}
		//3.没有匹配到任何边,新加节点
		if(!bToMatchNextNode)
		{
			return false;
		}
	}
	return false;
}
//根据指针从各文本中截取子串
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
			if(end>totalOffset)//跨越两个或以上
			{
				if(start < (totalOffset-value.length()) )//两个以上
					str.append(value);
				else
				{
					str.append( value.substr( value.length()-(totalOffset-start) ) );
				}
			}
			else
			{
				if(start < (totalOffset-value.length()) )//跨越的后面部分
				{
					offset=0;
					size=end-(totalOffset-value.length());
				}
				else//同一个
				{
					offset=start-(totalOffset-value.length());
					size=end-start;					
				}
				if((value.substr(offset+size,1)[0] & 0x80)>0)
				{	
					//非ascll码
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
//判断两个位置的字符是否相等
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
	//广度遍历
	while(nodeQueue.size()>0)
	{
		//出队
		pNode=nodeQueue.front();
		nodeQueue.pop();

		edgeNum=pNode->getChildNum();
		
		//遍历所有边
		for(i=0;i<edgeNum;i++)
		{
			pEdge=pNode->getChildEdge(i);
			printf("[%s]\n",subData(pEdge->getStartPos(), pEdge->getEndPos()-pEdge->getStartPos()).c_str());
			//入队
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
	if(isFind)//找到
	{		
		if(foundPos.bImplicit)//父节点
			pos=pNode->getChildEdge(foundPos.edgeIndex)->getStartPos()+foundPos.charIndex-value.length();
		else//本身
			pos=pNode->getFrontEdge()->getEndPos()-value.length();
	}
	return pos;
}