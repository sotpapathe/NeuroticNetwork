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

#ifndef _network_h
#define _network_h
#define _RETURN_SUCCESS 1
#define _CREATION_MEMORY_ERROR 2
#include <stdlib.h>
#include <stdio.h>

#include "neuron.h"


/*
===========================================================================
                           Still a prototype
                           Subject to change
===========================================================================
*/

/*
===========================================================================
                           Public Data Types
===========================================================================
*/

struct neural_net{                                 //Network Struct
        double              noise_margin;              //Noise margin of outputs, can be set at any number, default is 0.08
        char                *message;                  //Pointer to message
        double              learning_coefficient;      //Error back propagation learning coefficient
        int                 last_learning_ret;
        int                 learn_change_counter;
        int                 learning_counter;          //Learning iteration counter to prevent false freezing
        int                 num_of_inputs;             //Number of inputs of structure
        int                 num_of_layers;             //Number of layers in the neural network
        int                 sum_of_neurons;            //Sum of neurons in network (Inputs are treated as neurons)
        int                 *neurons_per_layer;        //Table of neurons per layer
        bool                Stagnated;                 //True if the network has stagnated
        neuron              *neuron_table;             //Table of network interconnects (1 dimensional)
};

/*
===========================================================================
                       Public Function Prototypes
===========================================================================
*/
/*Create a network*/
/*Returns address of neural_net struct*/
/*TO-DO: MAKE THIS VARADIC*/
/*NO ERROR CHECKING*/
int create_network                 (int                     num_of_inputs,
                                    int                     num_of_layers,
                                    int                     *neurons_per_layer,//make this argument optional
                                    struct neural_net       **network_addr);

/*Change the input vector of the network*/
/*NO ERROR CHECKING*/
void change_input                  (double                  *input_vector,
                                    struct neural_net       *network_addr);

/* Calculate the output of network */
/* Calculation from the input layers to the output serially */
/* NO ERROR CHECKING*/
void network_activate              (struct neural_net       *network);

/* Add the values of the deltaw array to the weight array of a single neuron */
/* NO ERROR CHECKING */
void network_delta                 (struct neural_net       *network,
                                    int                     layer_pointer,
                                    int                     neuron_pointer,
                                    double                  *deltaw);

/* Set the weights of a neuron in the network equal to the deltaw array */
/* NO ERROR CHECKING */
void network_setw                  (struct neural_net       *network,
                                    int                     layer_pointer,
                                    int                     neuron_pointer,
                                    double                  *deltaw);

/* Delete the network */
/* NO ERROR CHECKING */
void network_delete                (struct neural_net       *network);


/*Error back propagation*/
/*NO ERROR CHECKING*/
void errorback                     (struct neural_net       *network,
                                    double                  *intended_output);


//Normalizes the weights of the neurons
void normalize_weights             (struct neural_net       *network);


//Prints the weights of all the neurons in the network
void print_weights                 (struct neural_net       *network);


//Given a set of inputs and the intended outputs for these given inputs,
//modifies the weights of the system so that the output approaches the
//intended output
void network_learn                 (struct neural_net       *network,
                                    double                  *input,
                                    double                  *intended_output,
                                    int                     number_of_iterations);

//Given a set of inputs and the intended output for these given inputs,
//checks if the given outputs are within the networks noise margin of the intended outputs.
//Returns how many of the outputs do not satisfy the above condition.
int network_test                   (struct neural_net      *network,
                                    double                 *test_input,
                                    double                 *intended_output,
                                    int                    number_of_tests);

//Sets the message that the next network_print function will display
void network_set_message          (struct neural_net      *network,
                                   int                    message);

//Prints the message that was set and re initializes the networks message to NULL
void network_print                (struct neural_net      *network);

//Prints the outputs of all the neurons
void network_print_whole_out      (struct neural_net      *network);

//Prints the networks output
void network_print_output_only    (struct neural_net      *network);

//Change the learning coefficient ofthe error back propagation method of learning
void network_change_learning_coeff(struct neural_net *network,
                                   double new_learning_coefficient);

//Adapt the learning coefficient so thatconvergence occurs faster. Experimental
void adapt_learning_coeff         (struct neural_net *network,
                                   int               current_ret);
                                   
//Check if the network has reached a local extremum and randomize weights
void checkStagnated               (struct neural_net *network);

#endif
