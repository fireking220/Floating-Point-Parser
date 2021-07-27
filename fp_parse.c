//Scott Patterson
//5/13/17
//Assignment 3
//Mark Morresy
//This program takes a number of fraction bits, exponent bits, and a hex value from the user. It then converts this hex value based on the number of bits given into a floating point number. If the number happens to be +/- infinity or NaN (Not a number), the program will tell the user and exit without any calculation.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char * argv[])
{
	int n = 0, k = 0;
	int hexValue = 0;
	float fractionValue = 0;
	int exponentValue = 0;
	int exponent = 0;
	int signValue = 0;
	int bias = 0;
	int maxExpValue = 0;
	float finalValue = 0;
	float mantissa = 0;
	
	//check to see if 3 arguments were entered
	if(argc != 4)
	{
		printf("Usage; fp_parse <# of frac_bits> < # of exp_bits> <hex_to_convert>\n");
		exit(0);
	}

	//convert fractional/exponent bits to numbers
	n = atoi(argv[1]);
	k = atoi(argv[2]);

	//check to see if arguments are in the correct bounds
	if(n < 2 || n > 10)
	{
		printf("Illegal number of fraction bits(%d). Should be between 2 and 10\n", n);
		exit(0);
	}
	else if(k < 3 || k > 5)
	{
		printf("Illegal number of exponent bits(%d). Should be between 3 and 5\n", k);
		exit(0);
	}

	//get the hex value from our string
	hexValue = (int)strtol(argv[3], NULL, 16);
	bias = pow(2, k - 1) - 1;
	maxExpValue = pow(2, k) - 1;
	
	//fractional value from our hex value
	for(int i = n;i > 0;--i)
	{
		if(hexValue & 1 == 1)
		{
			fractionValue += powf(2, -1 * i);
		}
		hexValue = hexValue >> 1;
	}

	//exponent value from our hex value
	for(int i = 0;i < k;++i)
	{
		if(hexValue & 1 == 1)
		{
			exponentValue += pow(2, i);
		}
		hexValue = hexValue >> 1;
	}

	//sign value from our hex value
	if(hexValue & 1 == 1)
	{
		signValue = 1;
	}

	//check to see if normalized, denormalized, +inf, -inf, or NaN
	if(exponentValue == maxExpValue)
	{
		//NaN
		if(fractionValue > 0)
		{
			printf("NaN\n");
		}
		//+inf
		else if(signValue == 0)
		{
			printf("+inf\n");
		}
		//-inf
		else
		{
			printf("-inf\n");
		}
		exit(0);
	}
	//normalized
	else if(exponentValue > 0 && exponentValue < maxExpValue)
	{
		exponent = exponentValue - bias;
		mantissa = 1 + fractionValue;
	}
	//denormalized
	else
	{
		exponent = 1 - bias;
		mantissa = fractionValue;
	}

	printf("%f\n", pow(-1, signValue) * mantissa * pow(2, exponent));

	exit(0);
}
