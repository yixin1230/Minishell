/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/06 11:37:38 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_data all;
	char *input;

	(void)argc;
	(void)argv;
	all.envp = envp;
	while (1)
	{
		all.tmp_out = dup(1);
		all.tmp_fd = dup(0);
		protect_dup2(all.tmp_out, 1, &all);
		protect_dup2(all.tmp_fd, 0, &all);
		all.cmd = NULL;
		all.token = NULL;
		all.id = NULL;
		input = readline("minishell-> ");
		all.input = input;
		add_history(all.input);
		ft_commands(envp, &all);
		free_cmd(&all);
		free(input);
		free(all.input);
		free(all.id);
	}
	return (0);
}