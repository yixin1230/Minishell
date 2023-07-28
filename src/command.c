/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/13 10:21:45 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_commands(char **envp, t_data *all)
{
	t_cmd	*curr;
	int		i;

	i = 0;
	if (ft_strcmp(all->input, "exit") == 0)
		exit(0);
	//else if (ft_strcmp(all->input, "history") == 0)
	//	printf_history(all->history);
	else if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all, envp);
		token_to_cmd(all);
		free_token(all->token);
		curr = all->cmd;
		//here shcould open and init pipe, I should read more code to understand
		//malloc t_pid ,in the end waitpid_loop;
		//loop_redi cmd
		//below are fork thing
		//open_pipe();
		all->id = malloc(sizeof(pid_t) * all->cmd_len);
		if (!all->id)
			return ;
		if (curr && !curr->next)
			one_cmd_child(curr, envp, all);
		else if (curr && curr->next)
		{
			while (curr)
			{
				one_cmd_child(curr, envp, all);
				if (!curr->next)
					return ;
				curr = curr->next;
			}
		}
		while (i < all->cmd_len)
		{
			protect_waitpid(all->id[i], &all->status, 0);
			if (WEXITSTATUS(all->status))
				all->status = WEXITSTATUS(all->status);
			i++;
		}
		free_cmd(all);
	}
}


