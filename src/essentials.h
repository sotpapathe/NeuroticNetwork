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

//Essentials
#ifndef __essentials_h
#define __essentials_h

//Define a character variable with the name boolean
typedef enum {false,true} bool;

int max_i(int a,int b);

float max_f(float a, float b);

double max_d(double a, double b);

int min_i(int a,int b);

float min_f(float a, float b);

double min_d(double a, double b);

#endif
