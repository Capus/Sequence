#include "Sequence.h"
#include <iostream>
#include <fstream>
#include <memory.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

Sequence::Sequence(string filename)
{
	//initialize
	A=T=C=G=len=0;
	ifstream fin;
	fin.open(filename.c_str());
	if(!fin.is_open())	abort();
	string temp;
	while(fin>>temp)
	{
		seq=seq+temp;
		len+=temp.length();
		for(int i=0;i<temp.length();++i)
		{
			if(temp[i]=='A')
				A++;
			else if(temp[i]=='T')
				T++;
			else if(temp[i]=='C')
				C++;
			else if(temp[i]=='G')
				G++;
			else
				cerr<<"unexpected base\n";
		}
	}
	fin.close();
}

int Sequence::length()
{
	return len;
}

int Sequence::numberOf(char base)
{
	switch(base)
	{
		case 'A':return A;
		case 'T':return T;
		case 'C':return C;
		case 'G':return G;
		default:return 0;
	}
}

string Sequence::longestConsecutive()
{
	int max=0,counter=0;
	string result;
	char temp=seq[0];
	for(int i=1;i<len;++i)
	{	
		if(seq[i]==temp)
			counter++;
		else
		{
			if(counter>max)
			{
				max=counter;
				result=seq.substr(i-max,max);
			}
			counter=0;
		}
		temp=seq[i];
	}
	return result;
}

//functional function
bool mycmp(const char *t1,const char*t2)
{
	return strcmp(t1,t2)<0;
}

int myFun(const char *p1,const char *p2)
{
	int i=0;
	while(*p1++==*p2++)
		++i;
	return i;
}

string Sequence::longestRepeated()
{
	int max=0,index=0;
	char **postfix=new char *[len];
	for(int i=0;i<len;++i)
		postfix[i]=&seq[i];
	sort(postfix,postfix+len,mycmp);
	for(int i=0;i<len-1;++i)
	{
		int temp=myFun(postfix[i],postfix[i+1]);
		if(temp>max)
		{
			max=temp;
			index=i;
		}
	}
	string result;
	for(int i=0;i<max;++i)
	{
		result=result+postfix[index][i];
	}
	return result;
}
//extra
/*
string Sequence::longestRepeated()
{
	//to be finished
	int max=0,index=0;
	for(int i=0;i<len-max;++i)
	{
		for(int j=i+1;j<len-max;++j)
		{
			int t1=i,t2=j;
			int counter=0;
			while(seq[t1]==seq[t2])
			{
				counter++;
				t1++,t2++;
			}
			if(counter>max)
			{
				index=t1;
				max=counter;
			}
		}
	}
	string result=seq.substr(index,max);
	return result;
}
*/
/*
string Sequence::longestRepeated()
{
	int max=0;
	int index=0;
	
	int next[len+1]={};

	//int *next=NULL;
	for(int k=1;k<len-max;++k)
	{
		o//next=new int[len+1];
		memset(next,0,sizeof(int)*len+1);
		for(int i=k;i<len;++i)
		{
			int p=next[i];
	
			while(p>0&&seq[p]!=seq[i])
				p=next[p];
	
			if(seq[p]==seq[i])
				next[i+1]=p+1;
	
			else
				next[i+1]=0;
			//find the max
			if(next[i+1]>max)
			{
				max=next[i+1];
				index=i;
			}
		}
		//step test
		cout<<"%"<<double(k/(len-max))<<"has been done"<<endl;
		//delete[]next;//free the memory
	}
	//for(int i=0;i<len+1;++i)cout<<next[i]<<' ';	
	string result=seq.substr(index-max,max);
	return result;
}
*/

