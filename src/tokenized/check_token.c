/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:56:36 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/20 16:56:36 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_token(t_data *all)//should happen after env
{
	t_token	*curr;
	char	*topstr;
	char	*endstr;

	curr = all->token;
	while (curr)
	{
		if (curr->str && curr->next && !curr->next->str)
		{
			topstr = curr->str;
			printf("top:%s",topstr);
		}
		while (curr && !curr->str)
		{
			if (!curr->next)
				break ;
			curr = curr->next;
		}
		if (curr && curr->str && curr->prev && !curr->prev->str)
		{
			endstr = curr->str;
			printf("end:%s",endstr);
		}
		if (!curr->next)
			return ;
		curr = curr->next;
	}
}

// void	delete_token(t_token *token)
// {

// }


//test:gcc check_token.c split_token.c token_util.c tokenized.c ../tool/free_error.c ../tool/protection.c ../tool/tool_utils.c ../env/find_env.c ../env/handle_dollar_sign.c ../../libft/libft.a
int main(int argc, char **argv,char **envp)
{
	t_token *curr;
	t_data	all;
	char *str;

	all.cmd =NULL;
	all.history =NULL;
	(void)argc;
	(void)argv;
	//all.input = "  c\"\'\" asdasda\"\'\">&| \"|\" ";
	//all.input = " cmd arg| cmd";
	//all.input = "  chkhk df";
	//all.input = "  chkhk df >outfile <infile";
	//all.input = " cmd <file  >outfile | \"|\"<infile";
	//all.input = "cat <file1 cat > out | <ls| <file cmd"; //break pipe
	all.input = " $PA''TH $$<< inf''ile hgj''gh$dsf$sdfd$?$$$$$ <infile cmd arg>outfile| cmd1 aa a a a >1outfile|";//$$ error
	//all.input = " $PATH ADS  $sdf $ df hgjgh$dsf$sdfd$?$$$$$";
	//all.input = " $PATH ";
	//all.input = "||\"|\"cmd "; //break pipe
	//all.input = " \"echo\" hello ";
	//all.input = " \"echo\" hello | wc";
	//all.input = "<file1 cat > out \"|\" <infile "; //works 
	//all.input = " <infile cmd >outfile | <infile";
	tokenized(&all, envp);
	check_token(&all);
	curr = all.token;
	printf("test:%s\n", all.input);
	 while (curr != NULL)
	{
		printf(" %i: type :%i :%s\n", curr->index, curr->type , curr->str);
		curr = curr->next;
	} 
	return 0;
}
