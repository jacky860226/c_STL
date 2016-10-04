/****************************************
list.h
é€™è£¡å¯¦ä½œæ²’æœ‰å¾ªç’°çš„link list
ä¹Ÿå°±æ˜¯é ­çš„prevå’Œå°¾çš„nextæœƒæ˜¯NULL 
è¨˜ä½å†è¤‡è£½listæ™‚è£¡é¢çš„void *dataæ˜¯æŒ‡æ¨™ 
å¿…é ˆè¦å†è¢«è¤‡è£½å‡ºä¾†çš„list->dataé€²è¡Œmalloc 
****************************************/ 
#ifndef SM_LIST
#define SM_LIST
#include<malloc.h>
typedef struct _list{
	size_t data_size;
	void *data;
	struct _list *next,*prev;
}list,*Plist;
list *new_list(void *data,size_t data_size){//²£¥Í·sªºlist 
	list *node=(list*)malloc(sizeof(list));
	if(node==0)return 0;
	node->data=malloc(data_size);
	node->prev=node->next=0;
	node->data_size=data_size;
	while(data_size--)
		((char*)node->data)[data_size]=((char*)data)[data_size];
	return node;
}
list *new_copy_list(list *ori){//±qori½Æ»s·sªºlist 
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
list *list_insert_next(list *prev,list *node){//´¡¤J·s¤¸¯À¦bprev->next 
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
list *list_insert_prev(list *next,list *node){//´¡¤J·s¤¸¯À¦bnext->prev 
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
list *list_find_begin(list *node){//§ä¥Xnodeªºbegin 
	if(node)while(node->prev)node=node->prev;
	return node;
}
void list_free(list *node){//§R°£nodeªº°O¾ÐÅé 
	free(node->data);
	free(node);
}
void list_erase(list *node){//§R°£¤¸¯À 
	if(node->prev)
		node->prev->next=node->next;
	if(node->next)
		node->next->prev=node->prev;
	list_free(node);
}
int list_size(list *node){//­pºâ¤¸¯À©Ò¦bªºlist¤j¤p 
	if(node==0)return 0;
	size_t ans=1;
	list *i;
	for(i=node->next;i;i=i->next)++ans;
	for(i=node->prev;i;i=i->prev)++ans;
	return ans;
}
#endif
