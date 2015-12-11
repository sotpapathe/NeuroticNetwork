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

typedef struct{                                 //Network Struct
        int          num_inputs;                //Number of inputs of structure
        neuron       *neuron_table;             //Table of network interconnects (2 dimensional)
} neural_net;

/*
===========================================================================
                       Public Function Prototypes
===========================================================================
*/

/* Calculate the output of network */
/* Calculation from the input layers to the output serially */
/* NO ERROR CHECKING*/
void network_activate      (neural_net       *network);

/* Set the weight of an individual neuron */
/* NO ERROR CHECKING */
void network_delta         (neural_net       *network,
                            int              layer_pointer,
                            int              neuron_pointer,
                            double           *deltaw);


#endif

