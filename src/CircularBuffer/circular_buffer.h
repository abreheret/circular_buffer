#ifndef _circular_buffer_h_
#define _circular_buffer_h_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
==============================================================
   
	Author  : Amaury BREHERET
	Date    : 10/04/2014

	MIT License Copyright (c) 2014 Amaury BREHERET

Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation 
files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM
, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
==============================================================
   Example for use circular buffer : 
==============================================================

#include "circular_buffer.h"
#include <stdio.h>

typedef struct {
	int value;
	float fvalue;
}ElemType; 

int main(int agrv,char **argv) {
    CircularBuffer_t cb;
    int size_max = 8; 
    cb_init(&cb, size_max,sizeof(ElemType));
 
    // Fill buffer with elements
    for (int i = 0 ; i < 25 ; i ++) {
		ElemType elem;
		elem.value = i;
		elem.fvalue = i*3.14159265359;
		printf("push element {%02d %4.2f} size before push : [%d] \n", elem.value,elem.fvalue,cb.size);
        cb_push(&cb, &elem);												  
	}																		  

	// Read elements 
	for(int i = 0 ; i < cb.size ; i++) {									  
		ElemType * e = (ElemType *)cb_read(&cb,i);						  
		printf("read element {%02d %4.2f} size : [%d] \n", e->value,e->fvalue,cb.size);
	}																		  

    // Pop, Remove and print all elements 									  
    while (!cb_is_empty(&cb)) {												  
		ElemType elem;														  
		cb_pop(&cb,&elem);													  
		printf("pop element  {%02d %4.2f} size after pop : [%d] \n" , elem.value,elem.fvalue,cb.size);
    }
	
    cb_dead(&cb);
    return 0;
}

==============================================================
*/

/* Circular buffer object */
typedef struct {

	int      size       ;///< number of elements
						 
	/// private data for circualr buffer
	int      _size_max  ;///< maximum number of elements           
	int      _start     ;///< index of oldest element              
	int      _end       ;///< index at which to write new element  
	size_t   _sizeof_elt;///< sizeof element in octet
	void    *_elt       ;///< vector of elements                   
} CircularBuffer_t;

void cb_init(CircularBuffer_t *cb, int num_max_of_elt, size_t size_of_elt) ;
void cb_dead(CircularBuffer_t *cb) ;
int  cb_is_full(CircularBuffer_t *cb) ;
int  cb_is_empty(CircularBuffer_t *cb) ;
void cb_push(CircularBuffer_t *cb,const void *elem) ;
void cb_pop(CircularBuffer_t *cb,void *elem ) ;
void * cb_read(const CircularBuffer_t *cb,int index);

#ifdef __cplusplus
}
#endif

#endif //_circular_buffer_h_