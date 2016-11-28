/*
	Copyright (C) 2016 Alexandros Tsonis, Sotiris Papatheodorou

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
//#pragma GCC ivdep
#include "network.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

/*
===========================================================================
Public Function Declarations
===========================================================================
*/

/* Show NeuroticNetwork version and license */
void nn_info() {
	printf("\n\t\tNeuroticNetwork, version %d.%d.%d\n\n", NN_MAJOR_VERSION, NN_MINOR_VERSION, NN_PATCH_VERSION);

	printf("Copyright (C) 2016 Alexandros Tsonis, Sotiris Papatheodorou\n\n");

	printf("This program is free software: you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation, either version 3 of the License, or\n\
(at your option) any later version.\n\
\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n\
GNU General Public License for more details.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with this program. If not, see http://www.gnu.org/licenses/.\n\n");
}

/*Network creation*/
/*NO ERROR CHECKING*/
/*ONLY CHECKS FOR MEMORY ERRORS*/
int create_network               (int               num_of_inputs,
                                  int               num_of_layers,
                                  int               *neurons_per_layer,//make this argument optional
                                  struct neural_net **network_addr){
    //Variable Declaration
    struct neural_net *network;
    neuron *neuron_table_address;
    int neuron_counter, sum_of_neurons = 0, current_layer_neuron = 0, layer_counter = 0, weight_counter, input_pointer;
    unsigned int current_num_of_inputs;
    double *weights_of_neurons;
    int j;

    //Memory allocation of network
    network = malloc(sizeof(struct neural_net));
    if (network == NULL) {//Check if memory was available to allocate
        printf("\n---NOT ENOUGH MEMORY FOR NETWORK CREATION---\n");
        return _CREATION_MEMORY_ERROR;
    }
    network->message            = malloc(50*sizeof(char));
    if (network->message == NULL) {//Check if memory was available to allocate
        printf("\n---NOT ENOUGH MEMORY FOR NETWORK CREATION---\n");
        free(network);//Deallocate any allocated memory
        return _CREATION_MEMORY_ERROR;
    }
    //Set network learning coefficient
    network->learning_coefficient = 0.05;

    //Set network message to null
    network->message            = "\0";

    //Set network specific learning parameters
    network->last_learning_ret  = 0;
    network->learn_change_counter = 0;
    network->learning_counter   = 0;

    //Set network noise margin
    network->noise_margin       = 0.03;

    //Set network's structure
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
		network->learning_coefficient *= sum_of_neurons;
    srand((int)time(NULL));
    //Network Structure Setup
    input_pointer = 0;
    layer_counter = 0;

    //Setup each neuron parameters, inputs and weights
    for (neuron_counter = num_of_inputs; neuron_counter < sum_of_neurons; neuron_counter++) {
        current_layer_neuron += 1;
        if (current_layer_neuron > neurons_per_layer[layer_counter]) {//Layer change
            layer_counter += 1;
            current_layer_neuron = 1;
            input_pointer = neuron_counter - neurons_per_layer[layer_counter-1]-1;
        }

        //Initialize the created neuron
        neuron_init(&(network->neuron_table[neuron_counter]));

        //If the neuron is at the input layer, define its inputs to be the input vector
        if (layer_counter == 0)
        {
            for (j = 0; j < network->num_of_inputs; j++){
                add_input(&(network->neuron_table[neuron_counter]), &(network->neuron_table[input_pointer + j]));
            }
        }

        //Else define its input to be the output of the previous layer
        else
        {
            for (j = 0; j < neurons_per_layer[layer_counter - 1]; j++){
                add_input(&(network->neuron_table[neuron_counter]), &(network->neuron_table[input_pointer + j]));
            }
        }

        //Get the number of inputs and define the weights
        current_num_of_inputs = network->neuron_table[neuron_counter].num_inputs;
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
        //Randomize and normalize initial weights
        for (weight_counter = 0; weight_counter < current_num_of_inputs; weight_counter++) {
            weights_of_neurons[weight_counter] = (double)rand() / (double)RAND_MAX;
        }

        network->neuron_table[neuron_counter].weights = weights_of_neurons;
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
        //printf("%lf", intended_output[intended_output_index]);
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
        maxim = max_i(maxim, network->neurons_per_layer[temporary_iterator]);
    }
    maxim = max_i(maxim, network->num_of_inputs);
    deltaweights = malloc(maxim*sizeof(double));
    for (neuron_counter = network->num_of_inputs; neuron_counter < network->sum_of_neurons; neuron_counter++) {
        for (temporary_neuron_counter = 0; temporary_neuron_counter < network->neuron_table[neuron_counter].num_inputs; temporary_neuron_counter++) {
            check = fabs(network->neuron_table[neuron_counter].weights[temporary_neuron_counter]);
            if (check == check){
                deltaweights[temporary_neuron_counter] = (-1.0)*(network->learning_coefficient)* delta[neuron_counter] * (network->neuron_table[neuron_counter].inputs[temporary_neuron_counter]->output);
            }
            else {
                deltaweights[temporary_neuron_counter] = 0;
            }
        }
        neuron_deltaw(&(network->neuron_table[neuron_counter]), deltaweights);
    }
    network->learn_change_counter++;
    free(deltaweights);
    free(delta);
    //checkStagnated(network);
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
    for (neuron_counter = network->num_of_inputs; neuron_counter < network->sum_of_neurons; neuron_counter++) {
        for (inner_neuron_counter = 0; inner_neuron_counter < network->neuron_table[neuron_counter].num_inputs; inner_neuron_counter++) {
            printf("neuron: %d, weight:%d = %lf\n", neuron_counter, inner_neuron_counter, network->neuron_table[neuron_counter].weights[inner_neuron_counter]);
        }
    }
}

void network_learn           (struct neural_net       *network,
                              double                  *input,
                              double                  *intended_output,
                              int                     number_of_iterations){
    int iteration_counter;
    for (iteration_counter = 0; iteration_counter < number_of_iterations; iteration_counter++) {
        change_input(&(input[iteration_counter*network->num_of_inputs]), network);
        network_activate(network);
        errorback(network, &(intended_output[iteration_counter*(network->neurons_per_layer[network->num_of_layers - 1])]));
    }
    network->learning_counter++;
    if (network->learning_counter == 10000) {
        network->learning_counter = 0;
        network_set_message(network,1000);
        network_print(network);
    }
}

int network_test              (struct neural_net      *network,
                               double                 *test_input,
                               double                 *intended_output,
                               int                    number_of_tests){
    int iteration_counter,neuron_counter,output_counter,return_value=EXIT_SUCCESS;
    for (iteration_counter = 0; iteration_counter < number_of_tests; iteration_counter++) {
        change_input(&(test_input[iteration_counter*network->num_of_inputs]), network);
        network_activate(network);
        output_counter = 1;
        for (neuron_counter = network->sum_of_neurons - 1; neuron_counter > ((network->sum_of_neurons - 1) - (network->neurons_per_layer[network->num_of_layers - 1])); neuron_counter--) {
            if (fabs(network->neuron_table[neuron_counter].output - intended_output[(iteration_counter+1)*network->neurons_per_layer[network->num_of_layers - 1] - output_counter])>network->noise_margin) {
                return_value += 1;
            }
                output_counter++;
        }
    }
    //adapt_learning_coeff(network, return_value);
    network->last_learning_ret = return_value;
    return return_value;
}


void network_set_message(struct neural_net *network, int message) {
    if (message == 1000) {
        network->message = "Still Learning\n";
    }
}

void network_print(struct neural_net *network) {
    printf("%s",network->message);//To be changed probably
    network->message = "\0";
}

void network_print_whole_out(struct neural_net *network) {
    int neuron_counter;
    printf("\tPRINTING OUTPUT\n");
    for (neuron_counter = network->num_of_inputs; neuron_counter < network->sum_of_neurons; neuron_counter++) {
        printf("Neuron %d output is: %lf\n", neuron_counter- network->num_of_inputs, network->neuron_table[neuron_counter].output);
    }
}

void network_print_output_only(struct neural_net *network) {
    int neuron_counter,output_neuron=1;
    for (neuron_counter = network->sum_of_neurons - (network->neurons_per_layer[network->num_of_layers - 1]); neuron_counter < network->sum_of_neurons; neuron_counter++) {
        printf("Output of the %d output neuron is :%lf\n", output_neuron, network->neuron_table[neuron_counter].output);
        output_neuron++;
    }
}

void network_change_learning_coeff(struct neural_net *network, double new_learning_coefficient) {
    network->learning_coefficient = new_learning_coefficient;
}

void adapt_learning_coeff       (struct neural_net *network,
                                 int current_ret) {
    if (network->last_learning_ret == 0) {
        network->learn_change_counter = 0;
        network->learning_coefficient = 0.2;
    }
    else {
        if (network->last_learning_ret == current_ret) {
            network->learn_change_counter += 1;
        }
        else {
            if (network->last_learning_ret > current_ret) {
                network->learn_change_counter = 0;
                network->learning_coefficient = 0.1;
            }
            else {
                network->learn_change_counter += 100;
            }
        }
        if (network->learn_change_counter > 50000) {
            network->learning_coefficient *= 1.01;
            network->learn_change_counter = 0;
        }
    }
}

void checkStagnated         (struct neural_net * network){
  if (network->learn_change_counter > 50000000) {
    int i,j;
    bool weightStagnated=true,outStagnated=true;
    double randomizer,factor;
    for (i=network->num_of_inputs; i<network->sum_of_neurons;i++)
    {
      weightStagnated &= network->neuron_table[i].stagnatedWeights;
      outStagnated &= network->neuron_table[i].stagnatedOutput;
    }
    network->Stagnated=weightStagnated;//|outStagnated;
    if (network->Stagnated==true){
      //printf("\n stagnated \n")
      for (i=network->num_of_inputs; i<network->sum_of_neurons; i++)
      {
        for (j=0; j<network->neuron_table[i].num_inputs;j++)
        {
          factor = network->neuron_table[i].weights[j]/(1000.0*RAND_MAX);
          randomizer=rand()*factor;
          network->neuron_table[i].weights[j] += (rand()>(RAND_MAX/2)) ? (-randomizer) : (randomizer);
        }
      }
    }
    network->learn_change_counter = 0;
  }
}

//Create logging files
void startLogging (struct neural_net *network)
{
	char originalpath[90], filename[100];
	bool RIGHT_PATH;
	volatile int internalcounter=0;
	volatile int layercounter=1;
	volatile int i;
	//Logging starts here
	RIGHT_PATH=false;
	network->NW = malloc((network->sum_of_neurons-network->num_of_inputs)*sizeof(FILE*));
	while (RIGHT_PATH==false){
		printf("\n Type the destination path of the logs: ");
		fgets (originalpath, 90, stdin);//Read file input
		RIGHT_PATH=true;//Assume path given is correct (Will be checked later)
		if ((strlen(originalpath)>0) && (originalpath[strlen(originalpath)-1]=='\n')){
			originalpath[strlen(originalpath)-1]='\0';
			for (i=0;i<network->sum_of_neurons-network->num_of_inputs;i++)
			{
				internalcounter+=1;
				if (internalcounter-1==network->neurons_per_layer[layercounter-1]){
					layercounter+=1;
					internalcounter=1;
				}
				//Append the necessary characters to the path and open the files
				sprintf(filename,"%s",originalpath);
				if (!((filename[strlen(filename)-2]=='\\') || (filename[strlen(filename)-2]=='/')))
					sprintf(filename,"%s%c",filename,'/');
				sprintf(filename,"%s%s%d%s%d%s",filename,"nw_",layercounter,"_",internalcounter,".txt");
				network->NW[i]=fopen(filename,"w");

				//Check if files can be created in the given file path
				if (network->NW[i]==NULL)
				{
					RIGHT_PATH=false;
					printf("WRONG FILE PATH NAME\n");
					break;
				}
			}
		}

	}
	//Format log files
	for (int i=network->num_of_inputs;i<network->sum_of_neurons;i++)
	{
		for (int j=0;j<network->neuron_table[i].num_inputs;j++){
			fprintf(network->NW[i-network->num_of_inputs],"%d ",network->neuron_table[i].num_inputs);
		}
		fprintf(network->NW[i-network->num_of_inputs],"\n");
	}
}

//Log current weights
void networkLogging               (struct neural_net *network)
{
	for (int i=network->num_of_inputs;i<network->sum_of_neurons;i++)
	{
		for (int j=0;j<network->neuron_table[i].num_inputs;j++){
			fprintf(network->NW[i-network->num_of_inputs],"%lf ",network->neuron_table[i].weights[j]);
		}
		fprintf(network->NW[i-network->num_of_inputs],"\n");
	}
}

//Close logging files and flush buffer
void stopLogging                  (struct neural_net *network)
{
	for (int i=0;i<network->sum_of_neurons-network->num_of_inputs;i++)
	{
		fclose(network->NW[i]);
	}
}
