// Course: Advanced C programming
// exercise 2, question 3
// file name: ex2_q3.c

// --------------------------- //
//
//	Assigned by:
//	    Leon Yurkovski #314972357 
//		Koren Abugov #211480157
//
// --------------------------- //

// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define scanf_s scanf

// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //

void decode(char* str);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	char str1[] = "Hr(o Zjeno#";
	char str2[] = "H gmlw xmq(jo ojascyr vgpz xmqjcyzxia0 Vc bmqdn zjh gyrw acaf jghdox 0 np vmnko0 dvlwvfsf3 Mms hd xmq cmj-l lgjv3 H/k fmefq sm acz7";

	// Start Program:
	printf("Start Program\n");

	// call functions:
	decode(str1);
	decode(str2);

	// write output:
	printf("Output:\n");
	puts(str1);
	puts(str2);

	return 0;
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to a string,
/// and decode it according to the assignment requirment
/// </summary>
/// <param>char *str - encoded string</param>
/// <returns>None</returns>
void decode(char* str)
{
    // your code:
    int i = 0, j;
    int counter = 1;

    for (j = 0; str[j] != '\0'; j++) {

        if (isalpha(str[j])) {
            if (isupper(str[j])) {
                str[j] = 'A' + (str[j] - 'A' + (1 << i)) % 26;
                i++;
            }
            else if (islower(str[j])) {
                str[j] = 'a' + (str[j] - 'a' + (1 << i)) % 26;
                i++;
            }
        }
        else if (ispunct(str[j]) || isdigit(str[j])) {
            str[j] -= counter;
            counter++;
        }
        else if (isspace(str[j])) {
            i = 0;
        }

    }
}
// --------------------------- //
