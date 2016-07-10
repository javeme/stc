#include "SuffixTree.h"

#include "time.h"
#include "File.h"
using namespace bluemeiIO;
#include <iostream>
using namespace std;

class MainClass
{
public:
	void start();
};

void MainClass::start()
{
	cout<<"bluemei提示您:请把测试文本放入test.txt中."<<endl;
	File file("test.txt");
	//file.readAll();
	SuffixTree st("");
	String line="ABABABC";		st.addText(line);/*
	cout<<"正在构造后缀树,请稍后..."<<endl;
	float percent,length=0;
	long total=file.getSize();
	time_t oldTime,currentTime,costTime; 
	time(&oldTime); 
	while(file.readLine(line)>0)
	{
		percent=100*length/total;
		length+=line.length();
		cout<<"正在构造: (done:"<<percent<<"%)"<<endl<<line<<endl;
		st.addText(line); 
	}
	time(&currentTime);
	costTime=currentTime-oldTime;
	//difftime(currentTime,oldTime)
	char time[20]; 
	sprintf(time,"%d小时%d分%d秒",costTime/60/60,costTime/60%60,costTime%60);
	cout<<endl<<"-------------------构造完毕(耗时:"<<time<<")-------------------"<<endl<<endl;//*/
	String s;
	char buffer[100];
	while(s!="exit")
	{
		cout<<"请输入要查找字符串(exit退出):"<<endl;			
		//scanf("%s",buffer);
		cin>>buffer;
		if(cin.fail())
		{
			break;//如何重来clear flush ignore?
		}

		s=String(buffer,strlen(buffer));
		cout<<"index of '"<<s<<"': "<<st.positionOfSubstring(s)<<endl<<endl;
	}
	st.printTree();
}

int main()
{
	MainClass app;
	try{
		app.start();
	}catch(Exception e)
	{
		e.printException();
	}
	return 0;
}
