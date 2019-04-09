
#include<iostream>
#include"main_control.hpp"
#include<string>
#include<cmath>
using namespace std;

extern string opcode;


main_control::main_control( string func_31, string func_71)
    {
        
     
       func_3=func_31;
       func_7=func_71;
        //cout<<opcode<<endl;
        //cout<<func_3<<endl;
        //cout<<func_7<<endl;

    //    return ;
     Mem_write();
     //cout<<"hello_guru";
      //cout<<"mem_write:"<<mem_write<<endl;

    Mem_read();
       //cout<<"mem_read"<<mem_read<<endl;
     MemtoReg();
      //cout<<"mem_to_reg"<<mem_to_reg<<endl;
     branch();
     //cout<<"br"<<br<<endl;
     //cout<<"Meghana"<<alu_op<<"Reddy"<<endl;
    ALU_Op();
     //cout<<"alu_op"<<alu_op<<endl;
      //cout<<"ffun"<<endl;
       alu_cntrl_sgnl=  ALU_Control();
      /*  cout<<"alu_cntrl_sgnl:"<<alu_cntrl_sgnl;*/
    }
int main_control:: Mem_write()
    {
        
        if(opcode=="0100011")       // opcode for store instruction
        {
           
           
            mem_write=1;
        }
        //cout<<"hellodude"<<endl;
        //cout<<mem_write;
        //cout<<"thambi"<<endl;
     //return mem_write;
    }

int main_control:: Mem_read()
    { 
                    // load instruction
        if(opcode=="0000011" && (func_3=="000" || func_3=="001" || func_3=="010" || func_3=="011" || func_3=="100" || func_3=="101" || func_3=="110"))
        {
            mem_read=1;
            return mem_read;
        }
     //   return mem_read;
    }

int main_control:: MemtoReg()
    {
        
        if(Mem_read()==1 )
        {
            mem_to_reg=1;           // For load instruction
            return mem_to_reg;
        }
      //  return mem_to_reg;   
    }

int main_control:: branch()
    {
        
        if(opcode=="1100011")
        {
            br=1;
            return br;
        }
      //  return br;
    }

string main_control:: ALU_Op()
    {
	//cout<<"i entered alu_op()"<<endl;
        if(mem_read==1 || mem_write==1)     //this tells that the instruction is either load or store. So, in this case we perform addition operation in ALU
            alu_op="00";
        else if(br==1)                    //Branch instruction
            alu_op="01"; 
        else if(opcode=="0010011"&&(func_3=="010"||func_3=="011") || (opcode=="0110011"&&(func_3=="010"||func_3=="011")))    //slti and sltiu instructions 
        {
            if(func_3=="010" || func_3=="011")
                alu_op="11";
        }    
        else                                    // it checks for both func_3 and func_7
            alu_op="10";
//cout<<alu_op<<endl;
	//cout<<"i exited alu_op()"<<endl;

        return alu_op;            
    }

string main_control:: ALU_Control()
    {
	//cout<<"alu_op"<<alu_op<<endl;

        if(alu_op=="00")                        //load and store instructions
		    alu_cntrl_sgnl="0000";

	    else if(alu_op=="01")                   //branch
	    {
		    if(func_3=="000")                   //beq
			    alu_cntrl_sgnl="0010";
	    	else if(func_3=="001")               //bne
		    	alu_cntrl_sgnl="0011";
	    	else if(func_3=="100")               //blt
	    		alu_cntrl_sgnl="0100";
		    else if(func_3=="101")               //bge
		    	alu_cntrl_sgnl="0101";
		    else if(func_3=="110")               //bltu
		    	alu_cntrl_sgnl="0100";
		    else                                //bgeu
			    alu_cntrl_sgnl="0101";
	    }

        else if(alu_op=="10")
        {
            		if(func_3=="000")
		    {
			    if(func_7=="0100000")
				
				    alu_cntrl_sgnl="0001";          //sub
			    else if(func_7=="0000001")
				    alu_cntrl_sgnl="0111";          //mul
			    else
				    alu_cntrl_sgnl="0000";          //add
		    }

		    else if(func_3=="010"||func_3=="011")
			    alu_cntrl_sgnl="0111";             // mult
		
            else if(func_3=="111")
            {
                if(func_7=="0000001")
                alu_cntrl_sgnl="1111";           //remainder
                else
                alu_cntrl_sgnl="1001";            //and
            }

            else if(func_3=="110")
            {
                if(func_7=="0000001")
                alu_cntrl_sgnl="1111";            //remainder
                else 
                alu_cntrl_sgnl="1000";             //or
                
            }

            else if(func_3=="100")
            {
                if(func_7=="0000001")
                alu_cntrl_sgnl="0110";    //division
                else
                alu_cntrl_sgnl="1100";    //xor
            }

            else if(func_3=="001")
            {
                if(func_7=="0000001")
                alu_cntrl_sgnl="0111";    //multh
                else
                alu_cntrl_sgnl="1101";    //shift logical left (slli)
            }

            else if(func_3=="101")
            {
                if(func_7=="0000000")
                alu_cntrl_sgnl="1011";      //srli
                else if(func_7=="0100000")
                alu_cntrl_sgnl="1010";      //srai
                else if(func_7=="0000001")
                alu_cntrl_sgnl="0110";       //division
            }
        }
        else
	    {
		    if(func_3=="010")                //slt slti
			    alu_cntrl_sgnl="0100";
	    	else if(func_3=="011")           //sltu sltui
		    	alu_cntrl_sgnl="0100";
    	}

//cout<<"alu_cntrl_sgnl"<<alu_cntrl_sgnl<<endl;
return alu_cntrl_sgnl;


    }


