// Course: Advanced C programming
// exercise 2, question 4
// file name: ex2_q3.c

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
#define PATH1 "c:\\temp\\file1.txt"
#define PATH2 "c:\\temp\\file2.txt"
#define PATH3 "c:\\temp\\file3.txt"


// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //

int memoryReport(char* filename);
int stringToNumPush(char* s, int* i);
int MatByteCalc(int* first, int* second);

// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	int total1, total2, total3, total4;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	total1 = memoryReport(PATH1);
	total2 = memoryReport(PATH2);
	total3 = memoryReport(PATH3);

	// write output:
	printf("Output:\n");
	printf("First file required %d bytes\n", total1);
	printf("Second file required %d bytes\n", total2);
	printf("Third file required %d bytes\n", total3);

	return 0;
}
// --------------------------- //


int stringToNumPush(char* s, int* i)
{
	int  c = 0;
	while (s[*i] && s[*i] <= '9' && s[*i] >= '0')
	{
		c *= 10;
		c += s[(*i)++] - '0';
	}
	return c;
}


int MatByteCalc(int* first, int* second)
{
	int  c = 0;
	c = (*first) * (*second);
	return c;
}

/// <summary>
/// The function receives a pointer to a string, representing a path to a file.
/// The function output all varibles declerations and their size in byte.
/// </summary>
/// <param>char *filename - valid path to a file</param>
/// <returns>total bytes required</returns>
///
int memoryReport(char* filename)
{
	// your code:
	FILE* f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("Could not open file\n");
		return 0;
	}
	char s[200] = { 0 };
	char* declaration = fgets(s, sizeof(s), f);
	int i, size = strlen(s), v_size = 0, c, c2, total_sum = 0, ptr_size = 4;
	int token_ptr;
	char variable[3] = "";

	do
	{
		size = strlen(s);
		for (i = 0; i < size - 1; i++)
		{
			if ((i > 0) && (declaration[i - 1] == '*'))
			{
				break;
			}
			while ((declaration[i] == '\t') || (declaration[i] == ' '))
				++i;
			if (declaration[i] != ' ' && declaration[i] != '*')
			{
				variable[0] = declaration[i];
				if (variable[0] != 'l' && variable[0] != 'u')
				{
					variable[1] = '\0';
					for (; (declaration[i] != ' ') && (declaration[i] != '*'); i++); { 
						break;
					}
				}
				else
				{
					switch (variable[0])
					{
					case 'l':

						for (i = i + 5; i < size - 1; i++)
						{
							v_size = 8;
							while ((declaration[i] == '\t') || (declaration[i] == ' '))
								++i;
							if (declaration[i] == '*') {
								v_size = 4;
								variable[1] = '/0';
								variable[0] = '*';
								i++;
								break;
							}
							if (declaration[i] != ' ')
							{
								while ((declaration[i] == '\t') || (declaration[i] == ' '))
									++i;
								if (declaration[i] == 'l')
									if ((declaration[i + 4] == '*') && (declaration[i + 3] == 'g')) {
										i = i + 4;
										v_size = 4;
									}
									else if (declaration[i + 1] && declaration[i + 1] == 'o'
										&& declaration[i + 2] && declaration[i + 2] == 'n'
										&& declaration[i + 3] && declaration[i + 3] == 'g'
										&& declaration[i + 4] && declaration[i + 4] == ' ')
									{
										variable[1] = 'l', variable[2] = '\0';
										i += 4;
									}
									else
										variable[1] = '/0';
								if (declaration[i + 4] != '*' && declaration[i + 4] != ' ') {
									break;
								}
								break;
							}
							else
							{
								break;
							}
							break;
						}
						break;
					case 'u':
						for (i = i + 8; i < size - 1; i++)
						{
							if (declaration[i] != ' ')
							{
								if (declaration[i] == 'i') {
									if (declaration[i + 1] && declaration[i + 1] == 'n'
										&& declaration[i + 2] && declaration[i + 2] == 't')
									{
										i += 3;
										variable[1] = '/0';
									}
									else
										variable[1] = '/0';
								}
								else {
									i = i - 8;
								}
								break;
							}
						}
						break;
					}
				}
			}
			break;
		}

		switch (variable[0])
		{
		case 'c':
			v_size = sizeof(char);
			break;
		case 's':
			v_size = sizeof(short);
			break;
		case 'i':
			v_size = sizeof(int);
			break;
		case 'u':
			v_size = sizeof(unsigned int);
			break;
		case 'f':
			v_size = sizeof(float);
			break;
		case 'd':
			v_size = sizeof(double);
			break;
		case 'l':
			v_size = (variable[1] ? sizeof(long long) : sizeof(long));
			break;
		default:
			break;
		}
		while (i < size - 1)
		{
			if (declaration[i] != ' ' && declaration[i] != ',')
			{
				//when the declaration is *
				if (declaration[i] == '*')
				{
					for (i += 1; i < size; i++)
					{
						if (declaration[i] != ' ')
						{
							while (declaration[i] != ' ' && declaration[i] != ';' && declaration[i] != ',') {
								if (declaration[i] == '[') {
									break;
								}
								printf("%c", declaration[i++]);
							}
							while ((declaration[i] == '\t') || (declaration[i] == ' '))
								++i;
							if (declaration[i] == '[') {
								while ((declaration[i] == '\t') || (declaration[i] == ' '))
									++i;
								v_size = 4; 
								break;
							}
							printf(" requires %d Bytes\n", ptr_size);
							total_sum += ptr_size;
							break;
						}
					}

				}
				else
				{
					if (declaration[i] == ';')
						break;
					while (declaration[i] != ';' && declaration[i] != ' ' && declaration[i] != ',' && declaration[i] != '[') {
						while ((declaration[i] == '\t') || (declaration[i] == ' '))
							++i;
						printf("%c", declaration[i++]);

					}
					while ((declaration[i] == '\t') || (declaration[i] == ' '))
						++i;
					printf(" requires ");
					if (declaration[i] == '[')
					{
						i++;
						while ((declaration[i] == '\t') || (declaration[i] == ' '))
							++i;
						while ((declaration[i] == '\t') || (declaration[i] == ' '))
							++i;
						c = stringToNumPush(declaration, &(i));
						i++;
						while ((declaration[i] == '\t') || (declaration[i] == ' '))
							++i;
						if (declaration[i] == '[') {
							i++;
							c2 = stringToNumPush(declaration, &(i));
							printf("%d bytes\n", MatByteCalc(&c, &c2) * v_size);
							total_sum += MatByteCalc(&c, &c2) * v_size;
						}
						else
						{
							printf("%d bytes\n", c * v_size);
							total_sum += c * v_size;
						}

					}
					else {
						printf("%d bytes\n", v_size);
						total_sum += v_size;
					}
					i++;
				}
			}
			else
				i++;
		}
	} while (declaration = fgets(s, sizeof(s), f));
	fclose(f);
	return total_sum;
}

// --------------------------- //
