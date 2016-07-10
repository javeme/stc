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
	cout<<"bluemei��ʾ��:��Ѳ����ı�����test.txt��."<<endl;
	File file("test.txt");
	//file.readAll();
	SuffixTree st("");
	String line="ABABABC";		st.addText(line);/*
	cout<<"���ڹ����׺��,���Ժ�..."<<endl;
	float percent,length=0;
	long total=file.getSize();
	time_t oldTime,currentTime,costTime; 
	time(&oldTime); 
	while(file.readLine(line)>0)
	{
		percent=100*length/total;
		length+=line.length();
		cout<<"���ڹ���: (done:"<<percent<<"%)"<<endl<<line<<endl;
		st.addText(line); 
	}
	time(&currentTime);
	costTime=currentTime-oldTime;
	//difftime(currentTime,oldTime)
	char time[20]; 
	sprintf(time,"%dСʱ%d��%d��",costTime/60/60,costTime/60%60,costTime%60);
	cout<<endl<<"-------------------�������(��ʱ:"<<time<<")-------------------"<<endl<<endl;//*/
	String s;
	char buffer[100];
	while(s!="exit")
	{
		cout<<"������Ҫ�����ַ���(exit�˳�):"<<endl;			
		//scanf("%s",buffer);
		cin>>buffer;
		if(cin.fail())
		{
			break;//�������clear flush ignore?
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
