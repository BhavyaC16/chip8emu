#include "../include/Machine.hpp"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>

void loadFile(const std::string& filename, std::vector<uint8_t>& prog){
	// From https://stackoverflow.com/questions/5420317/reading-and-writing-binary-file
	std::ifstream input(filename, std::ios::binary);
	for(char c: std::vector<char>(std::istreambuf_iterator<char>(input), {})){
		prog.push_back(c);
	}
}

int main(int argc, char ** argv){
	Machine machine;

	{ // Create block to deallocate the possibly large variable prog
		// Load Instructions
		std::vector<uint8_t> prog;
		loadFile(argv[1], prog);
		machine.setInst(prog, 0x200);

		prog.clear();

		// Load Sprites
		loadFile("res/sprites.bin", prog);
		machine.setInst(prog, 0x000);
		
		// Set Machine cycle-rate
		if(argc==3){
			machine.setCycleRate((uint16_t)strtol(argv[2],NULL,10));
		}
	}
	
	// Begin instruction fetch-execute-increment cycle
	machine.runLoop();
	
	return 0;
}
