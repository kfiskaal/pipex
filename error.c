#include "pipex.h"

void	ft_perror_filename(char *str, char *filename)
{
	char	*p;

	write(STDERR, str, ft_strlen(str));
	p = strerror(errno);
	write(STDERR, p, ft_strlen(p));
	write(STDERR, ": ", 2);
	write(STDERR, filename, ft_strlen(filename));
	write(STDERR, "\n", 1);
	exit (EXIT_FAILURE);
}

void	exit_error(char *str)
{
	char *p;

	p = strerror(errno);
	write (STDERR, str, strlen(str));
	write (STDERR, p, ft_strlen(p));
	write (STDERR, "\n", 1);
	exit (EXIT_FAILURE);

}

void	error_cmd(char **cmd, char *path)
{
	char *p;

	p = strerror(errno);
	if (ft_strchr(cmd[0], '/'))
	{
		write (STDERR, "Error: ", 7);
		write (STDERR, p, ft_strlen(p));
		write (STDERR, ": ", 2);
		write (STDERR, cmd[0], ft_strlen(cmd[0]));
		write (STDERR, "\n", 1);
	}
	else
	{
		write(STDERR, ERROR_CMD, ft_strlen(ERROR_CMD));
		write (STDERR, cmd[0], ft_strlen(cmd[0]));
		write (STDERR, "\n", 1);
	}
	free_array (cmd);
	free (path);
	exit (EXIT_FAILURE);
}