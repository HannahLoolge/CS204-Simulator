all: sample

sample: main.o alu.o execute.o main_control.o myRISCSim.o fetch.o decode.o mem.o write_back.o
	g++ main.o alu.o execute.o main_control.o myRISCSim.o fetch.o decode.o mem.o write_back.o -o sample

main.o: main.cpp
	g++ -c main.cpp

alu.o: alu.cpp
	g++ -c alu.cpp

execute.o: execute.cpp
	g++ -c execute.cpp

main_control.o: main_control.cpp
	g++ -c main_control.cpp
	
myRISCSim.o: myRISCSim.cpp
	g++ -c myRISCSim.cpp
	
fetch.o: fetch.cpp
	g++ -c fetch.cpp

decode.o: decode.cpp
	g++ -c decode.cpp
	
mem.o: mem.cpp
	g++ -c mem.cpp
	
write_back.o: write_back.cpp
	g++ -c write_back.cpp

clean:
	rm*.o sample	
