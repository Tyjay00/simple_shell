#include "shell.h"

/**
 * dup_chars - Duplicates characters from a string.
 * @pathstr: The input string from which characters are to be duplicated.
 * @start: Starting index from where to start duplicating characters.
 * @stop: Stopping index until which characters are to be duplicated.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 *
 * Description: This function duplicates characters from the 'pathstr' string
 * starting from index 'start' until index 'stop'. The duplicated characters
 * are stored in a static buffer 'buf'. The function then returns a pointer to
 * the buffer 'buf' containing the duplicated characters. It is important to
 * note that the static buffer 'buf' is reused for each call to this function,
 * so its content will be overwritten on subsequent calls. It is the caller's
 * responsibility to use the duplicated content before calling this function
 * again to avoid unintended side effects.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Finds the full path of a command in the PATH string.
 * @info: Pointer to the info struct containing command information.
 * @pathstr: The PATH string containing directories separated by colons.
 * @cmd: The command to find in the PATH directories.
 *
 * Return: Pointer to the full path of the command if found,
 *         or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: Pointer to the info struct containing command information.
 * @path: Path to the file to be checked.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
