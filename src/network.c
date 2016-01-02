/*
Authors: Alexandros Tsonis, Sotiris Papatheodorou

This file is part of NeuroticNetwork.

NeuroticNetwork is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

NeuroticNetwork is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with NeuroticNetwork.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "neuron.h"
#include "network.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
/*
===========================================================================
Public Function Declarations
===========================================================================
*/


/*Network creation*/
/*NO ERROR CHECKING*/
/*ONLY CHECKS FOR MEMORY ERRORS*/
int create_network               (int               num_of_inputs,
                                  int               num_of_layers,
                                  int               *neurons_per_layer,//make this argument optional
                                  struct neural_net **network_addr){
    //Variable Declaration
    struct neural_net *network;
    neuron *neuron_table_address,*input_pointer;
    int neuron_counter,sum_of_neurons=0,current_layer_neuron=0,layer_counter=0,weight_counter,current_num_of_inputs;
    double *weights_of_neurons;
    
    
    //Memory allocation of network
    network = malloc(sizeof(struct neural_net));
    if (network == NULL) {//Check if memory was available to allocate
        printf("\n---NOT ENOUGH MEMORY FOR NETWORK CREATION---\n");
        return _CREATION_MEMORY_ERROR;
    }
    network->num_of_inputs      = num_of_inputs;
    network->num_of_layers      = num_of_layers;
    network->neurons_per_layer  = neurons_per_layer;
    for (neuron_counter = 0; neuron_counter < num_of_layers; neuron_counter++) {
        sum_of_neurons += neurons_per_layer[neuron_counter];//Calculate the sum of neurons to allocate the required memory
    }
    sum_of_neurons              += num_of_inputs;
    neuron_table_address        = malloc(sum_of_neurons*sizeof(neuron));
    if (neuron_table_address == NULL) {//Check if memory was available to allocate
        printf("\n---NOT ENOUGH MEMORY FOR NETWORK CREATION---\n");
        free(network);//Deallocate any allocated memory
        return _CREATION_MEMORY_ERROR;
    }
    network->neuron_table       = neuron_table_address;
    network->sum_of_neurons     = sum_of_neurons;
    srand(time(NULL));
    //Network Setup
    input_pointer = network->neuron_table;
    for (neuron_counter = num_of_inputs; neuron_counter < sum_of_neurons; neuron_counter++) {
        current_layer_neuron += 1;
        if (current_layer_neuron > neurons_per_layer[layer_counter]) {//Layer change
            layer_counter += 1;
            current_layer_neuron = 1;
            input_pointer = &(network->neuron_table[neuron_counter - neurons_per_layer[layer_counter-1]]);
        }
        neuron_init(&(network->neuron_table[neuron_counter]));
        if (layer_counter == 0) {
            current_num_of_inputs = num_of_inputs;
        }
        else {
            current_num_of_inputs = neurons_per_layer[layer_counter - 1];
        }
        network->neuron_table[neuron_counter].num_inputs = current_num_of_inputs;
        weights_of_neurons = malloc(current_num_of_inputs*sizeof(double));
        if (weights_of_neurons == NULL) {//Check if memory was available to allocate
            printf("\n---NOT ENOUGH MEMORY FOR NETWORK CREATION---\n");
            //Delete each neuron
            for (neuron_counter = neuron_counter; neuron_counter >= 0; neuron_counter--) {
                neuron_free(&(network->neuron_table[neuron_counter]));
                free(&(network->neuron_table[neuron_counter]));
            }
            free(network);//Deallocate any allocated memory
            return _CREATION_MEMORY_ERROR;
        }
        for (weight_counter = 0; weight_counter < current_num_of_inputs; weight_counter++) {
            weights_of_neurons[weight_counter] = (double)rand() / (double)RAND_MAX;
        }
        network->neuron_table[neuron_counter].weights = weights_of_neurons;
        network->neuron_table[neuron_counter].inputs = input_pointer;
    }
    
    
    //Input layer initialization
    for (neuron_counter = 0; neuron_counter < num_of_inputs; neuron_counter++) {
        neuron_init(&(network->neuron_table[neuron_counter]));
    }


    *network_addr = network;//Return the address of the network struct
    return _RETURN_SUCCESS;
}


void change_input          (double                  *input_vector,
                            struct neural_net       *network_addr){
    //Variable Declaration
    int input_neuron_counter;

    //Outputs of the input layer equal to the elements of the input vector
    for (input_neuron_counter = 0; input_neuron_counter < network_addr->num_of_inputs; input_neuron_counter++) {
        network_addr->neuron_table[input_neuron_counter].output = input_vector[input_neuron_counter];
    }
}

void network_activate      (struct neural_net       *network) {
    //Variable Declaration
    int neuron_counter;

    //Goes through all the neurons from input layer to output and activates them
    for (neuron_counter = network->num_of_inputs; neuron_counter < network->sum_of_neurons; neuron_counter++) {
        neuron_activate(&(network->neuron_table[neuron_counter]));
    }
}

void network_delta         (struct neural_net       *network,
                            int                     layer_pointer,
                            int                     neuron_pointer,
                            double                  *deltaw){
    //Variable declaration
    int local_neuron_pointer = network->num_of_inputs, local_layer_pointer = 0, difference = 0;


    //Neuron search
    while (local_layer_pointer < layer_pointer) {
        difference += 1;
        local_neuron_pointer += 1;
        if (difference == network->neurons_per_layer[local_layer_pointer]) {
            local_layer_pointer += 1;
            difference = 0;
        }
    }

    local_neuron_pointer += neuron_pointer-1;
    neuron_deltaw(&(network->neuron_table[local_neuron_pointer]), deltaw);
}

void network_setw          (struct neural_net       *network,
                            int                     layer_pointer,
                            int                     neuron_pointer,
                            double                  *deltaw){
    //Variable Declaration
    int local_neuron_pointer = network->num_of_inputs, local_layer_pointer = 0, difference = 0;


    //Neuron search
    while (local_layer_pointer < layer_pointer) {
        difference += 1;
        local_neuron_pointer += 1;
        if (difference == network->neurons_per_layer[local_layer_pointer]) {
            local_layer_pointer += 1;
            difference = 0;
        }
    }

    local_neuron_pointer += neuron_pointer;
    neuron_setw(&(network->neuron_table[local_neuron_pointer]), deltaw);
}

void network_delete          (struct neural_net       *network){
    //Variable Declaration
    int neuron_counter;

    //Delete each neuron
    for (neuron_counter = network->sum_of_neurons - 1; neuron_counter >= 0; neuron_counter--) {
        neuron_free(&(network->neuron_table[neuron_counter]));
    }
    free(network->neuron_table);
    //Delete network struct
    free(network);
}


void errorback               (struct neural_net       *network,
                              double                  *intended_output){
    //Variable Declaration
    double *delta,*deltaweights,check;
    int maxim,layer_counter = network->num_of_layers - 1, neuron_counter, intended_output_index,next_layer,temporary_neuron_counter,temporary_neuron_layer_pointer,temporary_iterator,weight_pointer;
    next_layer = network->num_of_layers - 1;
    delta = malloc(network->sum_of_neurons*sizeof(double));
    intended_output_index = network->neurons_per_layer[network->num_of_layers - 1]-1;
    

    //Output layer delta calculation
    for (neuron_counter = network->sum_of_neurons - 1;neuron_counter > ((network->sum_of_neurons - 1) - (network->neurons_per_layer[network->num_of_layers - 1])); neuron_counter--) {
        delta[neuron_counter] = (network->neuron_table[neuron_counter].output - intended_output[intended_output_index])*(network->neuron_table[neuron_counter].output)*(1 - (network->neuron_table[neuron_counter].output));
        intended_output_index--;
    }



    temporary_neuron_layer_pointer = neuron_counter + 1;
    weight_pointer = network->neurons_per_layer[next_layer-1]-1;
    //Inner layer delta calculation
    for (neuron_counter = neuron_counter; neuron_counter > network->num_of_inputs-1; neuron_counter--) {
        temporary_iterator = 0;
        delta[neuron_counter] = 0;
        for (temporary_neuron_counter = temporary_neuron_layer_pointer; temporary_iterator < network->neurons_per_layer[next_layer];temporary_neuron_counter++) {
            delta[neuron_counter] += delta[temporary_neuron_counter] * (network->neuron_table[temporary_neuron_counter].weights[weight_pointer]);
            temporary_iterator++;
        }
        delta[neuron_counter] *= (network->neuron_table[neuron_counter].output)*(1 - (network->neuron_table[neuron_counter].output));
        weight_pointer--;
        if (temporary_neuron_layer_pointer - (neuron_counter) == network->neurons_per_layer[next_layer - 1]) {
            temporary_neuron_layer_pointer = neuron_counter;
            next_layer--;
            weight_pointer = network->neurons_per_layer[next_layer - 1] - 1;
        }
    }


    //Calculation of deltaweights
    maxim = network->neurons_per_layer[0];
    for (temporary_iterator = 1; temporary_iterator < network->num_of_layers - 1; temporary_iterator++) {
        maxim = max(maxim, network->neurons_per_layer[temporary_iterator]);
    }
    maxim = max(maxim, network->num_of_inputs);
    deltaweights = malloc(maxim*sizeof(double));
    for (neuron_counter = network->num_of_inputs; neuron_counter < network->sum_of_neurons; neuron_counter++) {
        for (temporary_neuron_counter = 0; temporary_neuron_counter < network->neuron_table[neuron_counter].num_inputs; temporary_neuron_counter++) {
            check = fabs(network->neuron_table[neuron_counter].weights[temporary_neuron_counter]);
            if (check == check){
                deltaweights[temporary_neuron_counter] = (-0.2)* delta[neuron_counter] * (network->neuron_table[neuron_counter].inputs[temporary_neuron_counter].output);
            }
            else {
                deltaweights[temporary_neuron_counter] = 0;
            }
        }
        neuron_deltaw(&(network->neuron_table[neuron_counter]), deltaweights);
    }
    //normalize_weights(network);
    free(deltaweights);
    free(delta);
}

void normalize_weights(struct neural_net       *network) {
    int neuron_counter,inner_neuron_counter;
    double total;
    for (neuron_counter = network->num_of_inputs; neuron_counter < network->sum_of_neurons; neuron_counter++) {
        total = 0;
        for (inner_neuron_counter = 0; inner_neuron_counter < network->neuron_table[neuron_counter].num_inputs; inner_neuron_counter++) {
            total += fabs(network->neuron_table[neuron_counter].weights[inner_neuron_counter]);
        }
        for (inner_neuron_counter = 0; inner_neuron_counter < network->neuron_table[neuron_counter].num_inputs; inner_neuron_counter++) {
            network->neuron_table[neuron_counter].weights[inner_neuron_counter] = network->neuron_table[neuron_counter].weights[inner_neuron_counter] / total;
        }
    }
}

void print_weights(struct neural_net       *network) {
    int neuron_counter, inner_neuron_counter;
    system("cls");
    for (neuron_counter = network->num_of_inputs; neuron_counter < network->sum_of_neurons; neuron_counter++) {
        for (inner_neuron_counter = 0; inner_neuron_counter < network->neuron_table[neuron_counter].num_inputs; inner_neuron_counter++) {
            printf("neuron: %d, weight:%d = %lf\n", neuron_counter, inner_neuron_counter, network->neuron_table[neuron_counter].weights[inner_neuron_counter]);
        }
    }
}