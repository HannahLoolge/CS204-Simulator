
#include<bits/stdc++.h>
#include "myARMSim.h"
#include <cstdlib>
#include <cstdio>
#include<string>
using namespace std;

//reads the instruction register, reads operand1, operand2 fromo register file, decides the operation to be performed in execute stage
void decode() {
	iRA=0;
	iRM=0;
	iRd=0;
	iRB=0;
	RA=0;
	RB=0;
	funct3="";
	funct7="";
	opcode="";
	
	bitset<32> instword(instruction_word);
	//cout<<"++++++"<<instword<<endl;
	
	string s_instword = instword.to_string();
	//cout<<s_instword<<endl;
	
 opcode = s_instword.substr(25, 7);
	//cout<<"00000000000000000000000000000000000000000000000000000opcode"<<opcode<<endl;

	bitset<sizeof(int) * 8> b(opcode);
	iopcode = b.to_ulong();
	//cout << b.to_ulong() <<iopcode<< '\n';

	//string funct3, funct7;
	
	if(opcode=="0110011" || opcode=="0111011")          //Decoding R-format instruction
	{
		//cout<<"yes in it"<<endl;
		string  s_rs2, s_rs1, s_rd;
		
		for(int i=20; i<25; i++)
    		{
    			s_rd+=s_instword[i];
    		
    		}
    		//cout<<s_rd<<endl;
    		for(int i=17; i<20; i++)
    		{
    			funct3+=s_instword[i];
    		}
    		//cout<<"funct3"<<funct3<<endl;
    		for(int i=12; i<17; i++)
    		{
    			s_rs1+=s_instword[i];
    		}
    		//cout<<s_rs1<<endl;
    		for(int i=7; i<12; i++)
    		{
    			s_rs2+=s_instword[i];
    		}
    		//cout<<s_rs2<<endl;
    		for(int i=0; i<7; i++)
    		{
    			funct7+=s_instword[i];
    		}
    		//cout<<funct7<<endl;
    		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_rs1<<endl;
		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_rs2<<endl;
		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_rd<<endl;
		bitset<sizeof(int) * 8> ra(s_rs1);
		iRA = ra.to_ulong();
		RA=R[iRA];
		//cout << "3333333333333333333333333"<<ra.to_ulong() <<iRA<< '\n';
		bitset<sizeof(int) * 8> rb(s_rs2);
		iRB = rb.to_ulong();
		RB=R[iRB];
		//cout << "3333333333333333333333333"<<rb.to_ulong() <<iRB<< '\n';
		bitset<sizeof(int) * 8> rd(s_rd);
		iRd = rd.to_ulong();
		//cout << "3333333333333333333333333"<<rd.to_ulong() <<iRd<< '\n';
		
		
	}
	
	
	
	if(opcode=="0010111" || opcode=="0110111")
	{
		//cout<<"yes in it"<<endl;
		string s_imm, s_rd;
	
		for(int i=20; i<25; i++)
    		{
    			s_rd+=s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<s_rd<<endl;
    		for(int i=0; i<20; i++)
    		{
    			s_imm += s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<s_imm<<endl;
    		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_imm<<endl;
	
		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_rd<<endl;
		bitset<sizeof(int) * 8> rimm(s_imm);
		iRB = rimm.to_ulong();
		//cout << "3333333333333333333333333bbbbbbbbbbbbb"<<rimm.to_ulong() <<iRB<< '\n';
		
		bitset<sizeof(int) * 8> rd(s_rd);
		iRd = rd.to_ulong();
		//cout << "3333333333333333333333333"<<rd.to_ulong() <<iRd<< '\n';
		iRA=0;
		RB=iRB;
	}
	if(opcode=="0000011"||opcode=="0100011"||opcode=="0010011"||opcode=="0011011")
	{
		if(opcode=="0100011")
		{
			for(int i=17; i<20; i++)
    			{
    				funct3+=s_instword[i];
    			
    			}
    			//cout<<funct3<<endl;
    			if(funct3=="011")
    			{
    				//mac_bin = s_imm.substr(5,11) + s_rs2  + s_rs1 + funct3 +imm_str + opcode;
				string s_imm5_11, s_rs2, s_rs1, imm_str;
				for(int i=20; i<25; i++)
    				{
    					imm_str+=s_instword[i];
    			
    				}
    				//cout<<imm_str<<endl;
    			
    				for(int i=12; i<17; i++)
    				{
    					s_rs1+=s_instword[i];
    		
    				}
    				//cout<<s_rs1<<endl;
    				for(int i=7; i<12; i++)
    				{
    					s_rs2+=s_instword[i];
    				
    				}
    				//cout<<s_rs2<<endl;
				for(int i=0; i<7; i++)
    				{
    					s_imm5_11+=s_instword[i];
    				
    				}	
    				//cout<<s_imm5_11<<endl;	
    				string s_imm = 	s_imm5_11 + imm_str;
    				
    				//cout<<s_imm<<endl;
    		                //cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_imm<<endl;
	
		                //cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_rs1<<endl;
		                //cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_rs2<<endl;
		                
		                bitset<sizeof(int) * 8> ra(s_rs1);
				iRA = ra.to_ulong();
				RA=R[iRA];
				//cout << "3333333333333333333333333aaaaaaaaaaaaaaaaaaaaaaa"<<ra.to_ulong() <<iRA<< '\n';
				bitset<sizeof(int) * 8> rm(s_rs2);
				iRM = rm.to_ulong();
			//	cout << "3333333333333333333333333mmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<rm.to_ulong() <<iRM<< '\n';
				string s= s_imm.substr(0,1);
				bitset<sizeof(int) * 8> rimm(s_imm.substr(1,11));
				bitset<sizeof(int) * 8> rimm2(s);
				int tempimm = rimm.to_ulong();
			//	cout<<"ttttttttttttttttttttttttttt111111111111111111111111"<<tempimm<<endl;
				int tempimm2 =rimm2.to_ulong();
			//	cout<<"tttttttttttttttttttttttttttt22222222222222222"<<tempimm2<<endl;
				iRB = tempimm - tempimm2*pow(2, 11);
				//cout << "3333333333333333333333333bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"<<rimm.to_ulong() <<iRB<< '\n';				
				RB=iRB;
    				
			}
		}
		if(opcode=="0010011"||opcode=="0011011")
		{
			string  s_imm, s_rs1,  s_rd ;
			for(int i=20; i<25; i++)
    			{
    				s_rd+=s_instword[i];
    			
    			}
    			//cout<<s_rd<<endl;
    			for(int i=17; i<20; i++)
    			{
    				funct3+=s_instword[i];
    			
    			}
    			//cout<<funct3<<endl;
    			for(int i=12; i<17; i++)
    			{
    				s_rs1+=s_instword[i];
    		
    			}
    			//cout<<s_rs1<<endl;
    			int flag=0;
			for(int i=0; i<7; i++)
    			{
    				funct7+=s_instword[i];
    				if(funct7=="0000000"||funct7=="0100000")
    				{
    					flag=1;	
    				}
    			}	
    			//cout<<funct7<<endl;
    			for(int i=7; i<12; i++)
    			{
    				s_imm+=s_instword[i];
    				
    			}
    			if(flag==0)
    			{
    				s_imm = funct7+s_imm;
    				
    			}
    			//cout<<s_imm<<endl;	
    			
    			bitset<sizeof(int) * 8> ra(s_rs1);
			iRA = ra.to_ulong();
			RA=R[iRA];
			//cout << "3333333333333333333333333aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"<<ra.to_ulong() <<iRA<< '\n';
			bitset<sizeof(int) * 8> rd(s_rd);
			iRd = rd.to_ulong();
			//cout << "3333333333333333333333333dddddddddddddddddddddddddddddddddddddddddd"<<rd.to_ulong() <<iRd<< '\n';
			string s= s_imm.substr(0,1);
			bitset<sizeof(int) * 8> rimm(s_imm.substr(1,11));
			bitset<sizeof(int) * 8> rimm2(s);
			int tempimm = rimm.to_ulong();
			int tempimm2 =rimm2.to_ulong();
			iRB = tempimm - tempimm2*pow(2, 11);
			//cout << "3333333333333333333333333mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<rimm.to_ulong() <<iRB<< '\n';		
				RB=iRB;
			//cout<<"rrrraaaaaaaaaaaaaaaaaaaaaa"<<RA<<endl;
			//cout<<"rrrrbbbbbbbbbbbbbbbbbbbbbbb"<<RB<<endl;
			//bitset<sizeof(int) * 8> rimm(s_imm);
			//iRB = rimm.to_ulong();
			//cout << "3333333333333333333333333"<<rimm.to_ulong() <<iRB<< '\n';
		}
		
		
		
	}
	
	
	if(opcode=="0000011")
	{
		//cout<<"yes in it"<<endl;
		string  s_imm, s_rs1, s_rd;
		
		for(int i=20; i<25; i++)
    		{
    			s_rd+=s_instword[i];
    		
    		}
    		//cout<<s_rd<<endl;
    		for(int i=17; i<20; i++)
    		{
    			funct3+=s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<"funct3"<<funct3<<endl;
    		for(int i=12; i<17; i++)
    		{
    			s_rs1+=s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<s_rs1<<endl;
    		for(int i=0; i<12; i++)
    		{
    			s_imm+=s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<s_imm<<endl;
    		
    		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_rs1<<endl;
		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_imm<<endl;
		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_rd<<endl;
		bitset<sizeof(int) * 8> ra(s_rs1);
		iRA = ra.to_ulong();
		//cout << "3333333333333333333333333aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"<<ra.to_ulong() <<iRA<< '\n';
		
		bitset<sizeof(int) * 8> rd(s_rd);
		iRd = rd.to_ulong();
		//cout << "3333333333333333333333333ddddddddddddddddddddddddddddddddddddddd"<<rd.to_ulong() <<iRd<< '\n';
		
		string s= s_imm.substr(0,1);
		bitset<sizeof(int) * 8> rimm(s_imm.substr(1,11));
		bitset<sizeof(int) * 8> rimm2(s);
		int tempimm = rimm.to_ulong();
		int tempimm2 =rimm2.to_ulong();
		iRB = tempimm - tempimm2*pow(2, 11);
		//cout << "3333333333333333333333333mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<rimm.to_ulong() <<iRB<< '\n';
    		RB=iRB;
    		RA=R[iRA];
	}
	
	if(opcode=="1100111")
	{
		//cout<<"yes in it"<<endl;
		string s_imm,s_rs1, s_rd;
	
		for(int i=20; i<25; i++)
    		{
    			s_rd+=s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<s_rd<<endl;
    		for(int i=17; i<20; i++)
    		{
    			s_rd+=s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<s_rd<<endl;
    		for(int i=12; i<17; i++)
    		{
    			s_rs1+=s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<s_rd<<endl;
    		for(int i=17; i<20; i++)
    		{
    			funct3+=s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<"funct3"<<funct3<<endl;
    		for(int i=0; i<12; i++)
    		{
    			s_imm += s_instword[i];
    			//cout<<funct3[i-8]<<inst[i]<<endl;
    		}
    		//cout<<s_imm<<endl;
    		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_imm<<endl;
	
		//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<s_rd<<endl;
		//bitset<sizeof(int) * 8> rimm(s_imm);
		//iRB = rimm.to_ulong();
		//cout << "3333333333333333333333333"<<rimm.to_ulong() <<iRB<< '\n';
		bitset<sizeof(int) * 8> rd(s_rd);
		iRd = rd.to_ulong();
	//	cout << "3333333333333333333333333dddddddddddddddddddddddddddddddd"<<rd.to_ulong() <<iRd<< '\n';
		bitset<sizeof(int) * 8> ra(s_rs1);
		iRA = ra.to_ulong();
		//cout << "3333333333333333333333333aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"<<ra.to_ulong() <<iRA<< '\n';
		string s= s_imm.substr(0,1);
		bitset<sizeof(int) * 8> rimm(s_imm.substr(1,11));
		bitset<sizeof(int) * 8> rimm2(s);
		int tempimm = rimm.to_ulong();
		int tempimm2 =rimm2.to_ulong();
		iRB = tempimm - tempimm2*pow(2, 11);
		//cout << "3333333333333333333333333bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"<<rimm.to_ulong() <<iRB<< '\n';
		RA=R[iRA];
		RB=iRB;
		//jump_imm_offset=iRB+R[iRA];
		
	}
	
	string s_imm2, s_imm1;
	string s_imm;
	string s_rs2, s_rs1;
	string s_rd;
	//cout<<"OKAY OKAY"<<endl;
	//opcode="1101111";
	//s_instword="11111111110111111111000011101111";
	if(opcode=="0100011"){ // S instruction
		s_imm2 = s_instword.substr(0,7);
		s_imm1 = s_instword.substr(20,5);
		s_rs2 = s_instword.substr(7,5);
		s_rs1 = s_instword.substr(12,5);
		funct3 = s_instword.substr(17,3);
		bitset<sizeof(int)*8> ra(s_rs1);
		iRA = ra.to_ulong();
		s_imm = s_imm2 + s_imm1;
		string s= s_imm.substr(0,1);
		bitset<sizeof(int) * 8> rimm(s_imm.substr(1,11));
		bitset<sizeof(int) * 8> rimm2(s);
		int tempimm = rimm.to_ulong();
		int tempimm2 =rimm2.to_ulong();
		iRB = tempimm - tempimm2*pow(2, 11);
		//cout<<"iRA"<<iRA<<endl;
	//	cout<<"iRB"<<iRB<<endl;
		RA= R[iRA];
		RB=iRB; 
		//cout<<"imm2"<<imm2<<endl;
		//cout<<"imm1"<<imm1<<endl;
		//cout<<"rs2"<<rs2<<endl;
		//cout<<"rs1"<<rs1<<endl;
		//cout<<"func3"<<func3<<endl;
	}
	if(opcode=="1100011"){// SB instruction
		s_imm2 = s_instword.substr(0,7);
		s_imm1 = s_instword.substr(20,5);
		s_rs2 = s_instword.substr(7,5);
		s_rs1 = s_instword.substr(12,5);
		funct3 = s_instword.substr(17,3);
		bitset<sizeof(int)*8> ra(s_rs1);
		iRA = ra.to_ulong();
		string s_imm;
		s_imm="0";
		s_imm += s_imm1[4];
		
		for(int i=1; i<7; i++){
			s_imm +=s_imm2[i];
		}
		for(int i=0;i<4; i++)
		{
			s_imm +=s_imm1[i];
		}
		s_imm += s_imm2[0];
		//cout<<s_imm<<"YE HAI"<<endl;
		
		bitset<sizeof(int)*8> rb(s_rs2);
		iRB = rb.to_ulong();
		//cout<<"iRA"<<iRA<<endl;
		//cout<<"iRB"<<iRB<<endl;
		RA = R[iRA];
		RB = R[iRB];
		//cout<<"ra"<<RA<<endl;
		//cout<<"rb"<<RB<<endl;
		
		string s= s_imm.substr(0,1);
		bitset<sizeof(int) * 8> rimm(s_imm.substr(1,12));
		bitset<sizeof(int) * 8> rimm2(s);
		int tempimm = rimm.to_ulong();
		int tempimm2 =rimm2.to_ulong();
		jump_imm_offset = tempimm - tempimm2*pow(2, 12);
		//cout<<"JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"<<jump_imm_offset<<endl;
		
		//cout<<"imm2"<<imm2<<endl;
		//cout<<"imm1"<<imm1<<endl;
		//cout<<"rs2"<<rs2<<endl;
		//cout<<"rs1"<<rs1<<endl;
		//cout<<"func3"<<func3<<endl;
	}
	if(opcode=="1101111"){// UJ instruction
		s_imm = s_instword.substr(0,20);
		s_rd = s_instword.substr(20,5);

		bitset<sizeof(int)*8> ra(4);
		//iRA = ra.to_ulong();
		// string simm;
		bitset<21> bimm;
		bimm[0]=0;
		bimm[20]=s_imm[0]-48;
		for(int h=10;h>=1;h--)
		{
			bimm[h]=s_imm[11-h]-48;
		}
		bimm[11]=s_imm[11]-48;
		for(int h=19;h>=12;h--)
		{
			bimm[h]=s_imm[31-h]-48;
		}
		// s_fin[0] = s_imm[0];
		// for(int i=12; i<=19; i++)
		// {
		// 	s_fin[i-11]=s_imm[i];
		// }
		// s_fin[9]=s_imm[11];
		// for(int i=1; i<=10; i++)
		// {
		// 	s_fin[i+9]=s_imm[i];
		// }
		// s_fin[20]=0;
		// cout<<s_fin<<endl;
		// cout<<s_fin.length();

		string s;//= s_fin.substr(0,1);
		//s= s_fin.substr(0,1);
		s=bimm.to_string();
		//cout<<"?????"<<endl;
		bitset<sizeof(int) * 8> rimm(s.substr(1,20));
		bitset<1> rimm2(bimm[20]);
		//cout<<bimm[0]<<"bimm"<<endl;
		//cout<<"hello"<<endl;
		//cout<<rimm2<<"RIMM2"<<endl;
		int tempimm = rimm.to_ulong();
		int tempimm2 =rimm2.to_ulong();
		jump_imm_offset = tempimm - tempimm2*pow(2, 20);
		//cout<<"jump_offset:"<<jump_imm_offset<<endl;
		//cout<<"iRA"<<iRA<<endl;
		//cout<<"iRB"<<iRB<<endl;
		
		//cout<<"imm"<<imm<<endl;
		//cout<<"rd"<<rd<<endl;
		
	}
	
	
	//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<funct3<<endl;
	//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<funct7<<endl;
	bitset<sizeof(int) * 8> f3(funct3);
	ifunct3 = f3.to_ulong();
	//cout << "3333333333333333333333333"<<f3.to_ulong() <<ifunct3<< '\n';
	bitset<sizeof(int) * 8> f7(funct7);
	ifunct7 = f7.to_ulong();
	//cout << "77777777777777777777777777777"<<f7.to_ulong() <<"77"<<ifunct7<< '\n';
	
	
	
	
	if(opcode=="0110011")
	{
		if(funct3=="000"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is ADD, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		
		if(funct3=="000"&& funct7=="0100000")
		{
			cout<<"DECODE: Operation is SUB, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		
		if(funct3=="001"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is SLL, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
    		
		if(funct3=="010"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is SLT, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="011"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is SLTU, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="100"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is XOR, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="101"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is SRL, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="101"&& funct7=="0100000")
		{
			cout<<"DECODE: Operation is SRA, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="110"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is OR, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="111"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is AND, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="000"&& funct7=="0000001")
		{
			cout<<"DECODE: Operation is MUL, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
	}
	
	if(opcode=="0111011")
	{
		if(funct3=="000"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is ANDW, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="000"&& funct7=="0100000")
		{
			cout<<"DECODE: Operation is SUBW, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="001"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is SLLW, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="101"&& funct7=="0000000")
		{
			cout<<"DECODE: Operation is SRLW, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="101"&& funct7=="0100000")
		{
			cout<<"DECODE: Operation is SRAW, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
	}
	
	if(opcode=="0000011")
	{
		if(funct3=="000")
		{
			cout<<"DECODE: Operation is lb, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="001")
		{
			cout<<"DECODE: Operation is lh, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="010")
		{
			cout<<"DECODE: Operation is lw, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="011")
		{
			cout<<"DECODE: Operation is ld, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="100")
		{
			cout<<"DECODE: Operation is lbu, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="101")
		{
			cout<<"DECODE: Operation is lhu, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		if(funct3=="110")
		{
			cout<<"DECODE: Operation is lwu, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   R"<<iRB<<"="<<R[iRB]<<endl;
		}
		
	}
	if(opcode=="0010011")
	{
		//cout<<"7"<<funct3<<"7"<<endl;
		//cout<<"hhhhhhhhhhhhhhhhhhhhhhlllllllllllllllllllllllllllllllllllllll---------"<<endl;
		if(funct3=="000")
		{
			//cout<<"fffffffffffffffffffffffffffffffffffffffffff---------------"<<endl;
			cout<<"DECODE: Operation is addi, first operand R"<<RA<<" Second operand R"<<RB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<RB<<endl;
		}
		if(funct3=="001"&&funct7=="0000000")
		{
			cout<<"DECODE: Operation is slli, first operand R"<<iRA<<" Second operand "<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<RB<<endl;
		}
		if(funct3=="010")
		{
			cout<<"DECODE: Operation is slti, first operand R"<<iRA<<" Second operand "<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<RB<<endl;
		}
		if(funct3=="011")
		{
			cout<<"DECODE: Operation is sltiu, first operand R"<<iRA<<" Second operand "<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<RB<<endl;
		}
		if(funct3=="100")
		{
			cout<<"DECODE: Operation is xori, first operand R"<<iRA<<" Second operand "<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<RB<<endl;
		}
		if(funct3=="101"&&funct7=="0000000")
		{
			cout<<"DECODE: Operation is srli, first operand R"<<iRA<<" Second operand "<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<RB<<endl;
		}
		if(funct3=="101"&&funct7=="0100000")
		{
			cout<<"DECODE: Operation is srai, first operand R"<<iRA<<" Second operand "<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<RB<<endl;
		}
		if(funct3=="110")
		{
			cout<<"DECODE: Operation is ori, first operand R"<<iRA<<" Second operand "<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<RB<<endl;
		}
		if(funct3=="111")
		{
			cout<<"DECODE: Operation is andi, first operand R"<<iRA<<" Second operand "<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<RB<<endl;
		}
	}
	if(opcode=="0011011")
	{
		if(funct3=="000")
		{
			cout<<"DECODE: Operation is addiw, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
		if(funct3=="001"&&funct7=="0000000")
		{
			cout<<"DECODE: Operation is slliw, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
		if(funct3=="101"&&funct7=="0000000")
		{
			cout<<"DECODE: Operation is srliw, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
		if(funct3=="101"&&funct7=="0100000")
		{
			cout<<"DECODE: Operation is sraiw, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
		if(funct3=="011")
		{
			cout<<"DECODE: Operation is sd, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
		
	}
	if(opcode=="0100011")
	{
		if(funct3=="011")
		{
			cout<<"DECODE: Operation is sd, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
	}
	if(opcode=="1100111")
	{
		if(funct3=="000")
		{
			cout<<"DECODE: Operation is jalr, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
		
	}
	if(opcode=="0010111")
	{
			cout<<"DECODE: Operation is auipc, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
	}
	if(opcode=="0110111")
	{
			cout<<"DECODE: Operation is lui, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
	}
	if(opcode=="0100011")
	{
		if(funct3=="000")
		{
			cout<<"DECODE: Operation is sb, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
		if(funct3=="001")
		{
			cout<<"DECODE: Operation is sh, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
		if(funct3=="010")
		{
			cout<<"DECODE: Operation is sw, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
		}
	}
	if(opcode=="1100011")
	{
		if(funct3=="000")
		{
			cout<<"DECODE: Operation is beq, first operand R"<<iRA<<" Second operand R"<<iRB<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<RA<<"   R"<<iRB<<"="<<RB<<endl;
		}
		if(funct3=="001")
		{
			cout<<"DECODE: Operation is bne, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		//cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
			cout<<"Read registers R"<<iRA<<"="<<RA<<"   R"<<iRB<<"="<<RB<<endl;
		}
		if(funct3=="100")
		{
			cout<<"DECODE: Operation is blt, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		//cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
			cout<<"Read registers R"<<iRA<<"="<<RA<<"   R"<<iRB<<"="<<RB<<endl;
		}
		if(funct3=="101")
		{
			cout<<"DECODE: Operation is bge, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		//cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
			cout<<"Read registers R"<<iRA<<"="<<RA<<"   R"<<iRB<<"="<<RB<<endl;
		}
		if(funct3=="110")
		{
			cout<<"DECODE: Operation is bltu, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		//cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
			cout<<"Read registers R"<<iRA<<"="<<RA<<"   R"<<iRB<<"="<<RB<<endl;
		}
		if(funct3=="111")
		{
			cout<<"DECODE: Operation is bgeu, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		//cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<iRB<<endl;
			cout<<"Read registers R"<<iRA<<"="<<RA<<"   R"<<iRB<<"="<<RB<<endl;
		}
	}
	if(opcode=="1101111")
	{
		cout<<"DECODE: Operation is jal, first operand R"<<iRA<<" Second operand R"<<iRB<< " destination register R"<<iRd<<endl;
        		cout<<"Read registers R"<<iRA<<"="<<R[iRA]<<"   immediate= "<<jump_imm_offset<<endl;
	}	
}
