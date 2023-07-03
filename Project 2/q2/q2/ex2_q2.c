// Course: Advanced C programming
// exercise 2, question 2
// file name: ex2_q2.c

// --------------------------- //
//
//    Assigned by:
//		Leon Yurkovski #314972357 
//		Koren Abugov #211480157
//
// --------------------------- //

// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define ROWS 4
#define COLS 5
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct four
{
	int i, j, d, value;
} four;

typedef struct list
{
	four data;
	struct list* next;
} list;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
int createArrayAndList(int A[][COLS], list** lst, four** arr, int rows, int cols);
four createFour(int i, int j, int d, int value);
list* createElement(four data);
void printArray(four* arr, int n);
void printList(list* lst);
void freeDynamic(list** lst, four** arr);

// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	unsigned long id_num;
	int n;
	list* lst = NULL;
	four* arr = NULL;
	int A[ROWS][COLS] = {
		{0, 6, 5, 6, 6},
		{8, 9, 5, 6, 7},
		{7, 6, 5, 4, 7},
		{9, 8, 1, 6, 7},
	};

	// Start Program:
	printf("Start Program\n");

	// call functions:
	n = createArrayAndList(A, &lst, &arr, ROWS, COLS);

	// write output:
	printf("Output:\n");
	printArray(arr, n);
	printList(lst);

	// free dynamic:
	freeDynamic(&lst, &arr);

	return 0;
}
// --------------------------- //

/// <summary>
/// This function allocate a dynamic array and list, 
/// from elements found at matrix A 
/// </summary>
/// <param>int A[][] - The static matrix</param>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <param>four** arr - Pointer to the pointer of the head of the array</param>
/// <param>int rows - The number of rows in the matrix</param>
/// <param>int cols - The number of colums in the matrix</param>
/// <returns>Number of requested elements in found in A</returns>
int createArrayAndList(int A[][COLS], list** lst, four** arr, int rows, int cols)
{
	// your code:

	int count = 0, diff, i, j;
	four temp;
	*arr = (four*)calloc(rows * cols, sizeof(four));
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			diff = abs(i - j);
			if (A[i][j] == j + diff || A[i][j] == j - diff) {
				if ((i - j) > 0) {
					temp = createFour(i, j, -diff, A[i][j]);
				}
				else {
					temp = createFour(i, j, diff, A[i][j]);
				}
				(*arr)[count] = temp;
				count++;
				list* new_node = createElement(temp);
				if (*lst == NULL) {
					*lst = new_node;
				}
				else {
					list* current = *lst;
					while (current->next != NULL) {
						current = current->next;
					}
					current->next = new_node;
				}
			}
		}
	}
	*arr = (four*)realloc(*arr, count * sizeof(four));
	return count;
}
// --------------------------- //

/// <summary>
/// The function receives 4 integer values 
/// and returns a value from type four.
/// </summary>
/// <param>int i - The cell row number in matrix</param>
/// <param>int j - The cell colum number in the matrix</param>
/// <param>int d - The difference between the consecutive values</param>
/// <param>int value - The value at position [i,j] in matrix</param>
/// <returns>value from type four</returns>
four createFour(int i, int j, int d, int value)
{
	// your code:

	four temp;
	temp.i = i;
	temp.j = j;
	temp.d = d;
	temp.value = value;
	return temp;
}
// --------------------------- //

/// <summary>
/// The function receives a value from type four
/// and returns a dynamic element from type list  
/// </summary>
/// <param>four data - value from type four</param>
/// <returns>dynamic value from type list</returns>
list* createElement(four data)
{
	// your code:

	list* temp = (list*)calloc(1, sizeof(list));
	temp->data = data;
	temp->next = NULL;
	return temp;
}
// --------------------------- //


/// <summary>
/// The function receives an array from type four,
/// and print its values.  
/// </summary>
/// <param>four* arr - the array</param>
/// <param>int n - number of elements</param>
/// <returns>None</returns>
void printArray(four* arr, int n)
{
	// your code:

	printf("Printing Array\n");
	int i, j;
	for (i = 0; i < n; i++)
	{
		printf("%d, ", arr[i].value);
	}
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%d, ", arr[i].i);
	}
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%d, ", arr[i].j);
	}
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%d, ", arr[i].d);
	}
	printf("\n");
}
// --------------------------- //


/// <summary>
/// The function receives a list,
/// and print its values.  
/// </summary>
/// <param>list* lst - the list</param>
/// <returns>None</returns>
void printList(list* lst)
{
	// your code:

	printf("Printing List\n");
	while (lst != NULL)
	{
		printf("%d,%d,%d,%d\n", lst->data.value, lst->data.i, lst->data.j, lst->data.d);
		lst = lst->next;
	}
}
// --------------------------- //

/// <summary>
/// The function free all allocated memory of the program. 
/// </summary>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <param>four** arr - Pointer to the pointer of the head of the array</param>
/// <returns>None</returns>
void freeDynamic(list** lst, four** arr)
{
	// your code:
	list* current = *lst;
	while (current != NULL) {
		list* next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL; // Set the head of the list to NULL

	// Free the array
	free(*arr);
	*arr = NULL; // Set the head of the array to NULL
}
// --------------------------- //