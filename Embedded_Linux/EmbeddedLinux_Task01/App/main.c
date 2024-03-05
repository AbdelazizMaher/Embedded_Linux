#include <stdio.h>

#include "../Inc/addition.h"
#include "../Inc/subtraction.h"
#include "../Inc/multiplication.h"
#include "../Inc/division.h"
#include "../Inc/modulus.h"


int main()
{

	double In1 , In2;
	char Operation;

	printf("Enter one of the following operation( + , - , * , / , %% ): ");
	Operation = getchar();	
		
	printf("Enter the first argument: ");
	scanf("%lf",&In1);
	
	printf("Enter the second argument: ");
	scanf("%lf",&In2);
		
	switch(Operation)
	{
	case '+':
		printf("%f + %f = %f\n", In1, In2 ,Add(In1 ,In2));
		break;
	case '-':
		printf("%f - %f = %f\n", In1, In2 ,Subtract(In1 ,In2));
		break;
	case '*':
		printf("%f * %f = %f\n", In1, In2 ,Multiply(In1 ,In2));
		break;
	case '/':
		printf("%f / %f = %f\n", In1, In2 ,Divide(In1 ,In2));
		break;
	case '%':
		printf("%f %% %f = %f\n", In1, In2 ,Remainder(In1 ,In2));
		break;
	default:
		printf("wrong operation\n");									
	}
	
	/*double Val1 = 11;
	double Val2 = 13.4;
	printf("\n===================Simple Calculator================\n");
	printf("%f + %f = %f\n", Val1, Val2 ,Add(Val1 ,Val2));
	printf("%f - %f = %f\n",  Val1, Val2 ,Subtract(Val1 ,Val2));
	printf("%f * %f = %f\n",  Val1, Val2 ,Multiply(Val1 ,Val2));
	printf("%f / %f = %f\n",  Val1, Val2 ,Divide(Val1 ,Val2));
	printf("%f %% %f = %f\n",  Val1, Val2 ,Remainder(Val1 ,Val2)); 
	printf("====================================================\n");*/	
	
	return 0;
}

