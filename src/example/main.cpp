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
