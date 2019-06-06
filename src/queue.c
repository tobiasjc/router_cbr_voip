//
// Created by jose on 16/05/19.
//

#include "queue.h"

/**
 *
 * @param q queue pointer
 * @param s size of the packet
 */
void enqueue(queue *q, double s) {
    packet *np = (packet *) malloc(sizeof(packet));
    np->size = s;
    np->next = NULL;
    if (q->size == 0) {
        q->first = np;
        q->last = q->first;
    } else {
        q->last->next = np;
        q->last = np;
    }
    q->size++;
}

/**
 *
 * @param q
 * @return
 */
void dequeue(queue *q) {
    if (q->size == 0) {
        abort();
    }
    packet *tmp = q->first;
    q->first = tmp->next;
    free(tmp);
    q->size--;
}

/**
 *
 * @return
 */
queue *create_queue() {
    queue *tmp = (queue *) malloc(sizeof(queue));

    tmp->size = 0;
    tmp->first = NULL;
    tmp->last = NULL;

    return tmp;
}

/**
 *
 * @param p
 */
void destroy_packet(packet *p) {
    free(p);
}

/**
 *
 * @param q
 */
void destroy_queue(queue *q) {
    while (q->first != NULL) {
        packet *tmp = q->first;
        q->first = q->first->next;
        destroy_packet(tmp);
    }
    free(q);
}