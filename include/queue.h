//
// Created by jose on 16/05/19.
//

#ifndef ROUTER_CBR_LIST_QUEUE_H
#define ROUTER_CBR_LIST_QUEUE_H

#include <stdlib.h>
#include "types.h"

void dequeue(queue *q);

void enqueue(queue *q, double s);

queue *create_queue();

void destroy_queue(queue *q);

void destroy_packet(packet *p);

#endif //ROUTER_CBR_LIST_QUEUE_H