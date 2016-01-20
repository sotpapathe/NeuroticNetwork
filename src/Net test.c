//Neural Network Testing

#include <stdlib.h>
#include <stdio.h>
#include "neuron.h"
#include "network.h"

int main() {
    int npl[3],ret=0,retbef=0,count,tempret,neuroncounter;
    double *input,*intendedout;
    struct neural_net *net;
    npl[0] = 10;
    npl[1] = 10;
    npl[2] = 2;
    ret = create_network(3, 3, npl, &net);
    if (ret == _CREATION_MEMORY_ERROR) {
        return EXIT_FAILURE;
    }
    printf("Function returned %d\n Press any key", ret);
    scanf_s("%d", &ret);
    ret = EXIT_FAILURE;
    count = 0;
    input = malloc(8 * 3 * sizeof(double));
    intendedout = malloc(8 * 2 * sizeof(double));
    input[0] = 0;
    input[1] = 0;
    input[2] = 0;
    intendedout[0] = 0;
    intendedout[1] = 1;
    printf("%lf\t%lf\t%lf\n", input[count * 3], input[count * 3 + 1], input[count * 3 + 2]);
    for (count = 1;count < 8;count++) {
        input[count*3] = count % 2;
        input[count * 3 + 1] = input[count * 3 - 2];
        input[count * 3 + 2] = input[count * 3 - 1];
        if (input[count * 3] == 0) {
            input[count * 3 + 1] = ((int)input[count * 3 - 2] + 1) % 2;
            if (input[count * 3 + 1] == 0) {
                input[count * 3 + 2] = ((int)input[count * 3 - 1] + 1) % 2;
            }
        }
        printf("%lf\t%lf\t%lf\n", input[count * 3], input[count * 3 + 1], input[count * 3 + 2]);
        intendedout[count * 2] = ((int)input[count*3]+(int)input[count*3+1]+(int)input[count*3+2]) % 2;
        intendedout[count * 2 + 1] = ((int)intendedout[count*2] + 1) % 2;
        printf("%lf\t%lf\n", intendedout[count * 2], intendedout[count * 2 + 1]);
    }
    network_print(net);
    printf("Beginning learning process\n");
    network_print(net);
    count = 0;
    while (network_test(net, input, intendedout, 8)) {
        network_learn(net, input, intendedout, 8);
        count++;
        if (count % 10000 == 0) {
            count = 0;
            network_print_output_only(net);
            printf("%d", network_test(net, input, intendedout, 8));
        }
    }
    printf("Function returned %d\n Press any key", ret);
    printf("Enter first input\n 380 is the exit number\n");
    scanf_s("%lf", &input[0]);
    while (input[0] != 380) {
        printf("\nEnter second input\n");
        scanf_s("%lf", &input[1]);
        printf("\nEnter third input\n");
        scanf_s("%lf", &input[2]);
        change_input(input, net);
        network_activate(net);
        //network_print_whole_out(net);
        network_print_output_only(net);
        printf("Enter first input\n 380 is the exit number\n");
        scanf_s("%lf", input);
    }
    network_delete(net);
    return EXIT_SUCCESS;
}