/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 10:12:16 by yizhang       #+#    #+#                 */
/*   Updated: 2023/05/30 13:03:08 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//printf
//strlen
//exit
//syscalls

/* 
Something: 
	The shell implementation is divided into three parts: The Parser, The Executor, and Shell 
	Subsystems.  
	Shell Subsystems :Environment Variables: Expressions of the form ${VAR} are expanded with the 
	corresponding environment variable. Also the shell should be able to set, expand and 
	print environment vars. 
	● Wildcards: Arguments of the form a*a are expanded to all the files that match them in 
	the local directory and in multiple directories . 
	● Subshells: Arguments between `` (backticks) are executed and the output is sent as 
	input to the shell. 

1. command line prompt ,error check,
2. buffer for arg,read input
	parse that line that we just got from the input,
	creat a data structure
3. while loop,run minishell, run cmd till exit
4. free every thing
5. test
 */
int main(void)
{
	//set_prompt
	//get_next_line
	//The Lexical Analyzer
	//The Syntax Tree Parser
	while (1)
	{

	}
	return (0);
}