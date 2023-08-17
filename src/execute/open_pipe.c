/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 15:24:54 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 15:24:54 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_pipe(t_data *all, t_cmd *cmd, int **fd_2d)
{

	(void)all;
	fd_2d[cmd->index] = malloc(sizeof(int) * 2);
	if (!fd_2d[cmd->index])
		return (-1);
	if (pipe(fd_2d[cmd->index]) == -1)
	{
		free(fd_2d[cmd->index]);
		return (cmd->index);
	}
	if (cmd->index != 0)
		cmd->fd_in = fd_2d[cmd->index - 1][0];
	if (!cmd->next)
	{
		close(fd_2d[cmd->index][0]);
		close(fd_2d[cmd->index][1]);
	}
	else
		cmd->fd_out = fd_2d[cmd->index][1];
	return (0);
}

int	open_pipe(t_data *all)
{
	int		**fd_2d;
	t_cmd	*curr;
	int		index;

	fd_2d = malloc(sizeof(int*) * (all->cmd_len + 1));
	if (!fd_2d)
		return (1);
	fd_2d[all->cmd_len] = NULL;
	curr = all->cmd;
	while (curr)
	{
		index = init_pipe(all, curr, fd_2d);
		if (index != 0)
		{
			free_fd_2d(fd_2d ,index);
			return (1);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	free_fd_2d(fd_2d, 0);
	return (0);
}


void	free_fd_2d(int **fd_2d, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (index != 0)
		{
			close(fd_2d[i][0]);
			close(fd_2d[i][1]);
		}
		free(fd_2d[i]);
		i++;
	}
	free(fd_2d);
}