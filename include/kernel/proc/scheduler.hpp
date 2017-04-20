#pragma once

#include <kernel/multiboot.hpp>
#include <kernel/gdt.hpp>
#include <kernel/idt.hpp>

namespace Scheduler {
	extern unsigned int task_idx;
	extern unsigned int lock_count;
	extern registers base_state;
	extern bool has_initialised;
	extern volatile bool running;
	
	void next(registers* r);
	bool lock();
	bool unlock();
	void yield();
	
	void init();
};