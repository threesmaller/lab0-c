/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q) {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q) {
        return;
    }

    while (q->size) {
        q_remove_head(q, NULL, 0);
    }

    free(q);
    q = NULL;

    return;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (!q) {
        return false;
    }

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    int len = strlen(s) + 1;
    newh->value = malloc(sizeof(char) * len);
    if (!newh->value) {
        free(newh);
        return false;
    }

    strcpy(newh->value, s);

    newh->next = NULL;

    if (q->size == 0) {
        q->head = newh;
        q->tail = newh;
    } else {
        newh->next = q->head;
        q->head = newh;
    }

    q->size++;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q) {
        return false;
    }

    list_ele_t *newt;  // newt means new tail
    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }

    int len = strlen(s) + 1;
    newt->value = malloc(sizeof(char) * len);
    if (!newt->value) {
        free(newt);
        return false;
    }

    strcpy(newt->value, s);

    newt->next = NULL;

    if (q->size == 0) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }

    q->size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || q->size == 0) {
        return false;
    }

    list_ele_t *oldh = q->head;

    if (sp) {
        strncpy(sp, oldh->value, bufsize - 1);
        *(sp + bufsize - 1) = '\0';
    }
    free(oldh->value);
    oldh->value = NULL;

    if (q->size == 1) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = oldh->next;
    }

    free(oldh);
    oldh = NULL;

    q->size--;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return (q == NULL) ? 0 : q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || q->size == 0) {
        return;
    }

    /* You need to write the code for this function */
    list_ele_t *tmp = q->head->next;
    q->tail = q->head;
    while (tmp) {
        q->tail->next = tmp->next;
        tmp->next = q->head;
        q->head = tmp;
        tmp = q->tail->next;
    }

    return;
}
