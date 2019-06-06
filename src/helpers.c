//
// Created by jose on 25/05/19.
//

#include "helpers.h"

double _byte_to_mb(double b) {
    return ((b * 8.00) / 1000000.00);
}

double two_min(double a, double b) {
    return (a <= b) ? a : b;
}