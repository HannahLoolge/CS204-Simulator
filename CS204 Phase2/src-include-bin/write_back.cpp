
#include<bits/stdc++.h>
#include "myARMSim.h"
#include <cstdlib>
#include <cstdio>
#include<string>
using namespace std;


int binstr_to_dec2(string x)
{
	int sum=0;
	//cout<<"x:"<<x<<endl;
	for(int i=4;i>=0;i--)
	{
		int c=x[i];
		sum=sum+(c-48)*pow(2,4-i);
	}
	//cout<<"sum:"<<sum<<endl;
	return sum;
}

/*int binstr_to_decBigEndian(string x)
{
	int sum=0;
	for(int i=0;i<=3;i++)
	{
		int c=x[i];
		sum=sum+(c-48)*pow(2,3-i);
	}
	return sum;
}

string bin_to_hex(string mac_bin)
{
	string mac_code;
	for(int i=0;i<32;i+=4)
	{
		string x=mac_bin.substr(i,4);
		stringstream ss(x);
		int a=binstr_to_dec(x);
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
*/
//writes the results back to register file
void write_back() {
	bitset<32> instword(instruction_word);
	//cout<<instword<<endl;
	//cout<<"++++++"<<instword<<endl;
	string s_instword = instword.to_string();
	//cout<<s_instword<<endl;
	//string opcode = s_instword.substr(25, 7);
	//cout<<"opcode"<<opcode<<endl;
	//cout<<"WB"<<iAccess<<endl;
	//opcode="0000011";
	string imm;
	string rs1;
	string rd;
	string rs2;
	string imm2;
	string imm1;
	if(opcode=="1101111"||(opcode=="1100111"&&funct3=="000"))//jal and jalr
	{
	
		rd = s_instword.substr(20,5);
		//cout<<"rd"<<rd<<endl;
		int iRd=binstr_to_dec2(rd);
		if(iRd!=0)
			R[iRd]=ry;
		cout<<"WRITE "<<ry<<"to R"<<iRd<<endl;
		cout<<"R[iRd]:"<<R[iRd]<<endl;
		
	}
	else if(opcode=="0000011" || opcode=="0010011"||opcode=="0011011" || opcode=="1100111")//for immediate
	{
		rd = s_instword.substr(20,5);
		//cout<<"rd"<<rd<<endl;
		int iRd=binstr_to_dec2(rd);
		if(iRd!=0)
		R[iRd]=ry;
		cout<<"WRITE "<<ry<<"to R"<<iRd<<endl;
		cout<<"R[iRd]:"<<R[iRd]<<endl;
	}
	else if(opcode=="0110011")//R format
	{
		rd = s_instword.substr(20,5);
		//cout<<"rd"<<rd<<endl;
		int iRd = binstr_to_dec2(rd);
		if(iRd!=0)
		R[iRd]=ry;
		
		cout<<"WRITE "<<ry<<" to R"<<iRd<<endl;
		cout<<"R[iRd]:"<<R[iRd]<<endl;
		
	}
	else if(opcode=="0010111" || opcode=="0110111" )//U 
	{
		rd = s_instword.substr(20,5);
		int iRd = binstr_to_dec2(rd);
		if(iRd!=0)
		R[iRd]=RB;		
		cout<<"WRITE "<<ry<<" to R"<<iRd<<endl;
	}
	
}

