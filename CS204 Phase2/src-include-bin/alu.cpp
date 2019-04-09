
#include<iostream>
#include<cmath>
#include<bitset>
#include"alu.hpp"
using namespace std;

extern int RZ;
int ZERO=0;
extern int RA;
extern int RB;
extern int PCSRC;


int binstr9_to_dec(string x)
{
	int sum=0;
	for(int i=3;i>=0;i--)
	{
		int c=x[i];
		sum=sum+(c-48)*pow(2,3-i);
	}
	return sum;
}

int ALU (string alu_cntrl_sgnl)
{
	//cout<<alu_cntrl_sgnl<<endl;
   
    int x=binstr9_to_dec(alu_cntrl_sgnl);
//cout<<"x:"<<x<<endl; 
    int pow_2 = pow(2,31)-1;
    int ZERO=0;
    switch(x)
    {
        case (7):                    //multiplication
        { 
            RZ = RA*RB;
            if(-1*(pow_2)<= RZ &&  RZ <= pow_2-1)
               { cout<<"Multiply"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
                return RZ;}
            else
                cout<<"Overflow!"<<endl;
        }
        break;
        case (9):                  // AND
        {
            RZ = RA&RB;
            cout<<"AND"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
            return RZ;
        }
        break;
        case (8):                 // OR
        {
            RZ = RA|RB;
            cout<<"OR"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
            return RZ;
        }
        break;
        case (12):               //XOR
        {
            RZ = RA^RB;
            cout<<"XOR"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
            return RZ; 
        }
        break;
        case (0):              //ADD
        {
            RZ=RA+RB;
            if((RA>0 && RB>0 && RZ>=pow_2)||(RA<0&& RB<0 && RZ<(-1*(pow_2)))) 
                cout<<"overflow"<<endl;
            else
               { cout<<"Addition"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
                return RZ;    } 
        }
        break;
        case (1):
        {
		//cout<<"dinchak"<<endl;
            RZ=RA-RB;                 //Subtract
            if((RA*RB)<0&&(RZ*RB>0))
                cout<<"overflow"<<endl;
            else
            {    cout<<"Subtract"<<"  RA:"<<RA<<" RB: "<<RB<<endl;}
        }
        break;
        case (2):
        {
            cout<<"BEQ"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
            if((RA-RB)==0)
            {
            	PCSRC=1;
                ZERO=1;
            }    
            else
                ZERO=0;
            return ZERO; 
        }
        break;  
        case (3):
        {
            cout<<"BNE"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
            if(RA!=RB)
            {
            PCSRC=1;
            ZERO=1;
            }
            else
            ZERO=0;
            return ZERO;
        }
        break;
        case (4):
        {
	    cout<<"BLT"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
            if(RA<RB)
            {
            PCSRC=1;
            ZERO=1;
            }
            else 
            ZERO=0;
            return ZERO;
        }
        break;
        case(5):
        {
	    cout<<"BGE"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
            if(RA>=RB)
            {
	    PCSRC=1;
            ZERO= 1;
            }
            else
            ZERO= 0;
            return ZERO;
        }
        break;
        case (6):
        {

            if((RB==0)||(RA==0x80000000 && RB ==0xffffffff ))
            cout<<"Overflow!"<<endl;
            else
           { RZ=RA/RB;
		cout<<"Divide"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
            return RZ;}
        }
        break;  
        case (13):
        {
            RZ=RA*pow(2,RB);
            if(RZ>pow_2||RZ<(-1*pow_2))
                cout<<"Overflow!"<<endl;
            else
           {cout<<"Shift Logical Left"<<"  RA:"<<RA<<" RB: "<<RB<<endl;; return RZ;}    
        }
        break;
        case (11):
        {
 		cout<<"Shift Logical Right"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
		if(RA>=0)             	
		RZ=RA>>RB;//change this code and also check logical left slri slli
		else
		{
			bitset<32> i(RA);
			
		}
	//	cout<<"i:"<<i<<endl;
           
        }
        break;
        case (10):
        {
		 RZ=RA>>RB;
		cout<<"Shift Arithmetic Right"<<"  RA:"<<RA<<" RB: "<<RB<<endl;;return RZ;
           /* if(RA>=0)
             { cout<<"hello"<<endl;
		  RZ=RA>>RB;
                cout<<"RZ:"<<RZ;return RZ;}
            else
            {
                bitset<32> I(RA);
		cout<<"I:"<<I<<endl;
                for(int i=0;i<=31-RB;i++)
                {
                     I[i]=I[RB+i];
                }
		cout<<"I:"<<I<<endl;
                for(int i=31;i>31-RB;i--)
                {
		    cout<<"i:"<<i<<endl;
		    cout<<"ding"<<endl;
                    I[i]=1;
                }
		cout<<"I:"<<I<<endl;
            int x;
            x=I.to_ulong();
            x=pow(2,31)-x;
            x=x*(-1);
            RZ=x; 
            cout<<"RZ:"<<RZ;
            return RZ;          
            }
cout<<"i am bACK"<<endl;*/
        }
        break;
        case(15):
        {
            RZ=RA%RB;
            cout<<"Remainder"<<"  RA:"<<RA<<" RB: "<<RB<<endl;
            return RZ;
        }
        break;
    }    

}
