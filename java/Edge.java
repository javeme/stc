

public class Node;
public class SuffixTree;

public class Edge
{

// int dataId;
private int start,end;
private Node m_pFrontNode,m_pNextNode;
//隐式节点位置标记
private ArrayList< int> implicitPosOffsetArray;
//后缀树指针,用于叶节点查询最后一个字符位置
private SuffixTree m_pTree;

//public Edge();
//public Edge( int start, int end,Node pFrontNode,SuffixTree pTree);
//public ~Edge();

//public void setPosition( int start, int end);
//public void setFrontNode(Node pFrontNode);
//public void setNextNode(Node pNextNode);
//public void updateEndPosition( int end);
//void setDataId( int dataId);

//public Node getNextNode();
//public Node getFrontNode();
//public int charSize();
//public int getStartPos();
//public int getEndPos();
//public int getVirtualEndPos();
//public void addImplicitPosOffset( int offset);
//public int getImplicitPosition( int index);
//public int getImplicitNodeNum();



Edge()
{
this.setPosition(-1,-1);
this.setFrontNode(null);
this.setNextNode(new Node(this));
}

Edge( int start, int end,Node pFrontNode,SuffixTree pTree)
{
m_pTree=pTree;
this.setPosition(start,end);
this.setNextNode(new Node(this));
this.setFrontNode(pFrontNode);
}
~Edge()
{
//if()m_pFrontNode,m_pNextNode;
;
}
void setPosition( int start, int end)
{
this.start=start;
this.end=end;
}
void setFrontNode(Node pFrontNode)
{
this.m_pFrontNode=pFrontNode;
}
void setNextNode(Node pNextNode)
{
m_pNextNode=pNextNode;
}
void updateEndPosition( int end)
{
this.end=end;
}/
//设置字符串对应的id
void setDataId( int dataId)
{
this.dataId=dataId;
}/
int charSize()
{
return (getEndPos()-start);
}
int getStartPos()
{
return start;
}
int getEndPos()
{
if(end==0)//表示叶节点
return m_pTree.getEndPosition();
return end;
}
//直接返回end,即使是0也不经过转换
int getVirtualEndPos()
{
return end;
}
Node getNextNode()
{
return this.m_pNextNode;
}
Node getFrontNode()
{
return this.m_pFrontNode;
}
void addImplicitPosOffset( int offset)
{
this.implicitPosOffsetArray.push_back(offset);
}
int getImplicitPosition( int index)
{
return implicitPosOffsetArray[index]+start;
}
int getImplicitNodeNum()
{
return implicitPosOffsetArray.size();
}}