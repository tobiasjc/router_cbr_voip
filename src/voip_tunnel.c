#include "voip_tunnel.h"

voip_tunnel *create_voip_tunnel() {
    voip_tunnel *tmp = (voip_tunnel *) malloc(sizeof(voip_tunnel));
    tmp->head = NULL;
    tmp->size = 0;

    return tmp;
}

voip_connection *create_voip_connection(double cbr_interval, double time, double duration) {
    voip_connection *tmp = (voip_connection *) malloc(sizeof(voip_connection));

    tmp->end = time + gen_exp(duration);
    tmp->next_cbr = time + cbr_interval;
    tmp->next = NULL;

    return tmp;
}

void insert_new_connection(voip_tunnel *vt, double gap, double t, double d) {
    voip_connection *nc = create_voip_connection(gap, t, d);

    if (vt->size == 0) {
        vt->head = nc;
    } else {
        if (vt->size == 1) {
            vt->head->next = nc;
            vt->tail = nc;
        } else {
            vt->tail->next = nc;
            vt->tail = nc;
        }
    }
    vt->size += 1;
}

void insert_tail_connection(voip_tunnel *vt, voip_connection *vc) {
    if (vt->size > 0) {
        if (vt->tail != NULL) {
            vt->tail->next = vc;
            vt->tail = vc;
            vc->next = NULL;
        } else {
            vt->tail = vc;
            vc->next = NULL;
        }
    } else {
        vc->next = NULL;
        vt->head = vc;
    }
    vt->size += 1;
}

void insert_ending_connection(voip_tunnel *vt, voip_connection *vc) {
    if (vt->size > 0) {
        if (vc->next_cbr < vt->head->next_cbr) {
            vc->next = vt->head;
            vt->head = vc;
        } else {
            voip_connection *pre = vt->head;
            voip_connection *fwd = pre->next;
            while ((fwd != NULL) && (fwd->next_cbr <= vc->next_cbr)) {
                pre = fwd;
                fwd = pre->next;
            }
            if (fwd == NULL) {
                pre->next = vc;
                vt->tail = vc;
                vc->next = NULL;
            } else {
                pre->next = vc;
                vc->next = fwd;
            }
        }
    } else {
        vt->head = vc;
        vc->next = NULL;
    }
    vt->size += 1;
}

voip_connection *attend_connection(voip_tunnel *vt) {
    voip_connection *tmp = vt->head;
    vt->size -= 1;
    if (vt->size == 0) {
        vt->head = NULL;
    } else {
        vt->head = tmp->next;
    }
    return tmp;
}

void destroy_voip_connection(voip_connection *vc) {
    free(vc);
}

void destroy_voip_tunnel(voip_tunnel *vt) {
    while (vt->head != NULL) {
        voip_connection *tmp = vt->head;
        vt->head = tmp->next;
        destroy_voip_connection(tmp);
    }
    free(vt);
}