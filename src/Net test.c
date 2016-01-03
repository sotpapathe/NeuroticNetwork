//Neural Network Testing

#include <stdlib.h>
#include <stdio.h>
#include "neuron.h"
#include "network.h"

int main() {
    int npl[3],ret=0,neuroncounter;
    double input[3],intendedout;
    struct neural_net *net;
    npl[0] = 3;
    npl[1] = 3;
    npl[2] = 1;
    ret = create_network(3, 3, npl, &net);
    if (ret == _CREATION_MEMORY_ERROR) {
        return EXIT_FAILURE;
    }
    printf("Function returned %d\n Press any key", ret);
    scanf_s("%d", &ret);
    ret = 0;
    for (ret = 0;ret < 2000000; ret++) {
        input[0] = ret % 2;
        if (input[0] == 0) {
            input[1] = ((int)input[1] + 1) % 2;
            if (input[1] == 0) {
                input[2] = ((int)input[2] + 1) % 2;
            }
        }
        intendedout = ((int)input[0] +(int)input[1] + (int)input[2]) % 2;
        change_input(input, net);
        network_activate(net);
        errorback(net, &intendedout);
        if (ret % 100000==0) {
            print_weights(net);
        }
    }
    printf("Enter first input\n 380 is the exit number\n");
    scanf_s("%lf", &input[0]);
    while (input[0] != 380) {
        printf("\nEnter second input\n");
        scanf_s("%lf", &input[1]);
        printf("\nEnter third input\n");
        scanf_s("%lf", &input[2]);
        change_input(input, net);
        network_activate(net);
        printf("\nPRINTING OUTPUTS\n");
        for (neuroncounter = net->num_of_inputs; neuroncounter < net->sum_of_neurons; neuroncounter++) {
            input[0] = net->neuron_table[neuroncounter].output;
            printf("%lf\n", input[0]);
        }
        printf("Enter first input\n 380 is the exit number\n");
        scanf_s("%lf", input);
    }
    network_delete(net);
    return _RETURN_SUCCESS;
}