/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protection.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 12:54:21 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/12 12:55:28 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	protect_waitpid(pid_t id, int *status, int options, t_data *all)
{
	if (waitpid(id, status, options) == -1)
	{
		printf("4\n");
		print_error(NULL, 0, all);
		return (-1);
	}
	return (0);
}

void	protect_dup2(int file, int file2, t_data *all)
{
	if (dup2(file, file2) == -1)
	{
		printf("3\n");
		print_error(NULL, 0, all);
	}
}

void	protect_close(int file, t_data *all)
{
	if (close(file) == -1)
	{
		printf("2\n");
		print_error(NULL, 0, all);
	}
}

void	protect_write(int fd, char *buf, int count, t_data *all)
{
	if (write(fd, buf, count) == -1)
	{
			printf("1\n");
			print_error(NULL, 0, all);
	}
}

int	protect_pipe(int fd[2], t_data *all)
{
	(void)all;
	if (pipe(fd) == -1)
	{
		printf("5\n");
		//print_error(NULL, 0, all);
		return (-1);
	}
	return (0);
}
