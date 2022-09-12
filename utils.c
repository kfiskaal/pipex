#include "pipex.h"

void	find_path(t_path *cmd, char **envp)
{
	int i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp)
		exit_error("Envp: ");
	cmd->path_line = envp[i] + 5;
	cmd->split_line = ft_split(cmd->path_line, ':');
}

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
	free(arr);
}

char	*ft_strjoin_free(char const *s1, char *s2)
{
	unsigned int	len;
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, len);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[++j] != '\0')
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	free(s2);
	return (str);
}

char	*find_cmd(char *cmd, char **envp_split)
{
	char *path;
	int i;

	i = 0;
	path = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK))
			return (cmd);
		else
			return (NULL);
	}
	while (envp_split[i])
	{
		path = ft_strjoin("/", cmd);
		path = ft_strjoin_free(envp_split[i], path);
		if (access(path, F_OK) == 0)
			return path;
		free (path);
		i++;
	}
	return (NULL);
}