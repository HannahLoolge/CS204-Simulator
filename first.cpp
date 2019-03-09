#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

int main()
{
	ifstream myfile;
	myfile.open("example.asm");
	string line;
	while( getline(myfile,line) )
	{
		stringstream ss(line);
		
		string instruction;
		string firstParam; //firstParameter
		string secondParam; //second parameter
		string thirdParam; //third parameter
		
		ss>>instruction>>firstParam>>secondParam>>thirdParam;
		//comma append ho rha h
		//cout<<instruction<<firstParam<<secondParam<<thirdParam<<endl;
	}
}
