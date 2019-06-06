//
// Created by jose on 25/05/19.
//

#include "validation.h"

accumulator *_create_accumulator() {
    accumulator *tmp = (accumulator *) calloc(1, sizeof(accumulator));

    return tmp;
}

/**
 *
 * @param t
 * @param time
 * @param up
 */
void cumulative_sum(accumulator *t, double time, int up) {
    t->area += t->packets_count * (time - t->past_time);
    t->past_time = time;

    if (up == 1) {
        t->packets_count++;
    } else if (up == 0) {
        t->packets_count--;
    }
}

void destroy_accumulator(accumulator *a) {
    free(a);
}