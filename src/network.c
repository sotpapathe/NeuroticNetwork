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

    struct neural_net *network;
    neuron *neuron_table_address;
    int neuron_counter,sum_of_neurons=0;
    //Memory allocation of network
    network = malloc(sizeof(struct neural_net);
    if (network == nullptr) {//Check if memory was available to allocate
        printf("\n---NOT ENOUGH MEMORY FOR NETWORK CREATION---\n");
        return _CREATION_MEMORY_ERROR;
    }
    network->num_of_inputs      = num_of_inputs;
    network->num_of_layers      = num_of_layers;
    network->neurons_per_layer  = neurons_per_layer;
    network->input_vector       = nullptr;
    for (neuron_counter = 0; neuron_counter < num_of_layers; neuron_counter++) {
        sum_of_neurons += *neurons_per_layer[neuron_counter];//Calculate the sum of neurons to allocate the required memory
    }
    sum_of_neurons              += num_of_inputs;
    neuron_table_address        = malloc(sum_of_neurons*sizeof(neuron));
    if (neuron_table_address == nullptr) {//Check if memory was available to allocate
        printf("\n---NOT ENOUGH MEMORY FOR NETWORK CREATION---\n");
        free(network);//Deallocate any allocated memory
        return _CREATION_MEMORY_ERROR;
    }
    network->neuron_table       = neuron_table_address;
    *network_addr = network;
    //Network Setup
    for (neuron_counter = num_of_inputs; neuron_counter < sum_of_neurons; neuron_counter++) {
        neuron_init(&(network->neuron_table[neuron_counter]));
    }
    return _RETURN_SUCCESS;
}


void change_input          (double                  *input_vector,
                            struct neural_net       *network_addr){
    network_addr->input_vector = input_vector;
}

void network_activate      (struct neural_net       *network) {

}