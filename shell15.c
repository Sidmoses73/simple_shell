#include “shell.h”
/**
* free_pointer - frees a pointer and sets the address to NULL
* @ptr: address of the pointer to free
* @size: size of the memory block pointed by ptr
* Return: 1 if freed, otherwise 0.
*/
int free_pointer(void **ptr, size_t size)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
memset(*ptr, 0, size);
return (1);
}
return (0);
}

