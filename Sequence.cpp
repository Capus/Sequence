#include "Sequence.h"
#include <iostream>
#include <fstream>

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

string Sequence::longestRepeated()
{
	int max=0;
	int index=0;
	
	int next[len+1]={};
	next[0]=next[1]=0;
	
	for(int i=1;i<len;++i)
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
	for(int i=0;i<len+1;++i)cout<<next[i]<<' ';	
	string result=seq.substr(index-max,max);
	return result;
}


