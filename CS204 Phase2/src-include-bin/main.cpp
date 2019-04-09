#include "myARMSim.h"
#include <cstdio>
#include <cstdlib>
#include<bits/stdc++.h>
#include<string>

using namespace std;

int main(int argc, char** argv) {
  char* prog_mc_file; 
  if(argc < 2) {
    printf("Incorrect number of arguments. Please invoke the simulator \n\t./myRISCVSim <input mc file> \n");
    exit(1);
  }
  
  //reset the processor
  reset_proc();
  //load the program memory
  load_program_memory(argv[1]);
  //run the simulator
  run_RISCVsim();

  return 1;
}
