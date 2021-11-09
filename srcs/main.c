/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:22:45 by sobouatt          #+#    #+#             */
/*   Updated: 2021/11/06 17:24:37 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/pipex.h"

int ft_error_dealer(char *str) {
	write(1, "Error\n", ft_strlen("Error\n"));
	write(1, str, ft_strlen(str));
	return (1);
}

int ft_strstr(char *str, char *to_find) {
	int i;
	int j;


	i = 0;
	j = 0;
	while (str[i] == to_find[j]) {
		i++;
		j++;
	}
	if (to_find[j] == '\0')
		return (1);
	return (0);
}

int find_path(char **envp) {
	int i;

	i = 0;
	while (envp[i]) {
		if (ft_strstr(envp[i], "PATH=") == 1)
			return (i);
		i++;
	}
	return (-1);
}

char *find_valid_path(char **envp, char *cmd) {
	int i;
	int ret_access;
	char *path;
	char **pathes;

	ret_access = -1;
	i = 0;
	pathes = ft_split(envp[find_path(envp)] + 5, ':');
	while (pathes[i] && ret_access == -1) {
		path = ft_strjoin(pathes[i], "/");
		path = ft_strjoin(path, cmd);
		ret_access = access(path, F_OK);
		i++;
	}
	if (ret_access == -1)
		return (NULL);
	return (path);
}

void free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int main(int ac, char **av, char **envp) {
	char **cmd1;
	char **cmd2;
	int i;
	int fd1;
	int fd2;
	int fd3;
	pid_t pid_1;
	pid_t pid_2;
	int tube[2];
	int status;

	printf("test\n");
	pipe(tube);
	if (ac != 5)
		return (ft_error_dealer("argc != 5\n"));
	fd1 = open(av[1], O_RDONLY);
	fd1 = dup2(fd1, STDIN_FILENO);
	cmd1 = ft_split(av[2], ' ');
	pid_1 = fork();
	if (pid_1 < 0)
	{
		free_array(cmd1);
		return (ft_error_dealer("Creation of the child process was unsccessful\n"));
	}
	if (pid_1 == 0)
	{
		close(tube[0]);
		fd2 = dup2(tube[1], STDOUT_FILENO);
		if (execve(find_valid_path(envp, cmd1[0]), cmd1, envp) < 0)
		{
			free_array(cmd1);
			return (ft_error_dealer("Execve didn't work\n"));
		}
	}
	else
	{
		i = 0;
		close(tube[1]);
		printf("Salut depuis l'enfant\n");
		fd2 = dup2(tube[0], STDIN_FILENO);
		cmd2 = ft_split(av[3], ' ');
		fd3 = open(av[4], O_CREAT | O_RDWR | O_TRUNC , 0644);
		pid_2 = fork();
		if (pid_2 < 0)
		{
			free_array(cmd2);
			ft_error_dealer("Creation of child process unsuccesful");
		}
		if (pid_2 == 0)
		{
			dup2(fd3, STDOUT_FILENO);
			if (execve(find_valid_path(envp, cmd2[0]), cmd2, envp) < 0)
			{
				free_array(cmd2);
				return (ft_error_dealer("Execve didn't work\n"));
			}
		}
		else
		{
			waitpid(pid_1, &status, 0);
			printf("Cmd1 done\n");
			waitpid(pid_2, &status, 0);
			printf("Cmd2 done\n");
			free_array(cmd2);
			return (0);
		}
	}
}