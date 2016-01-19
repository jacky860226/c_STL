#ifndef SM_UNORDERED_MAP
#define SM_UNORDERED_MAP
#include "hashtable.h"
typedef struct{
	_Hashtable h;
	int first_size,second_size;
}unordered_map;
void unordered_map_init(unordered_map *m,int first_size,int second_size,int (*function)(const void *),int (*cmp)(const void *,const void *)){
	_Hashtable_init(&m->h,first_size+second_size,function,cmp);
	m->first_size=first_size;
	m->second_size=second_size;
}
#define unordered_map_clear(m) _Hashtable_clear(&m->h)
void unordered_map_free(unordered_map *m){
	_Hashtable_free(&m->h);
	m->first_size=0;
	m->second_size=0;
}
void unordered_map_insert(unordered_map *m,const void *key,const void *value){
	void *data=malloc(m->h.data_size);
	memcpy(data,key,m->first_size);
	memcpy(data+m->first_size,value,m->second_size);
	__bucket *bucket=_Hashtable_find_bucket(&m->h,m->h.buckets,m->h.bucket_size,data);
	if(!bucket->data)++m->h.size;
	else free(bucket->data);
	bucket->data=malloc(m->h.data_size);
	memcpy(bucket->data,data,m->h.data_size);
	if(m->h.size*2>m->h.bucket_size){
		_Hashtable_resize(&m->h,m->h.bucket_size+1);
	}
	free(data);
}
#define unordered_map_erase(m,key) _Hashtable_erase(&m->h,key)
void *unordered_map_find(unordered_map *m,const void *key){
	__bucket *tmp=_Hashtable_find_base(&m->h,key);
	if(!tmp)return 0;
	return tmp->data+m->first_size;
}
#endif
