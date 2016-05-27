# NeuroticNetwork
Neural network simulator by Alexandros Tsonis and Sotiris Papatheodorou

Contents:

1-------------Neuron architecture

2-------------Neuron functions

3-------------Network architecture

4-------------Network methods


1:Neuron architecture

Neurons consist of one integer variable that shows the number of the inputs of the neuron, one array of neuron pointers that point to the neurons that are treated as inputs to the current neuron which is always the size of the number of inputs, one array of double numbers that are the weights of the inputs of the current neuron and one double variable which is the output of the neuron.

2:Neuron functions

Neurons have the following functions:

1-------------neuron_init	(neuron		*target)

This function takes a pointer to a neuron as an argument and initializes the neuron pointed by the pointer to 0 (i.e number of inputs becomes 0, output becomes 0 and the arrays are initialized to NULL).

2-------------neuron_free	(neuron		*target)

This function takes a pointer to a neuron as an argument and frees the memory that this neuron takes up.

3-------------neuron_setw		(neuron		*target, double		*deltaw)

This function takes a pointer to a neuron and an array of double numbers as arguments and sets the weights of the neuron to the value of the input array. The size of the input array  must be equal to the number of the inputs of the neuron. If this is not the case, then if the input array is bigger in size, the elements past the index of the number of inputs of the target neuron are ignored. If the array is smaller in size, then access violation occurs.

4-------------neuron_deltaw		(neuron		*target, double		*deltaw)

This function takes a pointer to a neuron and an array of double numbers as arguments and adds element-wise the numbers in the input array to the weights of the target neuron. The size of the input array  must be equal to the number of the inputs of the neuron. If this is not the case, then if the input array is bigger in size, the elements past the index of the number of inputs of the target neuron are ignored. If the array is smaller in size, then access violation occurs.

5-------------neuron_activate	(neuron		*target)

This function takes a pointer to a neuron as an argument and calculates its output based on the input array and the weights of each input and sets the neurons output as that value. The output is calculated by the logistic function with a steepness of 1. If the array of the weights is not set up properly, i.e. its size is smaller than the number of inputs of the neuron, then the function will raise an access violation error.

6-------------add_input      (neuron *source, neuron *target)

This function takes two pointers to neurons as arguments and adds the address of the target neuron to the array of input neurons of the source neuron. The previous inputs of the source neuron are retained and the new neuron is appended to the end of the input array. The number of inputs of the source neuron is increased by 1 as well.

7-------------remove_input(neuron *source, int num)

This function takes a pointer to a neuron and an integer number as arguments and removes the neuron that is in the num index of the input list of the source neuron. The other inputs of the source neuron are retained. The number of inputs is decreased by 1 as well. If num is greater than the number of the inputs of the  neuron, then an access violation error is raised.
