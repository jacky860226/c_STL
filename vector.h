#ifndef SM_VECTOR
#define SM_VECTOR
#include<malloc.h>
#include<string.h>
#define BASE_SIZE 2
typedef struct{
	int data_size,element_size,size;
	void *elements;
}vector;
void vector_init(vector *v,int data_size){
	v->element_size=BASE_SIZE;
	v->data_size=data_size;
	v->size=0;
	v->elements=malloc(data_size*v->element_size);
}
void vector_free(vector *v){
	v->element_size=v->data_size=v->size=0;
	free(v->elements);
	v->elements=0;
}
void vector_resume(vector *v,int size){
	v->element_size=size;
	v->elements=realloc(v->elements,size*v->data_size);
}
void vector_clear(vector *v){
	v->size=0;
	vector_resume(v,BASE_SIZE);
}
void vector_push_back(vector *v,const void *data){
	if(v->element_size==v->size)
		vector_resume(v,v->size*2);
	char *tmp=(char*)v->elements;
	int i,base=v->size++*v->data_size;
	for(i=0;i<v->data_size;++i)
		tmp[base+i]=((char*)data)[i];
}
void vector_pop_back(vector *v){
	--v->size;
	if(v->element_size>=v->size*4&&v->element_size>BASE_SIZE)
		vector_resume(v,v->size*2);
}
void *vector_kth_element(vector *v,int k){
	if(k>=v->size)return 0;
	return v->elements+k*v->data_size;
}
#undef BASE_SIZE
#endif
