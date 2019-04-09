
#include<bits/stdc++.h>
#include "myARMSim.h"
#include <cstdlib>
#include <cstdio>
#include<string>
using namespace std;

int binstr1_to_dec(string x)
{
	int sum=0;
	for(int i=3;i>=0;i--)
	{
		int c=x[i];
		sum=sum+(c-48)*pow(2,3-i);
	}
	return sum;
}

string bin1_to_hex(string mac_bin)
{
	string mac_code;
	for(int i=0;i<32;i+=4)
	{
		string x=mac_bin.substr(i,4);
		stringstream ss(x);
		int a=binstr1_to_dec(x);
		if(a<=9)
		{
			char c=48+a;	
			mac_code+=c;
		}
		else
		{
			char c=55+a;
			mac_code+=c;
		}
		x="";		
	}
	return mac_code;
		
}

//reads from the instruction memory and updates the instruction register
void fetch() {
	
	PC_generator();
	//cout<<endl<<PC_count<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
	
	instruction_word = (read1_word(MEM,PC_count));
	//cout<<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<instruction_word<<endl;
	
	bitset<32> pc(PC_count);
	
	PC_count= PC_count+4;
	return_add = PC_count;
	//cout<<return_add<<"****************************************************************************"<<endl;
	if(instruction_word==4009754641)
	{
		//cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ N in it"<<N<<endl;
		N=1;
	}
	bitset<32> instword(instruction_word);
	//cout<<"++++++"<<instword<<endl;
	
	
	string istring = instword.to_string();
	string pcstring = pc.to_string();
	cout<<"FETCH:Fetch instruction 0x"<<bin1_to_hex(istring)<<" from address 0x"<<bin1_to_hex(pcstring)<< endl;
}
