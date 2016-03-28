/*
* RingBuffer.c
*
*  Created on: Jun 12, 2015
*      Author: http://c.learncodethehardway.org/book/
*/
#include <stdio.h>
#include <errno.h>
#include "bstrlib-master/bstrlib.h"

typedef struct {
	char *buffer;
	int length;
	int start;
	int end;
} RingBuffer;

RingBuffer *RingBuffer_create(int length);
void RingBuffer_destory(RingBuffer *buffer);
int RingBuffer_read(RingBuffer *buffer, char *target, int amount);
int RingBuffer_write(RingBuffer *buffer, char *data, int length);
int RingBuffer_empty(RingBuffer *buffer);
int RingBuffer_full(RingBuffer *buffer);
int RingBuffer_available_data(RingBuffer *buffer);
int RingBuffer_available_space(RingBuffer *buffer);
char * RingBuffer_get(RingBuffer *buffer, int amount);

#define RingBuffer_available_data(B) (((B)->end + 1) % (B)->length - (B)->start - 1)
#define RingBuffer_available_space(B) ((B)->length - (B)->end - 1)
#define RingBuffer_full(B) (RingBuffer_available_data((B)) - (B)->length == 0)
#define RingBuffer_empty(B) (RingBuffer_available_data((B)) == 0)
#define RingBuffer_puts(B, D) RingBuffer_write((B), bdata((D)), blength((D)))
#define RingBuffer_get_all(B) RingBuffer_gets((B), RingBuffer_available_data((B)))
#define RingBuffer_starts_at(B) ((B)->buffer + (B)->start)
#define RingBuffer_ends_at(B) ((B)->buffer + (B)->end)
#define RingBuffer_commit_read(B, A) ((B)->start = ((B)->start + (A)) % (B)->length)
#define RingBuffer_commit_write(B, A) ((B)->end = ((B)->end + (A)) % (B)->length)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

RingBuffer *RingBuffer_create(int length)
{
	RingBuffer *buffer = calloc(1, sizeof(RingBuffer));
	buffer->length = length + 1;
	buffer->start = 0;
	buffer->end = 0;
	buffer->buffer = calloc(buffer->length, 1);

	return buffer;
}

void RingBuffer_destroy(RingBuffer *buffer)
{
	if(buffer) {
		free(buffer->buffer);
		free(buffer);
	}
}

int RingBuffer_write(RingBuffer *buffer, char *data, int length)
{
	if(RingBuffer_available_data(buffer) == 0) {
		buffer->start = buffer->end = 0;
	}

	check(length <= RingBuffer_available_space(buffer),
			"Not enough space: %d request, %d available",
			RingBuffer_available_data(buffer), length);

	void *result = memcpy(RingBuffer_ends_at(buffer), data, length);
	check(result != NULL, "Failed to write data into buffer.");

	RingBuffer_commit_write(buffer, length);
	return length;
error:
	return -1;
}

int RingBuffer_read(RingBuffer *buffer, char *target, int amount)
{
	check_debug(amount <= RingBuffer_available_data(buffer),
				"Not enough in the buffer: has %d, needs %d",
				RingBuffer_available_data(buffer), amount);

	void *result = memcpy(target, RingBuffer_starts_at(buffer), amount);
	check(result != NULL, "Failed to write buffer into data.");

	RingBuffer_commit_read(buffer, amount);

	if(buffer->end == buffer->start) {
		buffer->start = buffer->end = 0;
	}

	return amount;
error:
	return -1;
}

char * RingBuffer_gets(RingBuffer *buffer, int amount)
{
	check(amount > 0, "Need more than 0 for gets, you gave: %d", amount);
	check_debug(amount <= RingBuffer_available_data(buffer),
				"Not enough in the buffer.");

	bstring result = blk2bstr(RingBuffer_starts_at(buffer), amount);
	check(result != NULL, "Failed to create gets result.");
	check(blength(result) == amount, "Wrong result length.");

	RingBuffer_commit_read(buffer, amount);
	assert(RingBuffer_available_data(buffer) >= 0 && "Error in read commit.");

	return result;
error:
	return NULL;
}

int main()
{

	return 0;
}

