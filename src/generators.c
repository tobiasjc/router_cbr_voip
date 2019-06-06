//
// Created by jose on 25/05/19.
//

#include "generators.h"

double gen_factor() {
    double u = random() % RAND_MAX;
    u = u / RAND_MAX;
    return (1.0 - u);
}

double gen_exp(double l) {
    return ((-1.0 / l) * log(gen_factor()));
}

double gen_packet_size() {
    double f = gen_factor();
    if (f <= 0.5) {
        return _byte_to_mb(550.00);
    } else if (f <= 0.9) {
        return _byte_to_mb(40.00);
    } else {
        return _byte_to_mb(1500.00);
    }
}