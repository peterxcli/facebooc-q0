/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdbool.h>
#include <stddef.h>

/**
 * element_t - Linked list element
 * @value: pointer to array holding string
 * @next: pointer to next node of singly-linked list
 *
 * @value needs to be explicitly allocated and freed
 */
typedef struct element {
    /* Pointer to array holding string.
     * This array needs to be explicitly allocated and freed
     */
    char *value;
    struct element *next;
} element_t;

typedef struct {
    element_t *head; /* Linked list of elements */
    element_t *tail;
    size_t size;
} queue_t;

/* Operations on queue */

/*
 * q_new() - Create an empty queue.
 *
 * Return: NULL for allocation failed.
 */
queue_t *q_new();

/*
 * q_free() - Free ALL storage used by queue, no effect if q is NULL.
 * @q: Queue data structure
 */
void q_free(queue_t *q);

/**
 * q_insert_head() - Insert an element in the head
 * @q: Queue data structure
 * @s: string would be inserted
 *
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 *
 * Return: true for success, false for allocation failed or queue is NULL
 */
bool q_insert_head(queue_t *q, char *s);

/**
 * q_insert_tail() - Insert an element at the tail
 * @q: Queue data structure
 * @s: string would be inserted
 *
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 *
 * Return: true for success, false for allocation failed or queue is NULL
 */
bool q_insert_tail(queue_t *q, char *s);

/**
 * q_remove_head() - Remove the element from head of queue
 * @q: Queue data structure
 * @sp: string would be inserted
 * @bufsize: size of the string
 *
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 *
 * NOTE: "remove" is different from "delete"
 * The space used by the list element and the string should not be freed.
 * The only thing "remove" need to do is unlink it.
 *
 * Reference:
 * https://english.stackexchange.com/questions/52508/difference-between-delete-and-remove
 *
 * Return: the pointer to element, %NULL if queue is NULL or empty.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize);

/**
 * q_size() - Get the size of the queue
 * @q: Queue data structure
 *
 * Return: the number of elements in queue, zero if queue is NULL or empty
 */
size_t q_size(queue_t *q);


/**
 * q_reverse() - Reverse elements in queue
 * @q: Queue data structure
 *
 * No effect if queue is NULL or empty.
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q);

/**
 * q_sort() - Sort elements of queue in ascending order
 * @q: Queue data structure
 *
 * No effect if queue is NULL or empty. If there has only one element, do
 * nothing.
 * This function's sorting algorithm should be merge sort.
 */
void q_sort(queue_t *q);

