#include <stdio.h>
#include <stdlib.h>

#ifndef ROUTER_CBR_LIST_VOIP_TUNNEL_H
#define ROUTER_CBR_LIST_VOIP_TUNNEL_H

#include "types.h"
#include "generators.h"

voip_tunnel *create_voip_tunnel();

voip_connection *create_voip_connection(double cbr_interval, double time, double duration);

void insert_new_connection(voip_tunnel *vt, double gap, double t, double d);

void insert_tail_connection(voip_tunnel *vt, voip_connection *vc);

void insert_ending_connection(voip_tunnel *vt, voip_connection *vc);

voip_connection *attend_connection(voip_tunnel *vt);

void destroy_voip_connection(voip_connection *vc);

void destroy_voip_tunnel(voip_tunnel *vt);

#endif