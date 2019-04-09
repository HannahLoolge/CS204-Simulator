
#include<bits/stdc++.h>
#include "myARMSim.h"
#include <cstdlib>
#include <cstdio>
#include<string>
using namespace std;

int read_byte(unsigned char *mem, unsigned int address);
int read_hw(unsigned char *mem, unsigned int address);
int read_dw(unsigned char *mem, unsigned int address);
void write_byte(unsigned char *mem, unsigned int address, uint8_t data);
void write_hw(unsigned char *mem, unsigned int address, uint16_t data);
void write_dw(unsigned char *mem, unsigned int address, unsigned long long int data);

int read_word(unsigned char *mem, unsigned int address);
void write_word(unsigned char *mem, unsigned int address, unsigned int data);


int binstr_to_dec3(string x)
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

void mem() 
{	
	//cout<<"Hey ya i see you"<<endl;
	bitset<32> instword(instruction_word);
	//cout<<"++++++instword"<<instword<<endl;
	string s_instword = instword.to_string();
	//cout<<s_instword<<endl;
	//string opcode = s_instword.substr(25, 7);
	//cout<<"opcode"<<opcode<<endl;
	string func3 = s_instword.substr(17,3);
	//cout<<"func3"<<func3<<endl;
	
	
	string imm;
	string rs1;
	string rd;
	string rs2;
	string imm2;
	string imm1;
	ry=RZ;
	
	if(opcode=="1101111"||(opcode=="1100111"&&func3=="000"))
	{
		cout<<"no operation in memory stage"<<endl;
		ry=return_add;
		//cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<ry<<endl;
		//return;
	}
	//opcode="0100011";
	//func3="010";
	//MEM[32]=255;
	//MEM[33]=1;
	//MEM[34]=1;
	//MEM[35]=1;
	//MEM[36]=1;
	//MEM[37]=1;
	//MEM[38]=1;
	//MEM[39]=1;

	//opcode="0100011";
	 //func3="001";
	else if(opcode=="0000011" && func3=="010")//for lw
	{
		//cout<<"------------------------------"<<endl;
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
		//int iRs = binstr_to_dec3(rs1);
		//int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs]+iImm;
		//iAccess=32;
		ry = read_word(MEM,RZ);
		cout<<"loading  from memory address at :"<<RZ<<endl;
		//cout<<ry<<"ry2"<<endl;
	//cout<<"helloq"<<endl;
		
	}
	else if(opcode=="0000011" && func3=="000")//lb 
	{
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
		//int iRs = binstr_to_dec3(rs1);
		//int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs]+iImm;
		//iAccess=32;
		ry = read_byte(MEM, RZ);
		cout<<"loading  from memory address at :"<<RZ<<endl;
		//cout<<ry<<endl;
	//cout<<"hellop"<<endl;

	}
	else if(opcode=="0000011" && func3=="001")//lhw
	{

		//cout<<"------------------"<<endl;
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
		//int iRs = binstr_to_dec3(rs1);
		//int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs]+iImm;
		//iAccess=32;
		ry = read_hw(MEM,RZ);
		cout<<"loading  from memory address at :"<<RZ<<endl;
		//cout<<ry<<endl;
	//cout<<"hellot"<<endl;

	}
	if(opcode=="0000011" && func3=="011")//ld
	{
		
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
		//int iRs = binstr_to_dec3(rs1);
		//int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs]+iImm;
		ry = read_dw(MEM, RZ);
		cout<<"loading  from memory address at :"<<RZ<<endl;
		//cout<<ry<<endl;
	//cout<<"helloe"<<endl;

	}
	else if(opcode=="0000011" && func3=="100")//lbu
	{
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
		//int iRs = binstr_to_dec3(rs1);
		//int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs]+iImm;
		ry = read_byte(MEM, RZ);
		cout<<"loading  from memory address at :"<<RZ<<endl;
		//cout<<ry<<endl;
	//cout<<"hellos"<<endl;

	}
	else if(opcode=="0000011" && func3=="101")//lhu
	{
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
	//	int iRs = binstr_to_dec3(rs1);
	//	int iImm = binstr_to_dec3(imm);
	//	int iAccess = R[iRs]+iImm;
		ry = read_hw(MEM, RZ);
		cout<<"loading  from memory address at :"<<RZ<<endl;
		//cout<<ry<<endl;
	//cout<<"hellom"<<endl;

	}
	else if(opcode=="0000011" && func3=="110")//for lwu
	{
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
		//int iRs = binstr_to_dec3(rs1);
		//int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs]+iImm;
		ry = read_word(MEM, RZ);
		cout<<"loading  from memory address at :"<<RZ<<endl;
		//cout<<ry<<"ry2"<<endl;
	//cout<<"hellon"<<endl;

	}	
	else if(opcode=="0100011" && func3=="010")//for store operation sw
	{
		imm1 = s_instword.substr(0,7);
		imm2 = s_instword.substr(20,5);
		imm = imm1 + imm2;
		rs1 = s_instword.substr(12,5);
		rs2 = s_instword.substr(7,5);
		int iRs1 = binstr_to_dec3(rs1);
		int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs1]+iImm;
		//iAccess=0;
		int iRs2 = binstr_to_dec3(rs2);
		int daalo = R[iRs2];
		//daalo=6556;
		//MEM[iAccess]=34;
		//iAccess=32;
		//cout<<MEM[iAccess]<<endl;
		write_word(MEM,RZ,daalo);
		cout<<"storing  from memory address at :"<<RZ<<endl;
		//cout<<"helloending"<<MEM[iAccess]<<"i am back"<<endl;
		//printf("hi%dguru",MEM[iAccess]);
		//cout<<"hhhjjj"<<iAccess<<endl;
		//cout<<MEM[iAccess]<<endl;	
	//cout<<"helloa"<<endl;

	}
	if(opcode=="0100011" && func3=="011")//for store operation sd
	{
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
		//int iRs1 = binstr_to_dec3(rs1);
		//int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs1]+iImm;
		int iRs2 = binstr_to_dec3(rd);
		long long int daalo = R[iRs2];
		//daalo=67;
		//MEM[iAccess]=34;
		//cout<<MEM[iAccess]<<endl;
		write_dw(MEM,RZ,daalo);
		cout<<"storing  from memory address at :"<<RZ<<endl;
		//cout<<MEM[iAccess]<<endl;
	//cout<<"hellow"<<endl;

	}
	else if(opcode=="0100011" && func3=="000")//for store operation sb
	{
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
		int iRs1 = binstr_to_dec3(rs1);
		int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs1]+iImm;
		//cout<<"iAccess"<<iAccess<<endl;
		
		int iRs2 = binstr_to_dec3(rd);
		//cout<<"rrrrrr2"<<iRs2<<endl;
		//cout<<"iw   "<<instruction_word;
		//cout<<"rd   "<<rd<<endl;
		uint8_t daalo = R[iRs2];
		//cout<<"uuuuuudddddddddddddddddddddddddddddddddddd"<<daalo<<endl;
		//daalo = 255;
	//	MEM[iAccess]=45;
		//cout<<MEM[iAccess]=34;
		//cout<<MEM[iAccess]<<endl;
		//cout<<"------------------------------"<<RZ<<endl;
		write_byte(MEM,RZ,daalo);
		cout<<"storing  from memory address at :"<<RZ<<endl;
		//cout<<MEM[iAccess]<<endl;
		//printf("ding%dding",MEM[iAccess]);	
	//cout<<"hellos"<<endl;

	}
	else if(opcode=="0100011" && func3=="001")//for store operation sh
	{
		imm = s_instword.substr(0,12);
		rs1 = s_instword.substr(12,5);
		rd = s_instword.substr(20,5);
		int iRs1 = binstr_to_dec3(rs1);
		int iImm = binstr_to_dec3(imm);
		//int iAccess = R[iRs1]+iImm;
		int iRs2 = binstr_to_dec3(rd);
		uint16_t daalo = R[iRs2];
		//daalo = 258;
		//MEM[iAccess]=78;
		//cout<<MEM[iAccess]<<endl;
		write_hw(MEM, RZ,daalo);
		cout<<"storing  from memory address at :"<<RZ<<endl;	
		//cout<<MEM[iAccess]<<endl;
		//cout<<"hellox"<<endl;
	}
	//cout<<"hello"<<endl;;
}


int read_byte(unsigned char *mem, unsigned int address){
	char *data;
	data = (char*) (mem + address);
	int *val;
	val=(int*)data;
	//cout<<"data"<<*data<<endl;
	int x = (*val >> (8*0)) & 0xff;
	
	return x;
}

int read_hw(unsigned char *mem, unsigned int address){
	char *data;
	data = (char*) (mem + address);
	int *val;
	val=(int*)data;
	//cout<<"data"<<*data<<endl;
	int x = (*val >> (8*0)) & 0xffff;
	
	return x;
}

int read_dw(unsigned char *mem, unsigned int address) {
  int *data1,*data2,*data;
  data1 =  (int*) (mem + address);
  //cout<<"data"<<(*(data1))<<endl;
  address+=4;
  data2 = (int*) (mem + address);
  long long int mul = 4294967296;
  mul*=(*(data2));
  int first = *data1;
  int finzz = first+mul;
  //cout<<"lmao"<<endl;
  //cout<<"2"<<*(data2)<<endl;
  return finzz;
}

int read_word(unsigned char *mem, unsigned int address) {
  int *data;
  data =  (int*) (mem + address);
  int x=*data;
  bitset<32> d(x);
  //cout<<"d:"<<d<<endl;
  //cout<<"data++++++++"<<(*(data))<<endl;
  return *data;
}

void write_hw(unsigned char *mem, unsigned int address, uint16_t data) {
  uint16_t *data_p;
  data_p = (uint16_t*) (mem + address);
  *data_p = data;
  //printf("okie %d dokie",*data_p);
  return;
}

void write_byte(unsigned char *mem, unsigned int address, uint8_t data) {
  uint8_t *data_p;
  data_p = (uint8_t*) (mem + address);
  *data_p = data;
  //cout<<"heyy"<<*data_p<<"ding"<<endl;
  //printf("dingchak%ddinchak",*data_p);
  return;
}
//lomng long int
void write_dw(unsigned char *mem, unsigned int address, unsigned long long int data) {
  long long int data2,data1;
  long long int mul = 4294967296;
  data2 = data%mul;
  data1 = data/mul;
  int *data_p;
  data_p = (int*) (mem + address);
  *data_p = data2;
  address-=4;
  data_p = (int*) (mem + address);
  *data_p = data1;
  return;
}

void write_word(unsigned char *mem, unsigned int address, unsigned int data) {
//cout<<"Meghana reddy"<<endl;
  int *data_p;
  data_p = (int*) (mem + address);
  *data_p = data;
  //cout<<" in write_back ";
  //cout<<*(data_p)<<endl;
  //printf("%d",*data_p);
  //printf("%d\n",*(data_p));
  return;
}

