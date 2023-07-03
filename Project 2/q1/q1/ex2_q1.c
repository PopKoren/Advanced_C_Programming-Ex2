// Course: Advanced C programming
// exercise 2, question 1
// file name: ex2_q1.c

// --------------------------- //
//
//	Assigned by:
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
#define COLS 4
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct fraction
{
	int num, numerator, denominator;
} fraction;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //

fraction** createMatrix(int rows, int cols);
fraction** matrixAverageNeighbor(int A[][COLS], int rows, int cols);
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols);
void printMatrix(fraction** B, int rows, int cols);
void freeMatrix(fraction** B, int rows);
fraction reduce_fraction(int , int );

// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	fraction** B;
	int A[ROWS][COLS] = {
		{5, 12, 6, 8},
		{4, 7, 0, 9},
		{13, 20, 8, 2},
		{18, 0, 2, 6}
	};

	// Start Program:
	printf("Start Program\n");

	// call functions:
	B = matrixAverageNeighbor(A, ROWS, COLS);

	// write output:
	printf("Output:\n");
	printMatrix(B, ROWS, COLS);

	// free matrix:
	freeMatrix(B, ROWS);

	return 0;
}
// --------------------------- //

/// <summary>
/// This code required one extra important function.
/// Think hard about what it should be.
/// </summary>
/// <params>You decide</params>
/// <returns>You decide</returns>

fraction reduce_fraction(int numer, int denom)
{
	// your code:
	fraction frac;
	int nu, a, b, r;

	if (numer == 0) {
		frac.num = 0;
		frac.numerator = 0;
		frac.denominator = 1;
		return frac;
	}

	frac.num = numer / denom;
	nu = numer % denom;

	if (nu == 0) {
		frac.numerator = 0;
		frac.denominator = 1;
		return frac;
	}

	a = nu; 
	b = denom;

	while (b) {
		r = a % b;
		a = b;
		b = r;
	}

	frac.numerator = nu / a;
	frac.denominator = denom / a;

	return frac;
}

// --------------------------- //

/// <summary>
/// This function allocate a dynamic matrix from type fraction.
/// </summary>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>allocated empty matrix B from type fraction</returns>
fraction** createMatrix(int rows, int cols)
{
	// your code:
	int i;
	fraction** mat = (fraction**)malloc(rows * sizeof(fraction*));
	for (i = 0; i < rows; i++) {
		mat[i] = (fraction*)malloc(cols * sizeof(fraction));
	}
	return mat;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix 
/// and for each cell in the matrix calculates 
/// the average of its neighbors.  
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>matrix B from type fraction</returns>
fraction** matrixAverageNeighbor(int A[][COLS], int rows, int cols)
{
	// your code:
	int i, j;
	fraction** B = createMatrix(rows, cols);

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			B[i][j] = neighborFractionAverage(A, i, j, rows, cols);
		}
	}
	return B;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix, and a cell value,
/// and calculates the average of its neighbors.  
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int i - the cell row number in matrix</param>
/// <param>int j - the cell colum number in the matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>value from type fraction</returns>
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols)
{
	// your code:
	int sum = 0, count = 0;

	if (rows == 1 && cols == 1) 
		return reduce_fraction(0, 1);

	if (i > 0 && j > 0) { 
		sum += A[i - 1][j - 1];
		count++;
	}
	if (j > 0) { 
		sum += A[i][j - 1];
		count++;
	}
	if (i < rows - 1 && j > 0) {
		sum += A[i + 1][j - 1];
		count++;
	}
	if (i < rows - 1) { 
		sum += A[i + 1][j];
		count++;
	}
	if (i < rows - 1 && j < cols - 1) { 
		sum += A[i + 1][j + 1];
		count++;
	}
	if (j < cols - 1) { 
		sum += A[i][j + 1];
		count++;
	}
	if (i > 0 && j < cols - 1) { 
		sum += A[i - 1][j + 1];
		count++;
	}
	if (i > 0) {
		sum += A[i - 1][j];
		count++;
	}

	if (count == 0)
		return reduce_fraction(0, 1);

	return reduce_fraction(sum, count);
}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and print the matrix as double varibles.  
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>None</returns>
void printMatrix(fraction** B, int rows, int cols)
{
	// your code:
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("%.2lf ", (double)B[i][j].num + (double)B[i][j].numerator / (double)B[i][j].denominator);
		}
		printf("\n");
	}
}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and free all allocated memory.  
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <returns>None</returns>
void freeMatrix(fraction** B, int rows)
{
	// your code:
	int i;
	for (i = 0; i < rows; i++) {
		free(B[i]);
		B[i] = NULL;
	}
	free(B);
	B = NULL;
}
// --------------------------- //
