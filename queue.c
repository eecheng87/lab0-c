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
    list_ele_t *l1head = NULL, *l1tail = NULL, *l2head = NULL, *l2tail = NULL;
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
            // printf("%d %d block size: %d\n",alen,blen,block_size);

            l1 = it;
            l1head = l1;
            // if left block is odd, just skip
            if (alen == blen && alen > 1) {
                // printf("hi");
                list_ele_t *slow = l1head;
                for (i = 0; i < alen - 1; ++i) {
                    slow = slow->next;
                    it = it->next->next;
                }
                it = it->next;
                l1tail = slow;
                l2 = l2head = slow->next;
                slow->next = NULL;
                l2tail = it;
                tmp = it->next;
                it->next = NULL;
                it = tmp;
            } else if (blen != 0) {
                // seperate one list into l1 and l2
                for (i = 0; i < alen - 1; ++i)
                    it = it->next;
                l1tail = it;
                l2 = l2head = it->next;
                it->next = NULL;
                it = l2head;
                for (i = 0; i < blen - 1; ++i)
                    it = it->next;
                l2tail = it;
                tmp = it->next;
                it->next = NULL;
                it = tmp;
            } else {
                l2 = l2head = l2tail = NULL;
                l1tail = l1head;
                while (l1tail->next) {
                    l1tail = l1tail->next;
                }
            }

            if (l1head && l2tail && l1tail && l2head &&
                strcmp(l1head->value, l1tail->value) == 0 &&
                strcmp(l1head->value, l2head->value) == 0 &&
                strcmp(l1head->value, l2tail->value) == 0) {
                // printf("%d\n",iter);
                iter += alen + blen;
                last->next = l1head;
                l1tail->next = l2head;
                last = l2tail;
                l2tail->next = NULL;
                q->tail = l2tail;
            } else {
                while (l1 && l2) {
                    if (strcmp(l1->value, l2->value) <= 0) {
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
                if (l1) {
                    // printf("l1: %d\n",alen);
                    last->next = l1;
                    last = l1tail;
                }
                if (l2) {
                    // printf("l2: %d\n",blen);
                    last->next = l2;
                    last = l2tail;
                }
                l2 = NULL;

                if (last)
                    last->next = NULL;
                // q->tail = last;
                iter += alen + blen;
            }
        }
        block_size <<= 1;
    }

    q->head = virtual_head.next;
    list_ele_t *nd = q->head;
    while (nd->next) {
        // printf("%s->",nd->value);
        nd = nd->next;
    }
    q->tail = nd;
}
