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

//Essential functions

int max_i(int a,int b)
{
	if (a>=b) return a;
	return b;
}

float max_f(float a, float b)
{
	if (a>=b) return a;
	return b;
}

double max_d(double a, double b)
{
	if (a>=b) return a;
	return b;
}

int min_i(int a,int b)
{
	if (a>=b) return b;
	return a;
}

float min_f(float a, float b)
{
	if (a>=b) return b;
	return a;
}

double min_d(double a, double b)
{
	if (a>=b) return b;
	return a;
}
