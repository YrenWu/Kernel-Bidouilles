#ifndef INTERRUPTS_H
#define INTERRUPTS_H

struct stateCPU
{
	/* general registers */
	size_t eax;
	size_t ebx;
	size_t ecx;
	size_t edx;

	/* source and destination indexes */
	size_t esi;
	size_t edi;
	/* base pointers */
	size_t ebp;
	//size_t esp;

	/* segment registers */
	size_t cs;
	size_t ds;
	size_t ss;
	size_t es;
	size_t fs;
	size_t gs;

} __attribute__((packed));
typedef struct stateCPU cpuSize_t;

struct stateStack
{
	size_t errorCode;
    size_t eip;
    size_t cs;
    size_t eflags;
	
}__attribute__((packed));
typedef struct stateStack stackSize_t;

// void interruptHandler(struct cpuSize_t cpu, struct stackSize_t stack, size_t interrupt);

#endif