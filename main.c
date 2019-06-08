#include "IO_manager.h"
#include "queue.h"
#include "voip_tunnel.h"
#include "generators.h"
#include "validation.h"
#include "execution.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define USER 1

int main(int argc, char **argv) {
    int seed = 1556915527;
    srandom(seed);

    parameters *p = create_parameters();

    if (USER)
        read_users_input(p);
    else
        read_system_input(p, argv);

    execution *e = create_execution(p);

    display_expectations(p);
    while (e->time <= p->total_time) {
        if ((e->q->size == 0) && (e->vt->size == 0)) {
            e->time = two_min(e->next_packet_arrival, e->next_voip_arrival);
        } else if (e->q->size == 0) {
            e->time = two_min(two_min(e->next_packet_arrival, e->next_voip_arrival), e->vt->head->next_cbr);
        } else if (e->vt->size == 0) {
            e->time = two_min(two_min(e->next_packet_arrival, e->next_voip_arrival), e->packet_exit);
        } else {
            e->time = two_min(two_min(two_min(e->next_packet_arrival, e->next_voip_arrival), e->packet_exit),
                              e->vt->head->next_cbr);
        }

        if (e->time == e->next_packet_arrival) {
            double packet_size = gen_packet_size();
            if (e->q->size == 0) {
                e->packet_exit = e->time + (packet_size / p->link_speed);
                e->occupancy += e->packet_exit - e->time;
            }

            // add packet to the queue and generate the next arrival time for a experiment packet
            enqueue(e->q, packet_size);
            e->next_packet_arrival = e->time + gen_exp(p->data_packet_interval);

            // accumulator calculation packet arrival
            cumulative_sum(e->l, e->time, 1);
            cumulative_sum(e->w_in, e->time, 1);
        } else if (e->time == e->next_voip_arrival) {
            insert_new_connection(e->vt, p->cbr_packet_interval, e->time, p->voip_duration);

            if (e->q->size == 0) {
                e->packet_exit = e->time + (p->cbr_packet_size / p->link_speed);
                e->occupancy += e->packet_exit - e->time;
            }

            // add cbr packet from void connection on queue, and generate the next voip connection arrival time
            enqueue(e->q, p->cbr_packet_size);
            e->next_voip_arrival = e->time + gen_exp(p->voip_interval);

            // accumulator calculation packet arrival
            cumulative_sum(e->l, e->time, 1);
            cumulative_sum(e->w_in, e->time, 1);
        } else if ((e->vt->head != NULL) && (e->time == e->vt->head->next_cbr)) {
            voip_connection *tmp = attend_connection(e->vt);
            if (e->q->size == 0) {
                e->packet_exit = e->time + (p->cbr_packet_size / p->link_speed);
                e->occupancy += e->packet_exit - e->time;
            }

            // add the cbr packet to the queue and verify where the connection will be put back in the circular queue
            enqueue(e->q, p->cbr_packet_size);

            if ((tmp->next_cbr + p->cbr_packet_interval) <= tmp->end) {
                tmp->next_cbr += p->cbr_packet_interval;
                insert_tail_connection(e->vt, tmp);
            } else if ((tmp->next_cbr + p->cbr_packet_interval) > tmp->end) {
                destroy_voip_connection(tmp);
            }

            // accumulator calculation packet arrival
            cumulative_sum(e->l, e->time, 1);
            cumulative_sum(e->w_in, e->time, 1);
        } else if (e->time == e->packet_exit) { // packet exiting modem -> exiting queue
            dequeue(e->q);
            if (e->q->size > 0) {
                e->packet_exit = e->time + (e->q->first->size / p->link_speed);
                e->occupancy += e->packet_exit - e->time;
            }

            // accumulator calculation packet exit
            cumulative_sum(e->l, e->time, 0);
            cumulative_sum(e->w_out, e->time, 1);
        }
    }
    // accumulator calculation packet exit
    cumulative_sum(e->w_in, e->time, 1);
    cumulative_sum(e->w_out, e->time, 1);
    display_results(e);

    // destroy structures
    destroy_execution(e);
    destroy_parameters(p);
    return 0;
}

//Total time of the simulation (seconds):
//885
//Experiment packet arrival interval (seconds):
//0.003528
//CBR packet size (bytes):
//1700
//CBR packet interval (seconds):
//0.02
//Voip arrival interval (seconds):
//0.453333
//Voip connection duration (seconds):
//2
//Link speed (Mbits/s):
//10
