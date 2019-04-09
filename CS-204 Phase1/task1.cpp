#include<bits/stdc++.h>
#include<iterator>
#include<map>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<regex>
#include<cmath>
#include<cstdio>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int cnt=-1;
ofstream outfile("mac_code.mc",ios::out);

int str_dec(string str)
{
	int num=0;
	int two_pow = pow(2,12);
	if(str[0]=='-')
	{
		string r = str.substr(1,str.length());
		stringstream ss(r);
		ss>>num;
		return two_pow-num;
	}
	else
	{
		stringstream ss(str);
		ss>>num;
		return num;
	}
}
int binstr_to_dec(string x)
{
	int sum=0;
	for(int i=3;i>=0;i--)
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

void U_format(string inst, int Unum[])
{
	string opcode;
	bitset<5> rd(Unum[0]);
	bitset<20> imm(Unum[1]);
	string s_rd = rd.to_string();
	string s_imm = imm.to_string();
    	
    	
	opcode = inst.substr(1, 7);
    
    	string mac_bin = s_imm + s_rd + opcode;	
    	bitset <32> b( mac_bin );
  	outfile<<"0x"<<hex<<4*cnt <<"  "<<"0x"<< hex << b.to_ulong() << endl;
}

void I_format(string code,int Rnum[3])
{
	string opcode=code.substr(1,7);
	string funct3;
	int i,j;

	for(int f=8;f<11;f++)
	{
		funct3+=code[f];
	}

	if(opcode=="0010011"||opcode=="0011011")
	{
		j=2;
		i=1;	
	}
	else if(opcode=="0000011"||opcode=="1100111")
	{
		j=1;
		i=2;
	}
	else if(opcode=="0100011")
	{
		string imm_str;
		
		bitset<5> rs2(Rnum[0]), rs1(Rnum[2]);
		string s_rs2 = rs2.to_string();
    	string s_rs1 = rs1.to_string();
    	string mac_bin="";
    	bitset<12> imm(Rnum[1]);
    	string s_imm = imm.to_string();
    	for(int f=0;f<5;f++)
		{
			imm_str+=s_imm[f];
		}
    	mac_bin = s_imm.substr(5,11) + s_rs2  + s_rs1 + funct3 +imm_str + opcode;
    	string mac_code=bin_to_hex(mac_bin); 
    	outfile<<"0x"<<hex<<4*cnt<<"  "<<"0x"<<mac_code<<endl;

		return;
	}

	bitset<5> rd(Rnum[0]), rs1(Rnum[i]);
	string s_rd = rd.to_string();
    string s_rs1 = rs1.to_string();
    string mac_bin="";

    if(code[11]=='\0')
    {
    	bitset<12> imm(Rnum[j]);
    	string s_imm = imm.to_string();
    	 mac_bin = s_imm  + s_rs1 + funct3 + s_rd + opcode;   //immediate takes the 12 bit value
    }

    else
    {
    	bitset<5> imm(Rnum[j]);
    	string s_imm = imm.to_string();
    	string funct7 = code.substr(11,17);
    	mac_bin = funct7 + s_imm + s_rs1  + funct3 + s_rd + opcode;  //immediate takes the 5 bit value
		funct7="";
    }

    string mac_code=bin_to_hex(mac_bin);
    outfile<<"0x"<<hex<<4*cnt<<"  "<<"0x"<<mac_code<<endl;
    funct3="";	
}



void S_format(string code,int array_num[])
{
	string opcode, funct3;
	
	bitset<5> rs2(array_num[0]),  rs1(array_num[2]);
	bitset<12> imm(array_num[1]);
	bitset<5> imm1;
	bitset<7> imm2;
	
	for(int i=0; i<5; i++)
	{
		imm1[i] = imm[i];
	}
	
	for(int i=5; i<12; i++)
	{
		imm2[i-5] = imm[i];
	}
	string s_rs2, s_rs1, s_imm1, s_imm2 ;
	opcode = code.substr(1,7);
	funct3 = code.substr(8,3);
	s_rs2 = rs2.to_string();
	s_rs1 = rs1.to_string();
	s_imm1 = imm1.to_string();
	s_imm2 = imm2.to_string();
	string machine_code = s_imm2 + s_rs2 + s_rs1 + funct3 + s_imm1 + opcode;
	string bin_machine_code  = bin_to_hex(machine_code);

	outfile<<"0x"<<hex<<4*cnt<<"  "<<"0x"<<bin_machine_code<<endl;
}


void SB_format(string code,int *array_num, string instruction, std::map<string, string> &temp_map)
{
	string opcode, funct3;
	string str,str1,label,check_mnen;
	int i=0,j=0,finStore;
	//cout<<"instruction"<<instruction<<endl;
	while(instruction[i]!='\0')
	{
		int flag2=0;
		int flag1=0;
		if(instruction[i]!=' ')
		str = str+instruction[i];
		str1=str;
		j++;
		while(instruction[i]==' ' || instruction[i] == ',')
		{
			flag1=1;
			str="\0";
			j=0;
			i++;
		}
		if(instruction[i]=='#')
		{
			flag2=1;
			//cout<<"str1:"<<str1<<endl;
			break;
		}
		if(flag1!=1)i++;
	}
	str1 = str1+":";
	int labelNo2=0 ;
    map<string, string>::iterator it;
    int flag=0;
    ifstream label_fle("assembly.asm");
    while(getline(label_fle,label))
    {
        stringstream ss(label);
        ss>>check_mnen;
        //cout<<check_mnen<<endl;
        if(check_mnen==str1)
        {
            flag=1;
            break;

        }
        else
        {
            it=temp_map.find(check_mnen);
            if(it!=temp_map.end())
            {
                labelNo2++;
            }
        }

    }
    //cout<<"label:1"<<cnt<<endl;
    //cout<<"labelNo2"<<labelNo2<<endl;
    if(flag==0)
    {
        cout<<"Label not found!"<<endl;
        return; 
    }
    finStore=labelNo2-cnt;
    finStore*=4;
	cout<<finStore<<endl;
	bitset<5> rs2(array_num[1]),rs1(array_num[0]);
	bitset<13> imm(finStore);
	bitset<5> imm1;
	bitset<7> imm2;
	
	imm1[0] = imm[11];
	
	for(int i=1; i<=4; i++)
	{
		imm1[i]=imm[i];
	}
	for(int i=5; i<=10; i++)
	{
		imm2[i-5]=imm[i];
		
	}
	imm2[6]=imm[12];
	
	string s_rs2, s_rs1, s_imm1, s_imm2 ;
	opcode = code.substr(2,7);
	funct3 = code.substr(9,3);
	s_rs2 = rs2.to_string();
	s_rs1 = rs1.to_string();
	s_imm1 = imm1.to_string();
	s_imm2 = imm2.to_string();

	string machine_code = s_imm2 + s_rs2 + s_rs1 + funct3 + s_imm1 + opcode;
	string bin_machine_code  = bin_to_hex(machine_code);

	outfile<<"0x"<<hex<<4*cnt<<"  "<<"0x"<<bin_machine_code<<endl;
	
}

void R_format(string inst, int Rnum[3])
{
	string opcode, funct3, funct7;
	
	bitset<5> rd(Rnum[0]), rs1(Rnum[1]), rs2(Rnum[2]);
	
	string s_rd = rd.to_string();
    string s_rs1 = rs1.to_string();
    string s_rs2 = rs2.to_string();	
	opcode = inst.substr(1, 7);
    for(int i=8; i<11; i++)
    {
    	funct3+=inst[i];
    }
    funct7 = inst.substr(11, 17);
    string mac_bin = funct7 + s_rs2 + s_rs1 + funct3 + s_rd + opcode;
    bitset <32> b( mac_bin );
  	outfile<<"0x"<<hex<<4*cnt <<"  0x"<< hex << b.to_ulong() << endl;
}

void UJ_format(string code,int Rnum[3], string instruction, std::map<string, string> &temp_map, int labelNo1)
{
	string opcode=code.substr(2,8);
	bitset<5> rd(Rnum[0]);
    string str,str1,label,check_mnen;
	int i=0,j=0,finStore;
	while(instruction[i]!='\0')
	{
		int flag2=0;
		int flag1=0;
		if(instruction[i]!=' ')
		str = str+instruction[i];
		str1=str;
		j++;
		while(instruction[i]==' ' || instruction[i] == ',')
		{
			flag1=1;
			str="\0";
			j=0;
			i++;
		}
		if(instruction[i]=='#')
		{
			flag2=1;
			//cout<<"str1:"<<str1<<endl;
			break;
		}
		if(flag1!=1)i++;
	}
	str1 = str1+":";
	int labelNo2=0 ;
    map<string, string>::iterator it;
    int flag=0;
    ifstream label_fle("assembly.asm");
    while(getline(label_fle,label))
    {
        stringstream ss(label);
        ss>>check_mnen;
        //cout<<"check_mnen"<<check_mnen<<endl;
        if(check_mnen==str1)
        {
            flag=1;
            break;

        }
        else
        {
            it=temp_map.find(check_mnen);
            if(it!=temp_map.end())
            {
                labelNo2++;
                //cout<<"labelNo2: "<<labelNo2<<" check_mnen:"<<check_mnen<<endl;
            }
        }
    }
    if(flag==0)
    {
        cout<<"Label not found!"<<endl;
        return; 
    }
    //cout<<"cnt"<<cnt<<endl;
    //cout<<"labelNo2"<<labelNo2<<endl;
    //cout<<"menen"<<check_mnen<<endl;
    finStore=labelNo2-cnt;
    finStore*=4;
	bitset<21> offset(finStore);
	//cout<<"finstore"<<finStore<<endl;
	//cout<<"offset"<<offset<<endl;
	string mac_bin="";
	
	string s_rd= rd.to_string();
	
	string f_offset=offset.to_string();
	//cout<<"f_offset"<<f_offset<<endl;
	
	string str_1=f_offset.substr(10,10);

	str_1=str_1;

	string str2=f_offset.substr(1,8);
	//cout<<mac_bin<<endl;
	mac_bin=f_offset[0]+str_1+f_offset[11]+str2+s_rd+opcode;
    string mac_code=bin_to_hex(mac_bin); 
    outfile<<"0x"<<hex<<4*cnt<<"  0x"<<mac_code<<endl;
	return;
}



int main()
{
	ifstream file, myfile;
	
	string instruction, mnem, num_str, line,prev_line;
	map<string, string> inst_map;   
    map<string, string>::iterator it ;
    int array_num[3]={0};
    int i=0;
	file.open("assembly.asm");
	myfile.open("inst.txt");
	regex rx(R"(-?[0-9]+)"); // Declare the regex with a raw string literal
    smatch m;

	while(getline(myfile,line))
	{
		stringstream ss(line);
		string mnemonics,code_val;
		ss>>mnemonics>>code_val;
		inst_map.insert(pair<string, string>(mnemonics,code_val)); 
	}
	
	int count=0;
	int l=0;
    while(getline(file,instruction))
	{
   //      while (instruction.length()==0 ) 
   //        { if(!file)
		 //  break;
		 //  //cout<<"l++"<<l++<<endl;
			// getline(file, instruction);} 
		i=0;
		stringstream ss(instruction);
		ss>>mnem;
		it = inst_map.find(mnem);
	
		
		while(ss>>num_str&&num_str[0]!='\0'&&num_str[0]!='#')
		{
			num_str = regex_replace(num_str, regex("sp"), "x2");
			if(mnem=="swi"&&num_str=="0x11")
			{
				cnt++;
				outfile<<"0x"<<hex<<4*cnt<<"  0x"<<"ef000011"<<endl;
				break;
			}
			string str = num_str;
			

			while (regex_search(str, m, rx)) 
			{
      			array_num[i]=str_dec(m[0]);
        		str = m.suffix().str(); // Proceed to the next match
        		i++;
    		} 
		}
		
		if(it != inst_map.end() ) 
    	{
    		
    		count++;
            cnt++;
           // cout<<"cnt"<<cnt;
    		string code;
    		code=it->second;
    		if(code[0]=='R')
    			R_format(code,array_num);
    		else if(code[0]=='I')
    			I_format(code,array_num);
    		else if(code[0]=='S' && code[1]=='B')
    		{	
    			//string labelVar = it->first;
    			SB_format(code,array_num, instruction, inst_map);
    		}
    		else if(code[0]=='S')
    			S_format(code,array_num);
			else if(code[0]=='U' && code[1]=='J')
    			UJ_format(code,array_num,instruction,inst_map,count);
    		else if(code[0]=='U')
    			U_format(code,array_num);
    		
    	}
	}    
}
