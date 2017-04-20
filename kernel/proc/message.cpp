#include <kernel/proc/message.hpp>
#include <kernel/proc/scheduler.hpp>

using namespace Process;

MessageQueue Process::postbox;

bool Process::SendMessage(int port_id, int src_thread, char data) {
	Scheduler::lock();
	//bcprintf("Sending msg... %c\n", data ); // data.getChar()
	postbox.push(port_id, Message(src_thread, data));
	Scheduler::unlock();
	
	return true;
}

void Process::MessageQueue::push(int port_id, Message msg) {
	//ports.push_back(msg);
}

Message* Process::MessageQueue::peek(int port_id) {
	std::vector<Message*> port_postbox = filter(port_id);

	if(port_postbox.size() > 0) { 
		return port_postbox[0];
	}
	else { 
		return nullptr;
	}
}

Message* Process::MessageQueue::pop(int port_id) {
	std::vector<Message*> port_postbox = filter(port_id);

	if(port_postbox.size() > 0) { 
		const int port = 1;
		auto element_it = std::find_if(postbox.ports.begin(), 
									   postbox.ports.end(),
									   PortQueueComp(1) );
		Message return_msg = *port_postbox[0];
		//list.erase(port_postbox[0]);
		return port_postbox[0];
	}
	else { 
		return nullptr;
	}
}

std::vector<Message*> Process::MessageQueue::filter(int port_id) {
	std::vector<Message*> filtered = std::vector<Message*>();

	for(auto x : ports) {
		if(x.port == port_id) {
			bcprintf("Message Recieved (port=%d)\n",port_id);
			//filtered.push_back(&x);
		}
	}

	return filtered;
}

void postbox_debug() {
	Message* msg = NULL;
	for(;;) {
		Scheduler::lock();
		while((msg = Process::postbox.pop(1)) != nullptr) {
			bcprintf("Message Recieved: %c\n",msg->data); // getChar()

			//msg = Process::postbox.pop(1);
		}
		Scheduler::unlock();
	}
}