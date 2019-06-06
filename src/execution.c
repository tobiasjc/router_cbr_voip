//
// Created by jose on 25/05/19.
//

#include "execution.h"
#include "types.h"

execution *create_execution(parameters *p) {
    execution *tmp = (execution *) calloc(1, sizeof(execution));

    tmp->next_packet_arrival = gen_exp(p->data_packet_interval);
    tmp->next_voip_arrival = gen_exp(p->voip_interval);
    tmp->vt = create_voip_tunnel();
    tmp->q = create_queue();
    tmp->w_in = _create_accumulator();
    tmp->w_out = _create_accumulator();
    tmp->l = _create_accumulator();

    return tmp;
}

void destroy_execution(execution *e) {
    destroy_queue(e->q);
    destroy_voip_tunnel(e->vt);
    destroy_accumulator(e->l);
    destroy_accumulator(e->w_in);
    destroy_accumulator(e->w_out);
    free(e);
}