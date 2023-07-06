/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 08:56:25 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/06 16:24:39 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_upper(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] >= 'a' && str[i]<= 'z')
			return (0);
		i++;
	}
	return (1);
}

int	env_index(t_token *token, char **envp)
{
	int	i;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(&token->str[1], "=");
	while(envp[++i])
	{
		if (ft_strnstr(envp[i], tmp, ft_strlen(tmp)) != NULL)
		{
			free(tmp);
			return (i);
		}
	}
	if (!envp[i])
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (i);
}

char	*find_env(t_token **token, char **envp)
{
	int	index;

	if (!*token)
		return (NULL);
	if (ft_strcmp((*token)->str, "$") == 0)
		return ((*token)->str);
	index = env_index(*token, envp);
	if (index == -1)
		return (NULL);
	return (envp[index]);
}


//test: gcc find_env.c ../tokenized/token_util.c ../../libft/libft.a

/* int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//t_token *token = new_token("$PATH");
	//t_token *token = new_token("$OLDPWD");
	//t_token *token = new_token("$TERM_SESSION_ID");
	char *str = find_env(&token, envp);
	printf("%s\n",str);
	return 0;
} */