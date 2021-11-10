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
	if (access(cmd, F_OK) != -1)
		return (cmd);
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

int	exec(char *cmd, int in_fd, int out_fd, char **envp, int to_close, int bis)
{
	int pid;
	char **av_cmd;
	char *c;

	av_cmd = ft_split(cmd, ' ');
	c = find_valid_path(envp, av_cmd[0]);
	if (c == NULL)
		{
			write(STDERR_FILENO, "command not found", ft_strlen("command not found"));
			return (-1);
		}
	pid = fork();

	if (pid == 0)
		{
			close(to_close);
			close(bis);
			dup2(in_fd, STDIN_FILENO);
			dup2(out_fd, STDOUT_FILENO);
			close(in_fd);
			close(out_fd);
			execve(c, av_cmd, envp);
		}
	return pid;
}

int	ft_open(char *path, int flags, mode_t mode)
{
	int fd;

	if (mode == 0)
		fd = open(path, flags);
	else
		fd = open(path, flags, mode);
	if (fd == -1)
		exit(0);
	return (fd);
}

int	main(int ac, char **av, char **envp)
{
	int fd1;
	int fd2;
	pid_t	pid1;
	pid_t	pid2;
	int p[2];

	if (ac != 5)
		return (ft_error_dealer("Error\nAc != 5\n"));
	int i = fork();
	if (i == 0) 
	{
		fd1 = ft_open(av[1], O_RDONLY, 0);
		fd2 = ft_open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
		pipe(p);
		pid1 = exec(av[2], fd1, p[1], envp, p[0], fd2);
		if (pid1 == -1)
			printf("Could not execve\n");
		close(fd1);
		close(p[1]);
		pid2 = exec(av[3], p[0], fd2, envp, -1, -1);
		if (pid2 == -1)
		{
			printf("Could not execve\n");
			exit(128);
		}
		close(fd2);
		close(p[0]);

		/*int pid = waitpid(-1, NULL, 0);
		if (pid == pid1) {
			close(p[1]);
		} else {
			close(fd1);
		}*/
		waitpid(-1, NULL, 0);
		waitpid(-1, NULL, 0);
	} else {
		waitpid(i, NULL, 0);
	}
}

/*int main(int ac, char **av, char **envp)
{
	char **cmd1;
	char **cmd2;
	int i;
	pid_t pid_1;
	pid_t pid_2;
	int tube[2];
	int status;

	pipe(tube);
	//cmd1 = ft_split(av[2], ' ');
	//pid_1 = fork();
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
	waitpid(pid_1, &status, 0);
	printf("Cmd1 done\n");
	waitpid(pid_2, &status, 0);
	printf("Cmd2 done\n");
	free_array(cmd2);
	return (0);
}*/

/*
int main(int ac, char **av, char **envp)
{
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
	waitpid(pid_1, &status, 0);
	printf("Cmd1 done\n");
	waitpid(pid_2, &status, 0);
	printf("Cmd2 done\n");
	free_array(cmd2);
	return (0);
}
*/