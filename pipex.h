#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include <errno.h>
#include <string.h>

#define STDERR 2
#define STDIN 0
#define STDOUT 1

#define ERROR_USAGE "Usage : ./pipex file1 cmd1 cmd2 file2\n"
#define ERROR_CMD "Error: command not found : "


typedef struct s_path
{
	char	**split_line;
	char	*path_line;
}				t_path;

void	exit_error(char *str);
void	error_cmd(char **cmd, char *path);
void	ft_perror_filename(char *str, char *filename);
void	free_array(char **arr);
char	*ft_strjoin_free(char const *s1, char *s2);
char	*find_cmd(char *cmd, char **envp_split);
void	find_path(t_path *cmd, char **envp);

#endif