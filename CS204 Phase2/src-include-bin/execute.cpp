#include<iostream>
#include"execute.hpp"
#include"main_control.hpp"
#include"alu.hpp"
#include"myARMSim.h"
using namespace std;

extern string opcode;

void execute()
{
	//cout<<"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"<<opcode<<endl;
	//cout<<instruction_word<<endl;
	if(opcode=="0010111"||opcode=="0110111"||opcode=="1101111")
	{
		if(opcode=="1101111")
		{
			PCSRC=1;
			cout<<"No operation in ALU"<<endl;
		}
		return;
	}		
	string func_3=funct3;
	string func_7=funct7;
    main_control mc( func_3, func_7);
  //  cout<<"i returned"<<endl;
//     mc.Mem_write();
//     cout<<"hello"<<endl;
//    mc.Mem_read();
//     mc.MemtoReg();
//     mc.branch();
//     mc.ALU_Op();
//    mc. ALU_Control();
  cout<<ALU(mc.alu_cntrl_sgnl)<<endl;
}



