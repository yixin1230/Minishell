/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 09:10:27 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/28 14:40:09 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_pipe(t_data *all, t_cmd *cmd)
{
	int	*fd;
	
	fd = malloc(siezof(int) * 2);
	if (fd)
		return ;
	protect_pipe(fd);
	cmd->in = fd[0];
	cmd->out = fd[1];
	close(cmd->in);
	close(cmd->out);
}

int	open_pipe(t_data *all)
{
	int		**fd_2d;
	int		i;
	t_cmd	*curr;

	i  = 0;
	fd_2d = malloc(sizeof(int*) * (all->cmd_len + 1));
	if (!ft_2d)
		return (1);
	fd_2d[all->cmd_len] = NULL;
	curr = all->cmd;
	while (curr)
	{
		if (init_pipe(all, curr) == -1)
		{
			free_fd_2d(fd_2d);
			return (1);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	free_fd_2d(fd_2d);
	return (0);
}

void	free_fd_2d(int **fd_2d)
{
	int	i;

	i = 0;
	while (fd_2d[i])
	{
		free(fd_2d[i]);
		i++;
	}
	free(fd_2d);
}
//open pipe, init pipe
//open_fd, redi
// fork, inside child dup2, parent close(fd1)close(fd0)
