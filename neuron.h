#ifndef __neuron_h
#define __neuron_h


/*
===========================================================================
                           Public Data Types
===========================================================================
*/

typedef struct						/* Neuron structure */
{
	int				num_inputs;		/* The number of inputs of the neuron */
	neuron			*inputs;		/* Pointers to the input neurons */
	double			*weights;		/* The weights of the inputs */
	double			output;			/* The output of the neuron */
} neuron;


/*
===========================================================================
                       Public Function Prototypes
===========================================================================
*/

/* Add the values of the deltaw array to the weights of the target neuron */
/* NO ERROR CHECKING */
void neuron_deltaw		(neuron		*target,
						 double		*deltaw);

/* Set the weights of the target neuron to the values of the deltaw array */
/* NO ERROR CHECKING */
void neuron_setw		(neuron		*target,
						 double		*deltaw);

/* Calculate the output of the neuron */
/* NO ERROR CHECKING */
void neuron_activate	(neuron		*target);


/* Free the memory used by the target neuron */
/* NO ERROR CHECKING */
void neuron_free	(neuron		*target);


/* Initialize the target neuron to zeros and NULL pointers */
/* NO ERROR CHECKING */
void neuron_init	(neuron		*target);
#endif
