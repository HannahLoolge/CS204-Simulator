
/* 

The project is developed as part of Computer Architecture class
Project Name: Functional Simulator for subset of RISCV Processor

Developer's Name:
Developer's Email id:
Date: 

*/


/* myRISCVSim.cpp
   Purpose of this file: implementation file for myRISCVSim
*/
#include<bits/stdc++.h>
#include "myARMSim.h"
#include"execute.hpp"
#include <cstdlib>
#include <cstdio>
#include<string>
using namespace std;
int ni=0;
//Register file
 unsigned int R[32];
//flags
int N,C,V,Z;

int ry, RZ;
//memory
 unsigned char MEM[4000];

//intermediate datapath and control path signals
 unsigned int instruction_word;
  unsigned int operand1;
 unsigned int operand2;
 signed int jump_imm_offset;
 unsigned int PCSRC;
 unsigned int PC_count;
 unsigned int PC_add;
 unsigned int return_add;
 int ifunct3;
 int ifunct7;
 int iopcode;
 string funct3;
 string funct7;
 string opcode;
 int iRA;
 int iRB;
 int iRd;
 int iRM;
 int RA;
 int RB;
 string operation;
int read_byte(unsigned char *mem, unsigned int address);
int read_hw(unsigned char *mem, unsigned int address);
int read_dw(unsigned char *mem, unsigned int address);
void write_byte(unsigned char *mem, unsigned int address, uint8_t data);
void write_hw(unsigned char *mem, unsigned int address, uint16_t data);
void write_dw(unsigned char *mem, unsigned int address, unsigned long long int data);

int binstr_to_dec(string x)
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

int binstr_to_decBigEndian(string x)
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

 
 void run_RISCVsim() {
  while(1) {
    fetch();
    
   decode();
   //cout<<"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"<<opcode<<endl;
   if(N==1||ni==45)
   {
	  break;
   }
   	PCSRC=0;
    execute();
    mem();
    write_back();
    
	cout<<endl;
	//ni++;
  }
  
  for(int i=0; i<32 ; i++)
	{
		cout<<"R["<<i<<"] = "<<R[i]<<"\t";
		//printf("intitalise hua");
		
	}
	
	cout<<endl<<endl;
  
  for(int j=0; j<4000; j++)
	{
		if(MEM[j]!=0)
		printf("MEM [%d] = %x		",j,MEM[j]);
		
	}
	cout<<endl;
}

// it is used to set the reset values
//reset all registers and memory content to 0
void reset_proc() {
	for(int i=0; i<32 ; i++)
	{
		R[i]=0;
		//printf("intitalise hua");
		
	}
	for(int j=0; j<4000 ; j++)
	{
		MEM[j]='\0';
		
	}

}

//load_program_memory reads the input memory, and pupulates the instruction 
// memory
void load_program_memory(char *file_name) {
  FILE *fp;
  unsigned int address, instruction;
  fp = fopen(file_name, "r");
  if(fp == NULL) {
    printf("Error opening input mem file\n");
    exit(1);
  }
  while(fscanf(fp, "%x %x", &address, &instruction) != EOF) {
	  //printf("%x       %x        ",address, instruction);
    write1_word(MEM, address, instruction);
  }
  fclose(fp);
  for(int i=0; i<32 ; i++)
	{
		R[i]=0;
		if(i==2)
		{
			R[i]=3996;
		}
		//printf("intitalise hua");
		
	}
	for(int j=0; j<4000; j++)
	{
		//if(MEM[j]!=0)
		//printf("MEM [%d] = %d		",j,MEM[j]);
		
	}
	jump_imm_offset=0;
	PCSRC=0;
	PC_count=0;
	PC_add=0;
	N=0;
	//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$  N  "<<N<<endl;
}
/*
//writes the data memory in "data_out.mem" file
void write_data_memory() {
  FILE *fp;
  unsigned int i;
  fp = fopen("data_out.mem", "w");
  if(fp == NULL) {
    printf("Error opening dataout.mem file for writing\n");
    return;
  }
  
  for(i=0; i < 4000; i = i+4){
    fprintf(fp, "%x %x\n", i, read_word(MEM, i));
  }
  fclose(fp);
}

//should be called when instruction is swi_exit
void swi_exit() {
  write_data_memory();
  exit(0);
}
*/

int PC_generator()
{
	//cout<<"in pc generator"<<endl;
	//cout<<"PCSRC "<<PCSRC<<endl;
	//return_add = PC_count+4;
	//cout<<return_add<<"****************************************************************************"<<endl;
	if(PCSRC==1)
	{
		//cout<<"jjjjjjjjjjjjjjjjjjjj"<<jump_imm_offset<<endl;
		//cout<<"pppppppppppppppppppp"<<PC_count<<endl;
		
		//cout<<return_add<<"****************************************************************************"<<endl;
		PC_count = PC_count + jump_imm_offset - 4;
	}
	if(opcode=="1100111" && funct3=="000")
	{
		PC_count = RZ;
		//cout<<RZ<<endl;
	}
	
			
}


//executes the ALU operation based on ALUop
//void execute() {}
//perform the memory operation
//void mem() {}
//writes the results back to register file
//void write_back() {}


int read1_word(unsigned char *mem, unsigned int address) {
  int *data;
  data =  (int*) (mem + address);
  //cout<<"data++++++++"<<(*(data))<<endl;
  return *data;
}

void write1_word(unsigned char *mem, unsigned int address, unsigned int data) {
  int *data_p;
  data_p = (int*) (mem + address);
  *data_p = data;
}
