#include <std/ringbuffer.hpp>

int buffer_read(buffer_t * buffer) {
	if (buffer->head == buffer->tail) {
		return -1; // Buffer is empty
	}

	uint8_t data = buffer->buffer[buffer->tail];

	size_t next = buffer->tail + 1;
	if (next >= buffer->size) {
		next = 0;
	}

	buffer->tail = next;
	return (int)data;
}

int buffer_write(buffer_t * buffer, uint8_t v) {
	size_t next = buffer->head + 1;
	if (next >= buffer->size) {
		next = 0;
	}

	if (next == buffer->tail) {
		return -1; // Buffer is full
	}

	buffer->buffer[buffer->head] = v;
	buffer->head = next;
	return 0;
}

int buffer_clear(buffer_t* buffer) {
	for(int idx = 0; idx < buffer->size; idx++) {
		buffer->buffer[idx] = 0;
	}
	return 0;
}