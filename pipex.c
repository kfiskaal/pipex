#include "pipex.h"

void	child1(int	end[], char **av, char **envp, t_path *cmd_s)
{
	char	*path;
	char	**cmd;
	pid_t	pid1;
	int		fd_in;

	pid1 = fork();
	if (pid1 < 0)
		exit_error("Fork :");
	if (pid1 == 0)
	{
		fd_in = open(av[1], O_RDONLY);
		if (fd_in < 0)
			ft_perror_filename("Error: ", av[1]);
		if (dup2(fd_in, STDIN) < 0 || dup2(end[1], STDOUT) < 0)
			exit_error("Dup2: ");
		close(end[0]);
		close(fd_in);
		cmd = ft_split(av[2], ' ');
		path = find_cmd(cmd[0], cmd_s->split_line);
		if (cmd && path)
			execve(path, cmd, envp);
		else
			error_cmd(cmd, path);
	}
}

void	child2(int end[], char **av, char **envp, t_path *cmd_s)
{
	char	**cmd;
	int		fd_out;
	char	*path;
	pid_t	pid2;

	pid2 = fork();
	if (pid2 < 0)
		exit_error("Fork :");
	if (pid2 == 0)
	{
		fd_out = open (av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd_out < 0)
			ft_perror_filename("Error: ", av[4]);
		if (dup2(fd_out, STDOUT) < 0 || dup2(end[0], STDIN) < 0)
			exit_error("Dup2: ");
		close(end[1]);
		close(fd_out);
		cmd = ft_split(av[3], ' ');
		path = find_cmd(cmd[0], cmd_s->split_line);
		if (cmd && path)
			execve(path, cmd, envp);
		else
			error_cmd(cmd, path);
	}
}

void	pipex(char **av, char **envp, t_path *cmd_path, int end[])
{
	cmd_path->split_line = NULL;
	if (pipe(end) < 0)
		exit_error("Pipe: ");
	find_path(cmd_path, envp);
	if (!cmd_path->split_line)
		exit_error("Error: ");
	child1(end, av, envp, cmd_path);
	child2(end, av, envp, cmd_path);
}

int	main(int ac, char **av, char **envp)
{
	int status;
	t_path	cmd_path;
	int end[2];

	if (ac == 5)
	{
		pipex(av, envp, &cmd_path, end);
		close (end[0]);
		close (end[1]);
		waitpid(-1, &status, 0);
		waitpid(-1, &status, 0);
		free_array (cmd_path.split_line);
	}
	else
	{	
		write(STDERR, ERROR_USAGE, ft_strlen(ERROR_USAGE));
		exit(EXIT_FAILURE);
	}	
	return (0);
} 