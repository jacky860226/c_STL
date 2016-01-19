#ifndef SM_HASHTABLE
#define SM_HASHTABLE
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include "algorithm.h"
#define __c_stl_num_prime 32
static unsigned long __c_stl_prime_list[__c_stl_num_prime]={
	2,5,11,23,
	53,97,193,389,769,
	1543,3079,6151,12289,24593,
	49157,98317,196613,393241,786433,
	1572869,3145739,6291469,12582917,25165843,
	50331653,100663319,201326611,402653189,805306457,
	1610612741,3221225473ul,4294967291ul
};
static int unsigned_long_cmp(const void *a,const void *b){
	unsigned long A=*(unsigned long*)a,B=*(unsigned long*)b;
	if(A!=B)return A<B?-1:1;
	return 0;
}
static unsigned long __c_stl_next_prime(unsigned long n){
	unsigned long *first=__c_stl_prime_list,*last=__c_stl_prime_list+__c_stl_num_prime;
	const unsigned long *pos=lower_bound(first,last,sizeof(unsigned long),&n,unsigned_long_cmp);
	return pos==last?*(last-1):*pos;
}
#define BASE_SIZE __c_stl_prime_list[2]
typedef struct{
	void *data;
}__bucket;
typedef struct{
	int data_size,bucket_size,size;
	__bucket *buckets;
	int (*hash_function)(const void *);
	int (*_cmp)(const void *,const void *);
}_Hashtable;
void _Hashtable_init(_Hashtable *h,int data_size,int (*function)(const void *),int (*cmp)(const void *,const void *)){
	h->data_size=data_size;
	h->bucket_size=BASE_SIZE;
	h->size=0;
	h->buckets=calloc(BASE_SIZE,sizeof(__bucket));
	h->hash_function=function;
	h->_cmp=cmp;
}
void _Hashtable_clear(_Hashtable *h){
	h->bucket_size=BASE_SIZE;
	h->size=0;
	__bucket *tmp=h->buckets;
	int i;
	for(i=0;i<h->bucket_size;++i){
		if(tmp[i].data)free(tmp[i].data);
	}
	h->buckets=calloc(BASE_SIZE,sizeof(__bucket));
	free(tmp);
}
void _Hashtable_free(_Hashtable *h){
	h->data_size=0;
	h->bucket_size=0;
	h->size=0;
	int i;
	for(i=0;i<h->bucket_size;++i){
		if(h->buckets[i].data)free(h->buckets[i].data);
	}
	free(h->buckets);
	h->buckets=0;
	h->hash_function=0;
	h->_cmp=0;
}
__bucket *_Hashtable_find_bucket(_Hashtable *h,__bucket *buckets,int bucket_size,const void *value){
	int i=h->hash_function(value)%bucket_size,j=0;
	if(i<0)i+=bucket_size;
	while(buckets[i].data&&h->_cmp(buckets[i].data,value)){
		i+=((++j)<<1)-1;
		if(i>=bucket_size)
			i-=bucket_size;
	}
	return buckets+i;
}
bool _Hashtable_insert_base(_Hashtable *h,__bucket *buckets,int bucket_size,const void *value){
	__bucket *bucket=_Hashtable_find_bucket(h,buckets,bucket_size,value);
	if(bucket->data)return 0;
	bucket->data=malloc(h->data_size);
	memcpy(bucket->data,value,h->data_size);
	return 1;
}
void _Hashtable_resize(_Hashtable *h,unsigned long new_size){
	new_size=__c_stl_next_prime(new_size);
	__bucket *tmp=calloc(new_size,sizeof(__bucket));
	static int i;
	for(i=0;i<h->bucket_size;++i){
		if(h->buckets[i].data){
			_Hashtable_insert_base(h,tmp,new_size,h->buckets[i].data);
			free(h->buckets[i].data);
		}
	}
	free(h->buckets);
	h->buckets=tmp;
	h->bucket_size=new_size;
}
void _Hashtable_insert(_Hashtable *h,const void *value){
	if(_Hashtable_insert_base(h,h->buckets,h->bucket_size,value))
		++h->size;
	if(h->size*2>h->bucket_size){
		_Hashtable_resize(h,h->bucket_size+1);
	}
}
void _Hashtable_erase(_Hashtable *h,const void *value){
	__bucket *bucket=_Hashtable_find_bucket(h,h->buckets,h->bucket_size,value);
	if(!bucket->data)return;
	free(bucket->data);
	bucket->data=0;
	--h->size;
}
__bucket *_Hashtable_find_base(_Hashtable *h,const void *value){
	__bucket *bucket=_Hashtable_find_bucket(h,h->buckets,h->bucket_size,value);
	if(!bucket->data)return 0;
	return bucket;
}
bool _Hashtable_find(_Hashtable *h,const void *value){
	if(_Hashtable_find_base(h,value))return 1;
	return 0;
}
#undef BASE_SIZE
#undef __c_stl_num_prime
#endif
