#include "circular_buffer.h"
#include <string.h>

void cb_init(CircularBuffer_t *cb, int num_max_of_elt, size_t size_of_elt) {
	cb->size        = 0;
    cb->_start      = 0;
    cb->_end        = 0;
	cb->_size_max   = num_max_of_elt +1;
	cb->_sizeof_elt = size_of_elt;
    cb->_elt        = malloc((cb->_size_max)*size_of_elt );
}
 
void cb_dead(CircularBuffer_t *cb) {
    free(cb->_elt); 
}
 
int cb_is_full(CircularBuffer_t *cb) {
	return cb->size+1 >= cb->_size_max; //return (cb->_end + 1) % (cb->_size_max) == cb->_start;
}
 
int cb_is_empty(CircularBuffer_t *cb) {
	return cb->size == 0; //return cb->_end == cb->_start;
}
 
void cb_push(CircularBuffer_t *cb, void *elem) {
	memcpy((char*)cb->_elt + cb->_end*cb->_sizeof_elt,elem,cb->_sizeof_elt);
    cb->_end = (cb->_end + 1) % (cb->_size_max);
	cb->size++;
    if (cb->_end == cb->_start) {
        cb->_start = (cb->_start + 1) % (cb->_size_max); // full and overwrite 
		cb->size = cb->_size_max-1;
	}
}
 
void cb_pop(CircularBuffer_t *cb,void *elem) {
	memcpy((char*)elem,(char*)cb->_elt + cb->_start*cb->_sizeof_elt,cb->_sizeof_elt);
    cb->_start = (cb->_start + 1) % (cb->_size_max);
	cb->size--;
}

void * cb_read(const CircularBuffer_t *cb,int index) {
	return (char*)cb->_elt + ((index+cb->_start) % (cb->_size_max))*cb->_sizeof_elt;
}