#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdlib.h>
#include <string>
using namespace std;

class Sequence
{
public:
	//basic
	Sequence(string);
	int length();
	int numberOf(char);
	string longestConsecutive();
	string longestRepeated();
	//extra
private:
	int A,T,C,G;
	int len;
	string seq;
};

#endif
