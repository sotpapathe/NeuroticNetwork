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

#include <math.h>
#include <stdlib.h>

#include "neuron.h"

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
		/* Replace last weights */
		target->lastWeights[i] = target->weights[i];
		/* Add the delta value to each weight */
		target->weights[i] = target->weights[i] + deltaw[i];
	}
	isStagnated(target);
}





void neuron_setw		(neuron		*target,
						 double		*deltaw)
{
	int i;

	/* Loop over all weights of target neuron */
	for (i=0; i<target->num_inputs; i++)
	{
		/* Replace last weights */
		target->lastWeights[i] = target->weights[i];
		/* Set the value of each weight */
		target->weights[i] = deltaw[i];
	}
	isStagnated(target);
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
		x = x + target->weights[i] * target->inputs[i]->output;
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
	target->lastWeights = NULL;
	target->inputs = NULL;

	/* FALSE */
	target->stagnatedWeights=false;
	target->stagnatedOutput=false;
}

void add_input(neuron *source, neuron *target)
{
  source->num_inputs++;
  source->inputs = realloc(source->inputs, source->num_inputs*sizeof(struct neuron_t *));
	source->weights = realloc(source->weights, source->num_inputs*sizeof(double));
	source->lastWeights = realloc(source->lastWeights, source->num_inputs*sizeof(double));
  source->inputs[source->num_inputs - 1] = target;
	source->weights[source->num_inputs - 1] = 0.5;
	source->lastWeights[source->num_inputs - 1] = 0.5;
}

void remove_input(neuron *source, int num)
{
    int i,j=0;
    struct neuron_t **temp;
	double *tempw,*templw;
    temp = malloc((source->num_inputs-1)*sizeof(struct neuron_t *));
	tempw = malloc((source->num_inputs-1)*sizeof(double));
	templw = malloc((source->num_inputs-1)*sizeof(double));
    for (i = 0; i < source->num_inputs; i++)
    {
        if (i == num) continue;
        temp[j] = source->inputs[i];
		tempw[j] = source->weights[i];
		templw[j] = source->lastWeights[i];
        j++;
    }
    free(source->inputs);
	free(source->weights);
	free(source->lastWeights);
    source->inputs = temp;
}

void isStagnated(neuron *neuron)
{
	int i;
	bool check = true;
	for (i=0; i < neuron->num_inputs; i++)
	{
		if (fabs(neuron->lastWeights[i]-neuron->weights[i]) > 0.0000001)
		{
			check = false;
		}
	}
	neuron->stagnatedWeights = check;
	check = true;
	if (fabs(neuron->lastOutput - neuron->output) > 0.000001)
	{
		check = false;
	}
	neuron->stagnatedOutput = check;
}
