#ifndef SM_DEQUE
#define SM_DEQUE
#include<malloc.h>
#include<string.h>
#define BASE_SIZE 3
typedef struct{
	int data_size,element_size,size;
	void *elements,*begin,*end;
}deque;
void deque_init(deque *dq,int data_size){
	dq->element_size=BASE_SIZE;
	dq->data_size=data_size;
	dq->size=0;
	dq->elements=malloc(data_size*dq->element_size);
	dq->begin=dq->end=dq->elements+data_size;
}
void deque_free(deque *dq){
	dq->element_size=dq->data_size=dq->size=0;
	free(dq->elements);
	dq->elements=dq->begin=dq->end=0;
}
void deque_resume(deque *dq,int size){
	dq->element_size=size;
	void *tmp=malloc(size*dq->data_size),*tmp_front=dq->begin;
	dq->begin=tmp+size/3*dq->data_size;
	dq->end=tmp+size/3*dq->data_size*2;
	memcpy(dq->begin,tmp_front,dq->size*dq->data_size);
	free(dq->elements);
	dq->elements=tmp;
}
void deque_clear(deque *dq){
	dq->size=0;
	deque_resume(dq,BASE_SIZE);
}
void deque_push_back(deque *dq,const void *data){
	if(dq->elements+dq->element_size*dq->data_size==dq->end)
		deque_resume(dq,dq->size*3);
	memcpy(dq->end,data,dq->data_size);
	++dq->size;
	dq->end+=dq->data_size;
}
void deque_pop_back(deque *dq){
	--dq->size;
	dq->end-=dq->data_size;
	if(dq->element_size>=dq->size*5&&dq->element_size>BASE_SIZE)
		deque_resume(dq,dq->size*3);
}
void deque_push_front(deque *dq,const void *data){
	if(dq->begin==dq->elements)
		deque_resume(dq,dq->size*3);
	memcpy(dq->begin-=dq->data_size,data,dq->data_size);
	++dq->size;
}
void deque_pop_front(deque *dq){
	--dq->size;
	dq->begin+=dq->data_size;
	if(dq->element_size>=dq->size*5&&dq->element_size>BASE_SIZE)
		deque_resume(dq,dq->size*3);
}
void *deque_kth_element(deque *dq,int k){
	if(k>=dq->size)return 0;
	return dq->begin+k*dq->data_size;
}
#undef BASE_SIZE
#endif
