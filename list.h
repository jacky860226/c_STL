/****************************************
list.h
這裡實作沒有循環的link list
也就是頭的prev和尾的next會是NULL 
記住再複製list時裡面的void *data是指標 
必須要再被複製出來的list->data進行malloc 
****************************************/ 
#ifndef SM_LIST
#define SM_LIST
#include<malloc.h>
typedef struct _list{
	size_t data_size;
	void *data;
	struct _list *next,*prev;
}list,*Plist;
list *new_list(void *data,size_t data_size){//產生新的list 
	list *node=(list*)malloc(sizeof(list));
	if(node==0)return 0;
	node->data=malloc(data_size);
	node->prev=node->next=0;
	node->data_size=data_size;
	while(data_size--)
		((char*)node->data)[data_size]=((char*)data)[data_size];
	return node;
}
list *new_copy_list(list *ori){//從ori複製新的list 
	if(ori==0)return 0;
	list *node=(list*)malloc(sizeof(list));
	if(node==0)return 0;
	node->data=malloc(ori->data_size);
	node->prev=ori->prev;
	node->next=ori->next;
	node->data_size=ori->data_size;
	size_t i=ori->data_size;
	while(i--)
		((char*)node->data)[i]=((char*)ori->data)[i];
	return node;
}
list *list_insert_next(list *prev,list *node){//插入新元素在prev->next 
	if(node==0)return 0;
	if(prev){
		node->next=prev->next;
		prev->next=node;
		node->prev=prev;
		if(node->next)
			node->next->prev=node;
	}
	return node;
}
list *list_insert_prev(list *next,list *node){//插入新元素在next->prev 
	if(node==0)return 0;
	if(next){
		node->prev=next->prev;
		next->prev=node;
		node->next=next;
		if(node->prev)
			node->prev->next=node;
	}
	return node;
}
list *list_find_begin(list *node){//找出node的begin 
	if(node)while(node->prev)node=node->prev;
	return node;
}
void list_free(list *node){//刪除node的記憶體 
	free(node->data);
	free(node);
}
void list_erase(list *node){//刪除元素 
	if(node->prev)
		node->prev->next=node->next;
	if(node->next)
		node->next->prev=node->prev;
	list_free(node);
}
int list_size(list *node){//計算元素所在的list大小 
	if(node==0)return 0;
	size_t ans=1;
	list *i;
	for(i=node->next;i;i=i->next)++ans;
	for(i=node->prev;i;i=i->prev)++ans;
	return ans;
}
#endif
