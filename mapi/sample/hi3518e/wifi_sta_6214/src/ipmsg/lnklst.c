
#ifdef CFG_SUPPORT_WIFI_STA
#include <stdlib.h>
#include "lnklst.h"

#define ONE_WAY_LINKED_LIST
//#define TWO_WAY_LINKED_LIST

typedef struct basic_nod_t
{
#ifdef TWO_WAY_LINKED_LIST
    struct basic_nod_t* prev;
#endif
    struct basic_nod_t* next;
} BASICNOD, *PBASICNOD;

static __inline PBASICNOD prev_node(PBASICNOD head, PBASICNOD nod)
{
#ifdef ONE_WAY_LINKED_LIST
    PBASICNOD n = head;

    if ((nod == NULL) || ( nod == head))
    { return NULL; }

    while (n)
    {
        if (n->next == nod)
        { return n; }

        n = n->next;
    }

    return NULL;
#endif
#ifdef TWO_WAY_LINKED_LIST
    return nod->prev;
#endif
}

void* next_node(void* current)
{
    return (void*)((PBASICNOD)current)->next;
}

void* last_node(void* head)
{
    PBASICNOD p = (PBASICNOD)head;

    while (p && p->next)
    {
        p = p->next;
    }

    return p;
}

void add_node_to(void** head, void* node, void* to, NOD_POSITION before_or_after)
{
    PBASICNOD* h = (PBASICNOD*)head;
    PBASICNOD n = (PBASICNOD)node;
    PBASICNOD tt = (PBASICNOD)to;

    if (node == NULL)
    { return; }

    if (*h == NULL)
    {
        // the link list is empty
        *h = n;
#ifdef TWO_WAY_LINKED_LIST
        n->prev = NULL;
#endif
        n->next = NULL;
    }
    else if (before_or_after == NOD_BEFORE)
    {
        // move the 'moved' node to the place before 'to'
        // if 'to' is NULL, then move the 'moved' node to the head
#ifdef ONE_WAY_LINKED_LIST
        PBASICNOD prev_nod;
#endif

        if (tt == NULL)
        { tt = *h; }

        if (*h == tt)
        { *h = n; }

#ifdef TWO_WAY_LINKED_LIST
        n->prev = tt->prev;
#endif
        n->next = tt;
#ifdef TWO_WAY_LINKED_LIST
        tt->prev = n;

        if (n->prev != NULL)
        {
            n->prev->next = n;
        }

#endif
#ifdef ONE_WAY_LINKED_LIST
        prev_nod = prev_node(*h, tt);

        if (prev_nod)
        {
            prev_nod->next = n;
        }

#endif
    }
    else if (before_or_after == NOD_AFTER)
    {
        //move the 'moved' node to the place after 'to'
        if (tt == NULL)
        { tt = last_node(*h); }

        n->next = tt->next;
#ifdef TWO_WAY_LINKED_LIST
        n->prev = tt;
#endif
        tt->next = n;
#ifdef TWO_WAY_LINKED_LIST

        if (n->next != NULL)
        { n->next->prev = n; }

#endif
    }
}

void add_node(void** head, void* node)
{
    add_node_to(head, node, NULL, NOD_AFTER);
}

void del_node(void** head, void* node)
{
    PBASICNOD* h = (struct basic_nod_t**)head;
    PBASICNOD n = (struct basic_nod_t*)node;
#ifdef ONE_WAY_LINKED_LIST
    PBASICNOD tmp;
#endif

    if (h == NULL)
    { return; }

    if (*h == NULL)
    { return; }

    if (n == *h)
    {
        *h = n->next;
    }

#ifdef TWO_WAY_LINKED_LIST

    if (n->prev)
    { n->prev->next = n->next; }

    if (n->next)
    { n->next->prev = n->prev; }

#endif
#ifdef ONE_WAY_LINKED_LIST
    tmp = prev_node(*h, n);

    if (tmp)
    { tmp->next = n->next; }

#endif
}

void move_node(void** head, void* moved, void* to, NOD_POSITION before_or_after)
{
    PBASICNOD* h = (PBASICNOD*)head;
    PBASICNOD m = (PBASICNOD)moved;
    PBASICNOD tt = (PBASICNOD)to;

    if (	(h == NULL) || (*h == NULL) || (m == tt))
    { return; }

    del_node(head, moved);
    add_node_to(head, moved, to, before_or_after);
}

void sort_list(void** head, CMP_FUNC nodcmp)
{
    PBASICNOD* h = (PBASICNOD*)head;
    PBASICNOD nod1 = *h;
    PBASICNOD nod2 = nod1->next;
    int swaped = 1;

    if (nod2 == NULL)
    { return; }

    while (swaped)
    {
        swaped = 0;

        while (1)
        {
            if ((*nodcmp)(nod1, nod2) > 0)
            {
                move_node(head, nod1, nod2, NOD_AFTER);
                nod2 = nod1->next;
                swaped = 1;
            }
            else
            {
                nod1 = nod2;
                nod2 = nod2->next;
            }

            if (nod2 == NULL)
            {
                nod1 = *h;
                nod2 = nod1->next;
                break;
            }
        }
    }
}

void add_node_sorted(void** head, void* node, CMP_FUNC nodcmp)
{
    int added = 0;
    PBASICNOD* h = (PBASICNOD*)head;
    PBASICNOD n = (PBASICNOD)node;
    PBASICNOD tmp = *h;

    if (*h == NULL)
    {
        add_node_to(head, node, NULL, NOD_AFTER);
        return;
    }

    if ((*nodcmp)(n, *h) < 0)
    {
        add_node_to(head, node, *h, NOD_BEFORE);
        return;
    }

    //	if((*nodcmp)(n, last_node(*head,*h)) >= 0)
    //	{
    //		add_node(head, node);
    //		return;
    //	}
    while (tmp)
    {
        if ((*nodcmp)(n, tmp) < 0)
        {
            add_node_to(head, node, tmp, NOD_BEFORE);
            added = 1;
            break;
        }
        else
        { tmp = tmp->next; }
    }

    if (added == 0)
    { add_node_to(head, node, NULL, NOD_AFTER); }
}

int get_node_count(void** head)
{
    PBASICNOD* h = (PBASICNOD*)head;
    PBASICNOD tmp = *h;
    int count = 0;

    if (h == NULL)
    { return 0; }

    if (*h == NULL)
    { return 0; }

    while (tmp)
    {
        tmp = tmp->next;
        count++;
    }

    return count;
}

void* get_node_byID(void* head, int ID)
{
    PBASICNOD h = (PBASICNOD)head;
    PBASICNOD tmp;
    int count = 0;

    if (ID == 0)
    { return head; }

    for (tmp = h; tmp && (count < ID); tmp = tmp->next, count++);

    return tmp;
}
#endif
