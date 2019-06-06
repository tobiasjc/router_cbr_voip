// Created by jose on 25/05/19.
//

#ifndef ROUTER_CBR_LIST_VALIDATION_H
#define ROUTER_CBR_LIST_VALIDATION_H

#include <stdlib.h>
#include "types.h"

accumulator *_create_accumulator();

void cumulative_sum(accumulator *t, double time, int up);

void destroy_accumulator(accumulator *a);

#endif //ROUTER_CBR_LIST_VALIDATION_H
