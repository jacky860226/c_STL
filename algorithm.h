#ifndef SM_ALGORITHM
#define SM_ALGORITHM
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<stdbool.h>
//stl_algobase.h:
void iter_swap(void *a,void *b,size_t data_size){
	while(data_size--){
		char tmp=((char*)a)[data_size];
		((char*)a)[data_size]=((char*)b)[data_size];
		((char*)b)[data_size]=tmp;
	}
}
#define swap(a,b) {\
	void*tmp=malloc(sizeof(a));\
	memcpy(tmp,&(a),sizeof(a));\
	a=b;\
	memcpy(&(b),tmp,sizeof(a));\
}
//stl_heap.h:
void *is_heap_until(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	size_t n=(last-first)/data_size,parent=0,child;
	for(child=1;child<n;++child){
		if(cmp(first+parent*data_size,first+child*data_size)<0)return first+child*data_size;
		if((child&1)==0)++parent;
	}
	return first+n*data_size;
}
bool is_heap(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	return is_heap_until(first,last,data_size,cmp)==last;
}
void __push_heap(void *first,size_t hole,size_t top,const void *value,size_t data_size,int (*cmp)(const void *,const void *)){
	int parent=((int)hole-1)/2;
	while(hole>top&&cmp(first+parent*data_size,value)<0){
		memcpy(first+hole*data_size,first+parent*data_size,data_size);
		hole=parent;
		parent=((int)hole-1)/2;
	}
	memcpy(first+hole*data_size,value,data_size);
}
void push_heap(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	void *value=malloc(data_size);
	memcpy(value,last-data_size,data_size);
	__push_heap(first,(last-first)/data_size-1,0,value,data_size,cmp);
	free(value);
}
void __adjust_heap(void *first,size_t hole,size_t len,void *value,size_t data_size,int (*cmp)(const void *,const void *)){
	const size_t top=hole;
	int secondChild=hole;
	while(secondChild<((int)len-1)/2){
		secondChild=2*(secondChild+1);
		if(cmp(first+secondChild*data_size,first+(secondChild-1)*data_size)<0)--secondChild;
		memcpy(first+hole*data_size,first+secondChild*data_size,data_size);
		hole=secondChild;
	}
	if((len&1)==0&&secondChild==((int)len-2)/2){
		secondChild=2*(secondChild+1);
		memcpy(first+hole*data_size,first+(secondChild-1)*data_size,data_size);
		hole=secondChild-1;
	}
	__push_heap(first,hole,top,value,data_size,cmp);
}
void __pop_heap(void *first,void *last,void *result,size_t data_size,int (*cmp)(const void *,const void *)){
	void *value=malloc(data_size);
	memcpy(value,result,data_size);
	memcpy(result,first,data_size);
	__adjust_heap(first,0,(last-first)/data_size,value,data_size,cmp);
	free(value);
}
void pop_heap(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	__pop_heap(first,last-data_size,last-data_size,data_size,cmp);
}
void make_heap(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	int len=(last-first)/data_size;
	if(len<2)return;
	int parent=(len-2)/2;
	void *value=malloc(data_size);
	for(;;){
		memcpy(value,first+parent*data_size,data_size);
		__adjust_heap(first,parent,len,value,data_size,cmp);
		if(parent==0)return;
		parent--;
	}
	free(value);
}
void sort_heap(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	while(last-first>=(int)data_size){
		last-=data_size;
		__pop_heap(first,last,last,data_size,cmp);
	}
}
//stl_algo.h:
void *lower_bound(void *first,void *last,size_t data_size,const void *value,int (*cmp)(const void *,const void *)){
	size_t len=(last-first)/data_size;
	while(len>0){
		size_t half=len>>1;
		void *middle=first+half*data_size;
		if(cmp(middle,value)<0){
			first=middle+data_size;
			len=len-half-1;
		}else len=half;
	}
	return first;
}
void *upper_bound(void *first,void *last,size_t data_size,const void *value,int (*cmp)(const void *,const void *)){
	size_t len=(last-first)/data_size;
	while(len>0){
		size_t half=len>>1;
		void *middle=first+half*data_size;
		if(cmp(value,middle)<0)len=half;
		else{
			first=middle+data_size;
			len=len-half-1;
		}
	}
	return first;
}
void *unique(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	if(first==last)return last;
	void *dest=first;
	first+=data_size;
	while((first+=data_size)!=last)
		if(!cmp(dest,first)){
			int i;
			dest+=data_size;
			memcpy(dest,first,data_size);
		}
	return dest+data_size;
}
void reverse(void *first,void *last,size_t data_size){
	if(first==last)return;
	last-=data_size;
	while(first<last){
		iter_swap(first,last,data_size);
		first+=data_size;
		last-=data_size;
	}
}
void rotate(void *first,void *middle,void *last,size_t data_size){
	if(first==middle||last==middle)return;
	void *first2=middle;
	do{
		iter_swap(first,first2,data_size);
		first+=data_size;
		first2+=data_size;
		if(first==middle)middle=first2;
	}while(first2!=last);
	first2=middle;
	while(first2!= last){
		iter_swap(first,first2,data_size);
		first+=data_size;
		first2+=data_size;
		if(first==middle)middle=first2;
		else if(first2==last)first2=middle;
	}
}
void *copy(void *first,void *last,void *result,size_t data_size){
	while(first<last){
		memcpy(result,first,data_size);
		first+=data_size;
		result+=data_size;
	}
	return result;
}
void *copy_backward(void *first,void *last,void *result,size_t data_size){
	while(first!=last)
		memcpy(result-=data_size,last-=data_size,data_size);
	return result;
}
void __unguarded_linear_insert(void *last,void *val,size_t data_size,int (*cmp)(const void *,const void *)){
	void *next=last;
	next-=data_size;
	while(cmp(val,next)<0){
		memcpy(last,next,data_size);
		last=next;
		next-=data_size;
	}
	memcpy(last,val,data_size);
}
void __insertion_sort(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	if(first==last)return;
	void *i,*val=malloc(data_size);
	for(i=first+data_size;i!=last;i+=data_size){
		memcpy(val,i,data_size);
		if(cmp(i,first)<0){
			copy_backward(first,i,i+data_size,data_size);
			memcpy(first,val,data_size);
		}else __unguarded_linear_insert(i,val,data_size,cmp);
	}
	free(val);
}
void *merge(void *first1,void *last1,void *first2,void *last2,void *result,size_t data_size,int (*cmp)(const void *,const void *)){
	while(first1!=last1&&first2!=last2){
		if(cmp(first2,first1)<0){
			memcpy(result,first2,data_size);
			first2+=data_size;
		}else{
			memcpy(result,first1,data_size);
			first1+=data_size;
		}
		result+=data_size;
	}
	return copy(first2,last2,copy(first1, last1,result,data_size),data_size);
}
void __merge_without_buffer(void *first,void *middle,void *last,size_t data_size,size_t len1,size_t len2,int (*cmp)(const void *,const void *)){
	if(len1==0||len2==0)return;
	if(len1+len2==2){
		if(cmp(middle,first)<0)iter_swap(first,middle,data_size);
		return;
	}
	void *first_cut=first,*second_cut=middle;
	size_t len11=0,len22=0;
	if(len1>len2){
		len11=len1/2;
		first_cut+=len11*data_size;
		second_cut=lower_bound(middle,last,data_size,first_cut,cmp);
		len22=(second_cut-middle)/data_size;
	}else{
		len22=len2/2;
		second_cut+=len22*data_size;
		first_cut=upper_bound(first,middle,data_size,second_cut,cmp);
		len11=(first_cut-first)/data_size;
	}
	rotate(first_cut,middle,second_cut,data_size);
	void *new_middle=first_cut;
	new_middle+=second_cut-middle;
	__merge_without_buffer(first,first_cut,new_middle,data_size,len11,len22,cmp);
	__merge_without_buffer(new_middle,second_cut,last,data_size,len1-len11,len2-len22,cmp);
}
void __inplace_stable_sort(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	if(last-first<(int)data_size*15){
		__insertion_sort(first,last,data_size,cmp);
		return;
	}
	void *middle=first+((last-first)/data_size/2)*data_size;
	__inplace_stable_sort(first,middle,data_size,cmp);
	__inplace_stable_sort(middle,last,data_size,cmp);
	__merge_without_buffer(first,middle,last,data_size,(middle-first)/data_size,(last-middle)/data_size,cmp);
}
void __stable_sort(void *first,void *last,void *buffer,size_t data_size,int (*cmp)(const void *,const void *)){
	if(last-first<(int)data_size*15){
		__insertion_sort(first,last,data_size,cmp);
		return;
	}
	size_t len=(last-first)/data_size/2;
	void *middle=first+len*data_size;
	__stable_sort(first,middle,buffer,data_size,cmp);
	__stable_sort(middle,last,buffer+len*data_size,data_size,cmp);
	merge(first,middle,middle,last,buffer,data_size,cmp);
	memcpy(first,buffer,last-first);
}
void stable_sort(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	void *buffer=malloc(last-first);
	if(buffer){
		__stable_sort(first,last,buffer,data_size,cmp);
		free(buffer);
	}else __inplace_stable_sort(first,last,data_size,cmp);
}
void *min_element(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	if(first==last)return first;
	void *result=first;
	while((first+=data_size)!=last)
		if(cmp(first,last)<0)
			result=first;
	return result;
}
void *max_element(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	if(first==last)return first;
	void *result=first;
	while((first+=data_size)!=last)
		if(cmp(result,first)<0)
			result=first;
	return result;
}
bool next_permutation(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	if(first==last)return false;
	void *i=first;
	i+=data_size;
	if(i==last)return false;
	i=last;
	i-=data_size;
	for(;;){
		void *ii=i;
		i-=data_size;
		if(cmp(i,ii)<0){
			void *j=last;
			while(cmp(i,j-=data_size)>=0);
			iter_swap(i,j,data_size);
			reverse(ii,last,data_size);
			return true;
		}
		if(i==first){
			reverse(first,last,data_size);
			return false;
		}
	}
}
bool prev_permutation(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	if(first==last)return false;
	void *i=first;
	i+=data_size;
	if(i==last)return false;
	i=last;
	i-=data_size;
	for(;;){
		void *ii=i;
		i-=data_size;
		if(cmp(ii,i)<0){
			void *j=last;
			while(cmp(j-=data_size,i)>=0);
			iter_swap(i,j,data_size);
			reverse(ii,last,data_size);
			return true;
		}
		if(i==first){
			reverse(first,last,data_size);
			return false;
		}
	}
}
void random_shuffle(void *first,void *last,size_t data_size,size_t (*__rand)(const size_t)){
	if(first==last)return;
	void *i;
	for(i=first+data_size;i!=last;i+=data_size)
		iter_swap(i,first+__rand((i-first)/data_size+1)*data_size,data_size);
}
void __heap_select(void *first,void *middle,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	make_heap(first,middle,data_size,cmp);
	void *i;
	for(i=middle;i<last;i+=data_size)
		if(cmp(i,first)<0)__pop_heap(first,middle,i,data_size,cmp);
}
void partial_sort(void *first,void *middle,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	__heap_select(first,middle,last,data_size,cmp);
	sort_heap(first,middle,data_size,cmp);
}
void __move_median_first(void *a,void *b,void *c,size_t data_size,int (*cmp)(const void *,const void *)){
	if(cmp(a,b)<0){
		if(cmp(b,c)<0)iter_swap(a,b,data_size);
		else if(cmp(a,c)<0)iter_swap(a,c,data_size);
	}else if(cmp(a,c)<0)return;
	else if(cmp(b,c)<0)iter_swap(a,c,data_size);
	else iter_swap(a,b,data_size);
}
void *__unguarded_partition(void *first,void *last,void *pivot,size_t data_size,int (*cmp)(const void *,const void *)){
	while(true){
		while(cmp(first,pivot)<0)first+=data_size;
		last-=data_size;
		while(cmp(pivot,last)<0)last-=data_size;
		if(!(first<last))return first;
		iter_swap(first,last,data_size);
		first+=data_size;
	}
}
void *__unguarded_partition_pivot(void *first,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	void *mid=first+((last-first)/data_size/2)*data_size;
	__move_median_first(first,mid,last-data_size,data_size,cmp);
	return __unguarded_partition(first+data_size,last,first,data_size,cmp);
}
void __introselect(void *first,void *nth,void *last,size_t data_size,size_t depth_limit,int (*cmp)(const void *,const void *)){
	while(last-first>3*(int)data_size){
		if(depth_limit==0){
			__heap_select(first,nth+data_size,last,data_size,cmp);
			iter_swap(first,nth,data_size);
			return;
		}
		--depth_limit;
		void *cut=__unguarded_partition_pivot(first,last,data_size,cmp);
		if(cut<=nth)first=cut;
		else last=cut;
	}
	__insertion_sort(first,last,data_size,cmp);
}
int __lg(int n){
	int k;
	for(k=0;n!=0;n>>=1)++k;
	return k-1;
}
void nth_element(void *first,void *nth,void *last,size_t data_size,int (*cmp)(const void *,const void *)){
	if(first==last||nth==last)return;
	__introselect(first,nth,last,data_size,__lg((last-first)/data_size)*2,cmp);
}
#endif
