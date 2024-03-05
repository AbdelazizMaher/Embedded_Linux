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
	printf("\n===================Simple Calculator================\n");
	printf("%d + %d = %f\n", Val1, Val2 ,Add(Val1 ,Val2));
	printf("%d - %d = %f\n",  Val1, Val2 ,Subtract(Val1 ,Val2));
	printf("%d * %d = %f\n",  Val1, Val2 ,Multiply(Val1 ,Val2));
	printf("%d / %d = %f\n",  Val1, Val2 ,Divide(Val1 ,Val2));
	printf("%d MOD %d = %f\n",  Val1, Val2 ,Remainder(Val1 ,Val2)); 
	printf("====================================================\n");	
	
	return 0;
}

