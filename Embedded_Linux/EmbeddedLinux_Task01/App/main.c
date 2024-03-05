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
	
	printf("Val1 + Val2 = %d", Add(Val1 ,Val2));
	printf("Val1 - Val2 = %d", Subtract(Val1 ,Val2));
	printf("Val1 * Val2 = %d", Multiply(Val1 ,Val2));
	printf("Val1 / Val2 = %d", Divide(Val1 ,Val2));
	printf("Val1 % Val2 = %d", Remainder(Val1 ,Val2)); 
	return 0;
}

