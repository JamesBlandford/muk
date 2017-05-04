#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.hpp>
#include <kernel/cpu.hpp>
#include <kernel/idt.hpp>
#include <kernel/timer.hpp>

#include <kernel/memory/alloc.hpp>

#include <kernel/proc/scheduler.hpp>
#include <kernel/proc/thread.hpp>
#include <kernel/proc/process.hpp>

unsigned int Scheduler::lock_count(0); 
volatile bool Scheduler::running(true);

static bool started = false;

// this function currently isn't used. I need to work out how
// to call interrupts from within the IRQ0 (timer) interrupt.
static void scheduler_isr130(registers * r) {
	Scheduler::next(r);
}

// this is the heart of our time slicing algorithm. It's extremely
// basic at the moment, with only a single process allowed and no
// ability to skip or change the time slice itself.
void Scheduler::next(registers * r) {

	// save the previous threads state
	if(started)
		memcpy(&(thread_running->state_reg), r, sizeof(registers));

	// Lets move on with task switching!
	thread_running = thread_running->next;

	bcprintf("\n/////////////////\n");

	bcprintf("thread: %s (%d)\n", thread_running->title, thread_running->thread_id);
	bcprintf("esp=%x, eip=%x\n", thread_running->state_reg.esp, thread_running->state_reg.eip);

	bcprintf("---------\n");

	bcprintf("prev->esp=%x, prev->eip=%x\n",thread_running->prev->state_reg.esp,
											thread_running->prev->state_reg.eip);

	// set the registers from the current thread's saved state
	// memcpy(r, &(thread_running->state_reg), sizeof(registers));	

	bcprintf("\\\\\\\\\\\\\\\\\\\\\\\n");

	started = true;

	MAGIC_BREAK;

	// change registers
	asm volatile (
		"mov %0, %%eax\n"
		"mov %1, %%ebx\n"
		"mov %2, %%ecx\n"
		"mov %3, %%edx\n"
		: : "r" (thread_running->state_reg.eax),
			"r" (thread_running->state_reg.ebx),
			"r" (thread_running->state_reg.ecx),
			"r" (thread_running->state_reg.edx)
		: "memory"); // clobber regs

	// change ESP
	asm volatile (
		"mov %0, %%ebx\n"
		"mov %1, %%esp\n"
		"mov %2, %%ebp\n"
		"mov %3, %%esi\n"
		"mov %4, %%edi\n"
		"sti\n"
		"jmp *%%ebx"
		: : "r" (thread_running->state_reg.eip),
			"r" (thread_running->state_reg.esp),
			"r" (thread_running->state_reg.ebp),
			"r" (thread_running->state_reg.esi),
			"r" (thread_running->state_reg.edi)
		: "%ebx", "memory"); // clobber regs
}



// this is used to allow threads to perform blocking I/O calculations.
// it stops schedule_next from switching context to another thread until
// resume() is called. 
// Note: this can HANG THE KERNEL if used improperly!!!!!
bool Scheduler::lock() {
	if(running) {
		running = false;
		return true;
	}
	return false; // already locked, we cannot lock AGAIN!
}

bool Scheduler::unlock() {
	if(!running) {
		running = true;
		return true;
	}
	return false; // already unlocked, we cannot unlock AGAIN!
}

void Scheduler::yield() {
	Scheduler::unlock();
	Timer::yield();
}

int Scheduler::threadId() {
	return thread_running->thread_id;
}

void Scheduler::init() {
	set_isr_handler(0x82, scheduler_isr130); // currently not used
}