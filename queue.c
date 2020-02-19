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
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    /* Return NULL if could not allocate space. */
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    list_ele_t *node = q->head;
    while (node != NULL) {
        list_ele_t *tmp = node;
        node = node->next;
        free(tmp->value);
        free(tmp);
        q->size--;
    }
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
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
    if (!q) {
        return false;
    }
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    newh->value = malloc(strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    q->size++;
    strncpy(newh->value, s, strlen(s) + 1);
    if (!q->head) {
        /* Queue haven't contain any element */
        newh->next = NULL;
        q->head = q->tail = newh;
    } else {
        /* Queue already have element */
        newh->next = q->head;
        q->head = newh;
    }
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
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }

    newh->value = malloc(strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    q->size++;
    strncpy(newh->value, s, strlen(s) + 1);
    q->head = q->tail ? q->head : newh;
    newh->next = NULL;
    if (q->tail)
        q->tail->next = newh;
    q->tail = newh;
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
    if (!q || !q->head)
        return false;
    list_ele_t *node = q->head;
    q->head = q->head->next;

    if (bufsize != 0) {
        if (strlen(node->value) > bufsize) {
            strncpy(sp, node->value, bufsize);
            sp[bufsize - 1] = '\0';
        } else {
            strncpy(sp, node->value, strlen(node->value) + 1);
        }
    }
    free(node->value);
    free(node);
    q->size--;
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
    if (!q || !q->head)
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head || q->size == 1)
        return;

    /* A pointer to already reversed linked lis, whicih always
       point at head of reversed list */
    list_ele_t *reverse_list = q->head;
    /* A pointer to the remaining list */
    list_ele_t *list_to_do = q->head->next;

    q->tail = reverse_list;
    reverse_list->next = NULL;

    while (list_to_do) {
        list_ele_t *tmp = list_to_do;
        list_to_do = list_to_do->next;
        tmp->next = reverse_list;
        reverse_list = tmp;
    }
    q->head = reverse_list;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
#if 0
void merge(list_ele_t *arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    list_ele_t *L[n1];
    list_ele_t *R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        printf("== %d %d ==",n1,i);
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i]->value, R[j]->value) <= 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
int min(int x, int y) 
{ 
    return (x<y)? x :y; 
}
void q_sort(queue_t *q)
{
    if (!q || !q->head || q->size == 1)
        return;

    int curr_size;  // For current size of subarrays to be merged
                   // curr_size varies from 1 to n/2
    int left_start; // For picking starting index of left subarray
                   // to be merged
    int n = q->size;
    list_ele_t *arr[n];
    list_ele_t *tmp = q->head;

    for(int i = 0; i < n && tmp != NULL; ++i){
        arr[i] = tmp;
        tmp = tmp->next;
    }

    // Merge subarrays in bottom up manner.  First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
    {
        // Pick starting point of different subarrays of current size
        for (left_start=0; left_start<n-1; left_start += 2*curr_size)
        {
            // Find ending point of left subarray. mid+1 is starting 
            // point of right
            int mid = left_start + curr_size - 1;

            int right_end = min(left_start + 2*curr_size - 1, n-1);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            merge(arr, left_start, mid, right_end);
        }
    }

    tmp = q->head = arr[0];
    q->tail = arr[n-1];
    // tmp = arr[0];
    for(int i = 1; i < n && tmp != NULL; ++i){
        tmp->next = arr[i];
        tmp = tmp->next;
    }
    q->tail->next = NULL;

}
#endif

int min(int x, int y)
{
    return (x < y) ? x : y;
}
void q_sort(queue_t *q)
{
    if (!q || !q->head || q->size == 1)
        return;
    int block_size = 1, n = q->size, i, alen, blen;
    list_ele_t virtual_head;
    list_ele_t *last = NULL, *it = NULL, *l1 = NULL, *l2 = NULL, *tmp = NULL;
    list_ele_t *l1head = NULL, *l1tail = NULL, *l2tail = NULL;
    virtual_head.next = q->head;
    while (block_size < n) {
        int iter = 0;
        last = &virtual_head;
        it = virtual_head.next;
        while (iter < n) {
            // decide each iterate time's block size a and b
            alen = min(n - iter, block_size);
            // avoid odd block
            blen = min(n - iter - alen, block_size);


            l1 = it;
            l1head = l1;
            // if left block is odd, just skip
            if (blen != 0) {
                // seperate one list in to l1 and l2
                for (i = 0; i < alen - 1; ++i)
                    it = it->next;
                l1tail = it;
                l2 = it->next;
                it->next = NULL;
                it = l2;
                for (i = 0; i < blen - 1; ++i)
                    it = it->next;
                l2tail = it;
                tmp = it->next;
                it->next = NULL;
                it = tmp;
            }

            if (block_size > 10000000 && l1head && l2tail &&
                strcmp(l1head->value, l2tail->value) == 0) {
                iter += alen + blen;
                last->next = l1;
                l1tail->next = l2;
                last = l2tail;
                l2tail->next = NULL;
            } else {
                while (l1 || l2) {
                    if (l2 == NULL ||
                        (l1 != NULL && strcmp(l1->value, l2->value) < 0)) {
                        // if l2 doesn't contain any node, just append l1 to
                        // merge list or if value of l1 is smaller
                        last->next = l1;
                        last = last->next;
                        l1 = l1->next;
                    } else {
                        // if l1 doesn't contain any node, just append l2 to
                        // merge list or if value of l2 is smaller
                        last->next = l2;
                        last = last->next;
                        l2 = l2->next;
                    }
                }
                last->next = NULL;
                iter += alen + blen;
            }
        }
        block_size <<= 1;
    }

    q->head = virtual_head.next;
    list_ele_t *nd = q->head;
    while (nd->next) {
        nd = nd->next;
    }
    q->tail = nd;
}
