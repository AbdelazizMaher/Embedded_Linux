#include <stdio.h>

#include "../Inc/addition.h"
#include "../Inc/subtraction.h"
#include "../Inc/multiplication.h"
#include "../Inc/division.h"
#include "../Inc/modulus.h"


int main()
{
	double Val1 = 11;
	double Val2 = 13.4;
	printf("\n===================Simple Calculator================");
	printf("Val1 + Val2 = %f\n", Add(Val1 ,Val2));
	printf("Val1 - Val2 = %f\n", Subtract(Val1 ,Val2));
	printf("Val1 * Val2 = %f\n", Multiply(Val1 ,Val2));
	printf("Val1 / Val2 = %f\n", Divide(Val1 ,Val2));
	printf("Val1 MOD Val2 = %f\n", Remainder(Val1 ,Val2)); 
	printf("====================================================\n");	
	
	return 0;
}

