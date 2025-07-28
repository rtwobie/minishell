/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:39:23 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/23 17:53:37 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "run.h"
#include "parser.h"
#include "error.h"
#include "tokenizer.h"
#include "debug.h"

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

static int	_execute_command(char **user_input)
{
	t_token		*tokens;
	t_ast_node	*ast;
	int			err;

	tokens = NULL;
	ast = NULL;
	err = lexer((char *)*user_input, &tokens);
	if (err)
	{
		print_error(err);
		return (EXIT_FAILURE);
	}
	free(*user_input);
	*user_input = NULL;
	err = expander(&tokens);
	if (err)
	{
		free_tokens(&tokens);
		return (EXIT_FAILURE);
	}
	// TEST: DEBUG
		print_all_tokens(tokens);
	if (parser(tokens, &ast))
	{
		print_error(1);
		free_tokens(&tokens);
		return (EXIT_FAILURE);
	}
	cleanup_ast(ast);
	free_tokens(&tokens);
	return (EXIT_SUCCESS);
}

// 1. Lexer (your existing `lexer` function) -> creates raw tokens
// 2. Expander (new function) -> processes raw tokens for expansions
// TODO:	the variable to expend ist delimited by if(ft_alnum())
//			find out how to get the expansion -> probably from env
//			research/test '$$' what it means and the behaviour
//
// 3. Parser -> builds command tree from expanded tokens
// 4. Executor -> runs commands

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
		_execute_command(&user_input);
		free(user_input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

// TODO: ln15: use exit function instead
