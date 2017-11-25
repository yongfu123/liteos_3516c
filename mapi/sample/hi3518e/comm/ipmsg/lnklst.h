#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define INLINE __inline
#else
#define INLINE inline
#endif

typedef enum {NOD_BEFORE = 0, NOD_AFTER = 1} NOD_POSITION;

void add_node_to(void** head, void* node, void* to, NOD_POSITION before_or_after);
void move_node(void** head, void* moved, void* to, NOD_POSITION before_or_after);
void add_node(void** head, void* node);
void del_node(void** head, void* node);
typedef int (*CMP_FUNC)(void* t1, void* t2);
void sort_list(void** head, CMP_FUNC nodcmp);
void add_node_sorted(void** head, void* node, CMP_FUNC nodcmp);
int get_node_count(void** head);
void* next_node(void* current);
void* get_node_byID(void* head, int ID);


#define DECLEAR_LIST(a, type)     type a[1];


#ifdef __cplusplus
};
#endif
