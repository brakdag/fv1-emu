#pragma once

struct Memory {
	double * start_ptr;
	unsigned int size;
	unsigned int head_index;
	unsigned int tail_index;
};

struct MemoryAddress {
	Memory* mem = 0;
	signed int displacement = 0;
};

class MemoryManager {
public:
	static Memory* createMemory(unsigned int size);
	static double getValueAtEnd(MemoryAddress* mem);
	static double getValueAtStart(MemoryAddress* mem);
	//static double getValueAtMiddle(MemoryAddress* mem);
	static void setValueAtStart(Memory* mem, double value);
	static void updateMemoryPointersIncrementingByOne(Memory* mem);

};