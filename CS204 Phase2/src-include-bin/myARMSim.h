#ifndef MYARMSIM_H
#define MYARMSIM_H
/* 

The project is developed as part of Computer Architecture class
Project Name: Functional Simulator for subset of RISCV Processor

Developer's Name:
Developer's Email id:
Date: 

*/


/* myRISCVSim.h
   Purpose of this file: header file for myRISCVSim
*/
//Register file
//#include<bits/stdc++.h>
#include<string>
using namespace std;

extern unsigned int R[32];
//flags
extern int N,C,V,Z;
//memory
extern unsigned char MEM[4000];

//intermediate datapath and control path signals
extern unsigned int instruction_word;
 extern unsigned int operand1;
extern unsigned int operand2;
 extern signed int jump_imm_offset;
extern unsigned int PCSRC;
extern unsigned int PC_count;
extern unsigned int PC_add;
extern unsigned int return_add;

extern int ifunct3;
extern int ifunct7;
extern int iopcode;

extern string funct3;
extern string funct7;
extern string opcode;
extern int iRA;
extern int iRB;
extern int iRd;
extern int iRM;
//extern string operation;
extern int ry, RZ;
extern int RA, RB;

void run_RISCVsim();
void reset_proc();
void load_program_memory(char* file_name);
//void write_data_memory();
//void swi_exit();

int PC_generator();
//reads from the instruction memory and updates the instruction register
void fetch();
//reads the instruction register, reads operand1, operand2 fromo register file, decides the operation to be performed in execute stage
void decode();

void mem();
void write_back();

int read1_word(unsigned char *mem, unsigned int address);
void write1_word(unsigned char *mem, unsigned int address, unsigned int data);
#endif
