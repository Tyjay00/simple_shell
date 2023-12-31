#include "shell.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 * This function concatenates two strings, src and dest.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	dest++;
	while (*src)
	*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strlen - Returns the length of a string.
 * @s: The string whose length to check.
 * This function calculates and returns the length of a given string.
 *
 * Return: Integer length of the string.
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
	return (0);

	while (*s++)
	i++;
	return (i);
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * @s1: The first string.
 * @s2: The second string.
 * This function performs lexicographic comparison of two strings, s1 and s2.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
	if (*s1 != *s2)
	return (*s1 - *s2);
	s1++;
	s2++;
	}
	if (*s1 == *s2)
	return (0);
	else
	return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if needle starts with haystack.
 * @haystack: String to search.
 * @needle: The substring to find.
 * This function checks if the string haystack starts with the string needle.
 *
 * Return: Address of the next char of haystack or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	if (*needle++ != *haystack++)
	return (NULL);
	return ((char *)haystack);
}

