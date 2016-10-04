#ifndef SM_QUEUE 
#define SM_QUEUE

//for queue
#include "deque.h"
typedef deque queue;
#define queue_init(q,data_size) deque_init(q,data_size)
#define queue_free(q) deque_free(q)
#define queue_clear(q) deque_clear(q)
#define queue_push(q,data) deque_push_back(q,data)
#define queue_pop(q) deque_pop_front(q)
#define queue_kth_element(q,k) deque_kth_element(q,k)

//for priority_queue
#include "vector.h"
#include "algorithm.h"
typedef struct{
	vector v;
	int (*cmp)(const void *,const void *);
	size_t size;
}priority_queue;
void priority_queue_init(priority_queue *pq,size_t data_size,int (*_cmp)(const void *,const void *)){
	vector_init(&pq->v,data_size);
	pq->size=0;
	pq->cmp=_cmp;
}
void priority_queue_free(priority_queue *pq){
	vector_free(&pq->v);
	pq->cmp=0;
	pq->size=0;
}
void priority_queue_clear(priority_queue *pq){
	vector_clear(&pq->v);
	pq->size=0;
}
void priority_queue_push(priority_queue *pq,const void *data){
	++pq->size;
	vector_push_back(&pq->v,data);
	push_heap(pq->v.elements,pq->v.elements+pq->v.size*pq->v.data_size,pq->v.data_size,pq->cmp);
}
void priority_queue_pop(priority_queue *pq){
	--pq->size;
	pop_heap(pq->v.elements,pq->v.elements+pq->v.size*pq->v.data_size,pq->v.data_size,pq->cmp);
	vector_pop_back(&pq->v);
}
const void *priority_queue_top(const priority_queue *pq){
	return pq->v.elements;
}
#endif
