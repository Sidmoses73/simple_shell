#include "shell.h"
/**
 * array_main - Function for array
 * Return: 0 on success
 */
int array_main(void)
{
/* array of integers with 5 elements*/
int numbers[5] = { 2, 4, 6, 8, 10 };

/* loop through the array and print each element*/
int i;
for (i = 0; i < 5; i++)
{
printf("%d ", numbers[i]);
}
printf("\n");

/*update an element in the array*/
numbers[2] = 7;

/* loop through the array and print each element again*/
for (i = 0; i < 5; i++)
{
printf("%d ", numbers[i]);
}
printf("\n");

return (0);
}
