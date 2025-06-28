/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:39:23 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/26 18:22:35 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "lexer.h"
#include "token_list.h"
#include "structs.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static void	_reset_prompt(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

static void	_signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
		_reset_prompt();
}

static void	_connect_to_signals(struct sigaction *sa)
{
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = _signal_handler;
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static int	_execute_command(const char *user_input)
{
	t_token	*tokens;
	int		errn;

	tokens = NULL;
	errn = lexer((char *)user_input, &tokens);
	if (errn)
	{
		printf("errn: %i\n", errn);
		return (EXIT_FAILURE);
	}
	print_tokens(tokens);
	// Tokenize input
	// look for cmd
	// if cmd is built-in give search for built-in function

	// 1. Lexer (your existing `lexer` function) -> creates raw tokens
	// 2. Expander (new function) -> processes raw tokens for expansions
	// TODO:	the variable to expend ist delimited by if(ft_alnum())
	//			find out how to get the expansion -> probably from env
	//			research/test '$$' what it means and the behaviour
	//
	// 3. Parser -> builds command tree from expanded tokens
	// 4. Executor -> runs commands
	free_tokens(&tokens);
	return (EXIT_SUCCESS);
}

int	run_minishell(void)
{
	char *user_input;
	struct sigaction sa;
	_connect_to_signals(&sa);
	while (1)
	{
		user_input = readline(PROMPT);
		if (user_input == NULL)
		{
			printf("exit\n");
			break ;
		}

		if (*user_input)
			add_history(user_input);
		// execute command:
		_execute_command(user_input);
		free(user_input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

// TODO: ln15: use exit function instead
