//
// Created by jose on 25/05/19.
//

#ifndef ROUTER_CBR_LIST_TYPES_H
#define ROUTER_CBR_LIST_TYPES_H


typedef struct packet_ {
    double size;
    struct packet_ *next;
} packet;

typedef struct queue_ {
    int size;
    struct packet_ *first;
    struct packet_ *last;
} queue;

typedef struct accumulator_ {
    double past_time;
    double area;
    double packets_count;
} accumulator;

typedef struct voip_connection_ {
    double end;
    double next_cbr;
    struct voip_connection_ *next;
} voip_connection;

typedef struct voip_tunnel_ {
    int size;
    struct voip_connection_ *head;
    struct voip_connection_ *tail;
} voip_tunnel;

typedef struct parameters_ {
    double total_time;
    double data_packet_interval;
    double cbr_packet_size;
    double cbr_packet_interval;
    double voip_interval;
    double voip_duration;
    double link_speed;
} parameters;

typedef struct execution_ {
    double occupancy;
    double packet_exit;
    double next_packet_arrival;
    double next_voip_arrival;
    double time;
    voip_tunnel *vt;
    queue *q;
    accumulator *l;
    accumulator *w_in;
    accumulator *w_out;
} execution;
#endif //ROUTER_CBR_LIST_TYPES_H
