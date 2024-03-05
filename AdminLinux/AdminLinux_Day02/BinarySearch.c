#include <stdio.h>

int BinarySearch(int ARR[],int ARRsize,int num);

int main()
{
	int ARR[] = {5,13,24,66,104,107};
	int index = -1;
	int ARRsize = sizeof(ARR)/sizeof(int);

        printf("search for: %d\n",24);
	index = BinarySearch(ARR,ARRsize,24);

	( index > -1 ) ? printf("Found at index: %d \n",index) : printf("Value is not Found\n ");

	return 0;
}


int BinarySearch(int ARR[],int ARRsize,int num)
{
	int left = 0 , right = ARRsize - 1 , mid = 0;

	while( left <= right )
	{
		mid = (	 left + right )/2;

		if( ARR[mid] == num)
			return mid;
		else if( ARR[mid] > num )
		       right = mid - 1;
		
		else if( ARR[mid] < num )
		      left = mid + 1;
	}

	return -1;	
}	
