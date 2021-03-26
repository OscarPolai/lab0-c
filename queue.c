#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q;
    q = malloc(sizeof(queue_t));

    /* TODO: What if malloc returned NULL? */

    if (!q)
        return NULL;
    q->head = q->tail = NULL;

    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */

    if (!q)
        return;

    list_ele_t *e = q->head;
    while (e) {
        list_ele_t *next = e->next;
        free(e->value);
        free(e);
        e = next;
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
    /* Return false if q is NULL */
    if (!q)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* Return false if malloc returns NULL for allocate new head*/
    if (!newh)
        return false;
    /* Return false if allocate memory for strings returns NULL*/
    size_t length = strlen(s) + 1;
    newh->value = malloc(sizeof(char) * length);
    if (!newh->value) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, length);
    /* if queue is empty , operation is needed for tail */
    if (q->size == 0)
        q->tail = newh;
    newh->next = q->head;
    q->head = newh;
    (q->size)++;

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
    /* Return false if q is NULL */
    if (!q)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* Return false if malloc returns NULL for allocate new head*/
    if (!newh)
        return false;
    /* Return false if allocate memory for strings returns NULL*/
    size_t length = strlen(s) + 1;
    newh->value = malloc(sizeof(char) * length);
    if (!newh->value) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, length);

    if (!(q->tail)) {
        q->head = q->tail = newh;
        (q->head)->next = NULL;
    } else {
        (q->tail)->next = newh;
        newh->next = NULL;
        q->tail = newh;
    }
    (q->size)++;

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
    if (!q || (q->size == 0))
        return false;
    list_ele_t *rmh = q->head;

    memcpy(sp, rmh->value, bufsize);
    if (q->size == 1)
        q->tail = NULL;
    q->head = rmh->next;
    free(rmh->value);
    free(rmh);

    (q->size)--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size == 0)
        return 0;
    return q->size;
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
    if (!q || q->size <= 1)
        return;

    list_ele_t *pre, *cur, *nex;
    pre = NULL;
    cur = q->head;
    nex = q->head->next;

    q->tail = q->head;

    while (cur->next) {
        cur->next = pre;

        pre = cur;
        cur = nex;
        nex = nex->next;
    }
    cur->next = pre;

    pre = cur;
    // cur = nex;

    q->head = pre;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q || (q->size) == 0)
        // printf("the address of q = %p\n",q);
        return;

    q->head = mergesort(q->head, q->size);
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

list_ele_t *mergesort(list_ele_t *a, size_t size)
{
    if (size > 1) {
        size_t lsize = size / 2;
        size_t rsize = size - lsize;

        list_ele_t *rh = Divide(a, lsize);
        a = mergesort(a, lsize);
        rh = mergesort(rh, rsize);
        a = combine(a, rh);
    }
    return a;
}

list_ele_t *Divide(list_ele_t *cut, size_t step)
{
    for (int i = 1; i < step; i++) {
        cut = cut->next;
    }
    list_ele_t *rh = cut->next;
    cut->next = NULL;
    return rh;
}

list_ele_t *combine(list_ele_t *lh, list_ele_t *rh)
{
    list_ele_t Dummy;
    list_ele_t *tail = &Dummy;
    Dummy.next = NULL;
    while (lh && rh) {
        if (strcmp((lh->value), (rh->value)) > 0) {
            // printf("value=%d\n", strcmp(lh->value, rh->value));
            tail->next = rh;
            rh = rh->next;


        } else {
            // printf("value=%d\n", strcmp(lh->value, rh->value));
            tail->next = lh;
            lh = lh->next;
        }
        tail = tail->next;
    }
    if (!lh) {
        tail->next = rh;
    } else {
        tail->next = lh;
    }
    return (Dummy.next);
}
