#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
* Computes the sum of elements from an array
* "size" -> the size of the array
* "A" -> pointer to the beginning of the array in the memory
*/
int list_sum(int size, int* A)
{
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += A[i];
	}
	return sum;
}

/*
* The main idea is to build a bitmask which will tell us what elements we will introduce in list B.
* Of course that we won't actually build two separate lists, we'll just calculate the average of them (having the number
* of elements and the sum of them for the list B, it's easy to calculate the average for the second list, C -> that's why
* we calculate in the first line the total sum of the list A)
* The number of all possible solutions (subsets) will be 2^size, and if the size is maximum (30), then it is 2^30
* We will iterate from 1 to (2^size - 2) and for each number we'll search for every 'jth' bit set in him (j: 0 -> size)
* If a bit is set, then the number from that position in the array is selected to go in list B
* The time complexity is -> O(2^size*size). So if the size = 30 => O(2^30*30) = aprox 32.212.254.720; which is not that bad
*/
bool check_possible_move(int size, int* A)
{
	int total_sum = list_sum(size, A);
	int limit_power = pow(2, size); //our bitmask up limit
	/* 
	* i is the bitmask
	* i starts from 1 and goes only to (pow(2,size) - 2) because this number doesn't have all bits set to 1
	* (while the number (pow(2,size)-1) does have), and by doing this, we are sure that each list (B or C) has at least one
	* element
	*/
	for (int i = 1; i < (limit_power - 1); i++)
	{
		int list_B_sum = 0; //holds the sum of elements in list B
		int list_B_len = 0; //holds the lenght of list B
		for (int j = 0; j < size; j++)
		{
			//first, we have to check if the jth bit is set in number 'i'
			if (i & (1 << j)) {
				list_B_sum += A[j];
				list_B_len ++;
			}
		}
		double list_B_average = (double)list_B_sum / list_B_len;
		double list_C_average = (double)(total_sum - list_B_sum) / (size - list_B_len);
		if (fabs(list_B_average - list_C_average) < 1e-4) { //here we test if the two arrays (B and C) have equal averages
			return true;
		}
	}
	return false;
}

int main()
{
	/*
	* I tried to keep the variables names as they were called in the problem.
	* I will read from the console the size of the input array and then the elements of the array
	*/
	int size_A;
	printf("Introduce the lenght of the array [1-30]: ");
	scanf_s("%d", &size_A, sizeof(int));
	int* A = (int*)malloc(size_A * sizeof(int*));
	printf("Introduce the elements (separated by a single space, no commas) [0-10000]: ");
	for (int i = 0; i < size_A; i++) {
		scanf_s("%d", &A[i], sizeof(int));
	}

	if(size_A < 2) //if size_A == 1, then we clearly can't form the two lists (B and C)
		printf("False\n");

	bool result = check_possible_move(size_A, A);
	if (result == true) {
		printf("True\n");
	}
	else {
		printf("False\n");
	}

	free(A);
	return 0;
}