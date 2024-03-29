/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:50:27 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/31 13:38:18 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_error_msg(char *str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(msg, 2);
}

static void	ft_process_error(char *str, int errcode, t_data *all)
{
	if (str)
		ft_error_msg(str, ": ");
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free_all(all);
	if (errcode == 1 || errcode == 126)
		exit(errcode);
	else
		exit(errno);
}

static int	print_error_utils(char *str, int errcode, t_data *all)
{
	if (errcode == 6 && str)
	{
		ft_error_msg(str, ": No such file or directory\n");
		exit(126);
	}
	else if (!str && errcode == 1)
	{
		ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		g_exit_status = 1;
		return (1);
	}
	else if (str)
		ft_process_error(str, errcode, all);
	return (0);
}

int	print_error(char *str, int errcode, t_data *all)
{
	if (errcode == 127 && str)
	{
		if (str[0] == '.' || str[0] == '/')
			ft_error_msg(str, ": No such file or directory\n");
		else
			ft_error_msg(str, ": command not found\n");
		exit(errcode);
	}
	else if (errcode == 7 && str)
	{
		ft_error_msg(str, ": is a directory\n");
		exit(126);
	}
	else
		if (print_error_utils(str, errcode, all))
			return (1);
	return (0);
}
