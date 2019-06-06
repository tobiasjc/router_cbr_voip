//
// Created by jose on 25/05/19.
//

#ifndef ROUTER_CBR_LIST_EXECUTION_H
#define ROUTER_CBR_LIST_EXECUTION_H

#include "validation.h"
#include "queue.h"
#include "generators.h"
#include "voip_tunnel.h"
#include "helpers.h"

execution *create_execution(parameters *p);

void destroy_execution(execution *e);

#endif //ROUTER_CBR_LIST_EXECUTION_H
