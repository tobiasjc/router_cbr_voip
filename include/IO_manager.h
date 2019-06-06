//
// Created by jose on 25/05/19.
//

#ifndef ROUTER_CBR_LIST_IO_MANAGER_H
#define ROUTER_CBR_LIST_IO_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "validation.h"
#include "execution.h"
#include "types.h"

parameters *create_parameters();

void read_users_input(parameters *p);

void display_expectations(parameters *p);

void display_results(execution *e);

void destroy_parameters(parameters *p);

void read_system_input(parameters *p, char **argv);

#endif //ROUTER_CBR_LIST_IO_MANAGER_H
