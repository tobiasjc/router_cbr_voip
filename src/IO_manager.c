//
// Created by jose on 25/05/19.
//

#include "IO_manager.h"

parameters *create_parameters() {
    parameters *tmp = (parameters *) calloc(1, sizeof(parameters));

    return tmp;
}

void read_system_input(parameters *p, char **argv) {
    p->total_time = strtod(argv[1], NULL);
    p->data_packet_interval = strtod(argv[2], NULL);
    p->cbr_packet_size = strtod(argv[3], NULL);
    p->cbr_packet_interval = strtod(argv[4], NULL);
    p->voip_interval = strtod(argv[5], NULL);
    p->voip_duration = strtod(argv[6], NULL);
    p->link_speed = strtod(argv[7], NULL);

    printf("Executing with parameters:\n");
    printf("Total time -> %lf\n", p->total_time);
    printf("Continuous packet interval(s) -> %lf\n", p->data_packet_interval);
    p->data_packet_interval = 1.0 / p->data_packet_interval;
    printf("CBR packet size(B) -> %lf\n", p->cbr_packet_size);
    p->cbr_packet_size = _byte_to_mb(p->cbr_packet_size);
    printf("CBR packet interval(s) -> %lf\n", p->cbr_packet_interval);
    printf("Voip connection interval(s) -> %lf\n", p->voip_interval);
    p->voip_interval = 1.0 / p->voip_interval;
    printf("Voip connection duration(s) -> %lf\n", p->voip_duration);
    p->voip_duration = 1 / p->voip_duration;
    printf("Link speed(Mb/s) -> %lf\n", p->link_speed);
}

void read_users_input(parameters *p) {
    char input[1024];

    printf("Total time of the simulation (seconds): \n");
    fgets(input, sizeof(input), stdin);
    while ((p->total_time = strtod(input, NULL)) == 0.0) {
        printf("Enter a valid simulation duration in (0.0, inf] seconds range: \n");
        fgets(input, sizeof(input), stdin);
    }
    fflush(stdin);

    printf("Experiment packet arrival interval (seconds): \n");
    fgets(input, sizeof(input), stdin);
    while ((p->data_packet_interval = strtod(input, NULL)) == 0.0) {
        printf("Enter a valid experiment packet arrival interval time in (0.0, inf] seconds range: \n");
        fgets(input, sizeof(input), stdin);
    }
    p->data_packet_interval = 1.0 / p->data_packet_interval;
    fflush(stdin);

    printf("CBR packet size (bytes): \n");
    fgets(input, sizeof(input), stdin);
    while ((p->cbr_packet_size = strtod(input, NULL)) == 0.0) {
        printf("Enter a valid CBR packet size in (0.0, inf] bytes range: \n");
        fgets(input, sizeof(input), stdin);
    }
    p->cbr_packet_size = _byte_to_mb(p->cbr_packet_size);
    fflush(stdin);

    printf("CBR packet interval (seconds): \n");
    fgets(input, sizeof(input), stdin);
    while ((p->cbr_packet_interval = strtod(input, NULL)) == 0.0) {
        printf("Enter a valid CBR packet interval in (0.0, inf] seconds range: \n");
        fgets(input, sizeof(input), stdin);
    }
    fflush(stdin);

    printf("Voip arrival interval (seconds): \n");
    fgets(input, sizeof(input), stdin);
    while ((p->voip_interval = strtod(input, NULL)) == 0.0) {
        printf("Enter a valid voip arrival interval in (0.0, inf] seconds range: \n");
        fgets(input, sizeof(input), stdin);
    }
    p->voip_interval = 1.0 / p->voip_interval;
    fflush(stdin);

    printf("Voip connection duration (seconds): \n");
    fgets(input, sizeof(input), stdin);
    while ((p->voip_duration = strtod(input, NULL)) == 0.0) {
        printf("Enter a valid voip duration in (0.0, inf] seconds range: \n");
        fgets(input, sizeof(input), stdin);
    }
    p->voip_duration = 1 / p->voip_duration;
    fflush(stdin);

    printf("Link speed (Mbits/s): \n");
    fgets(input, sizeof(input), stdin);
    while ((p->link_speed = strtod(input, NULL)) == 0.0) {
        printf("Enter a valid link size in (0.0, inf] Mbits/s range: \n");
        fgets(input, sizeof(input), stdin);
    }
    fflush(stdin);
}

void display_results(execution *e) {
    // generating final increment, either w_in or w_out will sum zero
    e->w_in->area += e->w_in->packets_count * (e->time - e->w_in->past_time);
    e->w_out->area += e->w_out->packets_count * (e->time - e->w_out->past_time);

    double ew = e->w_in->area - e->w_out->area;
    double en_val = (e->l->area / e->time);
    ew = ew / e->w_in->packets_count;
    double lambda = e->w_in->packets_count / e->time;

    printf("L = %lf\n", en_val);
    printf("W = %lf\n", ew);
    printf("lambda = %lf\n", lambda);
    printf("L - (lambda * W) = %lf\n", (en_val - lambda * ew));

    printf("occupancy = %lf\n", (e->occupancy / e->time));
}


void display_expectations(parameters *p) {

}

void destroy_parameters(parameters *p) {
    free(p);
}