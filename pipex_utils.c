/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:04:20 by mofaisal          #+#    #+#             */
/*   Updated: 2023/02/22 21:58:29 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	open_file_and_redirect_input(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error while opening the file");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
}

char	*get_path_from_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp("PATH=", env[i], 5) == 0))
			return (ft_strdup((env[i] + 5)));
		i++;
	}
	return (NULL);
}

char	*find_command_path(char **directories, char *command)
{
	int		i;
	int		j;
	char	*joinedstr;
	char	*cmd;

	i = 0;
	j = 1;
	cmd = malloc(ft_strlen(command) + 2);
	cmd[0] = '/';
	i = 0;
	while (command[i] && command[i] != ' ')
		cmd[j++] = command[i++];
	cmd[ft_strlen(command) + 1] = '\0';
	i = 0;
	while (directories[i])
	{
		joinedstr = ft_strjoin(directories[i], cmd);
		if (access(joinedstr, F_OK) == 0)
			return (joinedstr);
		free(joinedstr);
		i++;
	}
	return (NULL);
}

int child_process(char **argv, char **env, int *fd)
{
	char	**flags;
	char	*path;
	char	**dirs;

	flags = NULL;
	fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("Error while opening the output file");
		exit(1);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	
	flags = ft_split(argv[2], ' ');
	path = get_path_from_env(env);
	if (!(path))
		return (ft_printf("ERROR WHILE FINDING THE PATH\n") * 0 + 1);
	dirs = ft_split(path, ':');
	if (execve(find_command_path(dirs, argv[2]), flags, env) < 0)
		return (ft_printf("Error: Executing the command failed\n"), exit(1), 1);	
	return (0);
}
int parent_process(char	**argv, char **env, int *fd)
{
	char	**flags;
	char	*path;
	char	**dirs;

	flags = NULL;
	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("Error while opening the output file");
		exit(1);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
}