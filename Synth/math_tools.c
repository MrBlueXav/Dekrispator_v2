/**
 ******************************************************************************
 * File Name          	: math_tools.c
 * Author				: Xavier Halgand
 * Date               	:
 * Description        	:
 ******************************************************************************
 */
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
*/

#include "math_tools.h"

/*-----------------------------------------------------------------------------------*/
float approx_exp(float x)
{
	float y; // exp(x) = lim n->inf (1 + x/n)^n, here we've choosen n = 16
	y = 1.f + x/16.f ;
	y *= y;
	y *= y;
	y *= y;
	y *= y;
	return y ;
}
//------------------------------------------------------------------------------------
// input val in 0 ... 127
// output is an exponential between min and max
float	Lin2Exp(uint8_t val, float min, float max)
{
	return min * powf(max / min, val / MIDI_MAX);
}
//------------------------------------------------------------------------------------

float tanhXdX(float x)
{
	float a = x*x;
	// IIRC I got this as Pade-approx for tanh(sqrt(x))/sqrt(x)
	x = ((a + 105)*a + 945) / ((15*a + 420)*a + 945);
	return x;
}

//------------------------------------------------------------------------------------
float fastTanh(float var)
{
	if(var < -1.95f)     return -1.0f;
	else if(var > 1.95f) return  1.0f;
	else return  4.15f*var/(4.29f+var*var);
}
//------------------------------------------------------------------------------------
float 	softClipTwo(float in)
{
	return in * tanhXdX(0.5*in);
}
//------------------------------------------------------------------------------------
float 	fastTan(float x)
{
	float A = -15*x+x*x*x;
	float B = 3*(-5+2*x*x);
	return A/B;
}
