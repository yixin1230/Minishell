/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:50:27 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/04 16:13:10 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str, int errcode, t_data *all)
{
	if (errcode == 127 && str)
	{
		if (str[0] == '.' || str[0] == '/')
		{
			//ft_error_msg(str, ": No such file or directory\n");
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			//ft_error_msg(str, ": command not found\n");
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		exit(errcode);
	}
	if (errcode == 7 && str)
	{
		// ft_error_msg(str, ": is a directory\n");
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	if (errcode == 6 && str)
	{
		// ft_error_msg(str, ": No such file or directory\n");
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(126);
	}
	if (!str)
	{
		ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		g_exit_status = 1;
		return ;
	}
	if (str)
	{
		// ft_error_msg(str, ": \n");
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free_all(all);
	if (errcode == 1 || errcode == 126)
		exit(errcode);
	else
		exit(errno);
}

void	free_2dstr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	if (str)
		free(str);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		if (tmp->str)
			free(tmp->str);
		if (token->next)
		{
			token = token->next;
			free(tmp);
		}
		else
		{
			free(tmp);
			return ;
		}
	}
}

void	free_cmd(t_data *all)
{
	t_cmd	*tmp;

	while (all->cmd != NULL)
	{
		tmp = all->cmd;
		free_2dstr(tmp->words);
		free_token(tmp->redi);
		if (all->cmd->next)
		{
			all->cmd = all->cmd->next;
			free(tmp);
		}
		else
		{
			free(tmp);
			return ;
		}
	}
}

void	free_all(t_data *all)
{
	if (all->cmd)
		free_cmd(all);
	if (all->input)
		free(all->input);
	if (all->id)
		free(all->id);
}
