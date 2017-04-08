#include <stddef.h>

#include <std.hpp>
#include <std/vector.hpp>

#include <kernel/user/env.hpp>

std::vector<pair> ENV::environment = std::vector<pair>();

string ENV::get(char* envVar) {
	for(auto it = environment.begin(); it != environment.end(); it++) {
		if(strcmp((*it).key, envVar) == 0) 
			return (*it).value;
	}
	
	return "";
}

void ENV::set(string envVar, string envVal) {

	for(auto it = environment.begin(); it != environment.end(); it++) {
		if(strcmp((*it).key, envVar) == 0) {
			(*it).value = envVal;
			return;
		}
	}

	bcprintf("Set ENV::%s = %s\n", envVar, envVal);

	// if we get here, then the key wasn't found inside the vector, so let's add it!
	environment.push_back(pair(envVar, envVal));
}

void ENV::initialise() {
	// ENV::set("cd", "/");
	// ENV::set("user", "james");
	// ENV::set("comp-name", "localhost");
	//ENV::set()

	// terminal_printf("%x\n", &environment);
}