#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *que = malloc(sizeof(queue_t));
    que->head = NULL;
    que->size = 0;
    que->tail = NULL;
    return que;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL || q->head == NULL) return;
    for (element_t *e = q->head; e; e = e->next) {
        free(e->value);
        free(e);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */

bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) return false;
    element_t *new_element = malloc(sizeof(element_t));
    if (new_element == NULL) return false;
    new_element->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (new_element->value == NULL) return false;
    strcpy(new_element->value, s);
    new_element->next = q->head;
    q->head = new_element;
    q->size++;
    if (new_element->next == NULL) q->tail = new_element;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL) return false;
    element_t *new_element = malloc(sizeof(element_t));
    if (new_element == NULL) return false;
    new_element->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (new_element->value == NULL) return false;
    new_element->next = NULL;
    strcpy(new_element->value, s);
    if (q->head == NULL) {
        q->head = new_element;
        q->tail = new_element;
        q->size++;
        return true;
    }
    q->tail->next = new_element;
    q->tail = new_element;
    q->size++;
    
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL) return false;
    if (q->size == 0) return false;
    element_t* del = q->head;
    q->head = del->next;
    strncpy(sp, del->value, sizeof(char) * (bufsize-1));
    if (strlen(del->value) >= bufsize) sp[bufsize-1] = '\0';
    free(del->value);
    free(del);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
size_t q_size(queue_t *q)
{
    if (q != NULL) return q->size;
    return -1;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL) return;
    if (q->size <= 1) return;
    element_t* nxt = q->head, *prev = NULL;
    q->head = q->tail;
    q->tail = nxt;

    //e1 -> e2 -> e3 -> null
    // ^           ^
    // |           |
    //tail        head

    prev = q->tail;
    for (element_t *e = q->tail; e; e = nxt) {
        nxt = e->next;
        e->next = (prev != e ? prev : NULL); //first element
        prev = e;
    }
}

void queue_split(element_t* src, element_t** l, element_t** r) {
    element_t* left;
    element_t* right;
    right = src;
    left = src->next;

    while (left != NULL) {
        left = left->next;
        if (left != NULL) {
            right = right->next;
            left = left->next;
        }
    }

    *l = src;
    *r = right->next;
    right->next = NULL;
}

element_t* sorted_merge(element_t* l, element_t* r) {
    element_t* res = NULL;

    if (l == NULL) return r;
    else if (r == NULL) return l;

    if (strcmp(l->value, r->value) <= 0) {
        res = l;
        res->next = sorted_merge(l->next, r);
    }
    else {
        res = r;
        res->next = sorted_merge(l, r->next);
    }
    return res;
}

/*
 * The function's sorting algorithm should be merge sort.
 */
void merge_sort(element_t** head) {
    if (!(*head) || !(*head)->next) return;
    element_t *head_tmp = *head;
    element_t *a, *b;

    if ((head == NULL) || (head_tmp->next == NULL)) return;

    queue_split(head_tmp, &a, &b);

    merge_sort(&a), merge_sort(&b);

    *head = sorted_merge(a, b);
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q || !q->head)
        return;

    merge_sort(&q->head);
    element_t *walk = q->head;
    while (walk->next)
        walk = walk->next;

    q->tail = walk;
}
