#ifndef SM_UNORDERED_SET
#define SM_UNORDERED_SET
#include "hashtable.h"
typedef _Hashtable unordered_set;
#define unordered_set_init(s,data_size,function,cmp) _Hashtable_init(s,data_size,function,cmp)
#define unordered_set_clear(s) _Hashtable_clear(s)
#define unordered_set_free(s) _Hashtable_free(s)
#define unordered_set_insert(s,value) _Hashtable_insert(s,value)
#define unordered_set_erase(s,value) _Hashtable_erase(s,value)
#define unordered_set_find(s,value) _Hashtable_find(s,value)
#endif
