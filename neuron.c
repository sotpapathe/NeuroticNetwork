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

#include "neuron.h"
#include <math.h>
#include <stdlib.h>

/*
===========================================================================
                       Public Function Declarations
===========================================================================
*/

void neuron_deltaw		(neuron		*target,
						 double		*deltaw)
{
	int i;
	
	/* Loop over all weights of target neuron */
	for (i=0; i<target->num_inputs; i++)
	{
		/* Add the delta value to each weight */
		target->weights[i] = target->weights[i] + deltaw[i];
	}
}





void neuron_setw		(neuron		*target,
						 double		*deltaw)
{
	int i;
	
	/* Loop over all weights of target neuron */
	for (i=0; i<target->num_inputs; i++)
	{
		/* Set the value of each weight */
		target->weights[i] = deltaw[i];
	}
}





void neuron_activate	(neuron		*target)
{
	int i;
	double x = 0;
	/* Summation in a separate variable instead of the output
	* allows for feedback on the neuron */
	
	/* Loop over all inputs of target neuron */
	for (i=0; i<target->num_inputs; i++)
	{
		x = x + target->weights[i] * target->inputs[i].output;
	}
	
	/* Non-linear function */
	target->output = 1 / ( 1 + exp(-x) );
}





void neuron_free	(neuron		*target)
{
	/* Zero */
	target->num_inputs = 0;
	target->output = 0;
	
	/* Free weight array */
	free( target->weights );
	target->weights = NULL;
	
	/* Do NOT free input array, it contains pointers to other neurons */
	target->inputs = NULL;
}





void neuron_init	(neuron		*target)
{
	/* Zero */
	target->num_inputs = 0;
	target->output = 0;
	
	/* NULL */
	target->weights = NULL;
	target->inputs = NULL;
}
