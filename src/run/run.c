/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:39:23 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/07 15:42:46 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include "run.h"
#include "parser.h"
#include "heredoc.h"
#include "executor.h"
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

static int	_process_command(char **user_input, unsigned char *exit_status,
char **envp)
{
	t_data	data;

	data.tokens = NULL;
	data.tree = NULL;
	if (lexer(*user_input, &data.tokens))
		return (EXIT_FAILURE);
	free(*user_input);
	*user_input = NULL;
	if (expander(&data.tokens, exit_status))
		return (free_tokens(&data.tokens), EXIT_FAILURE);
	if (heredoc(&data.tokens))
		return (free_tokens(&data.tokens), EXIT_FAILURE);
	print_all_tokens(data.tokens); // DEBUG
	if (parser(data.tokens, &data.tree))
		return (free_tokens(&data.tokens), EXIT_FAILURE);
	print_ast(data.tree, 0); // DEBUG
	executor(&data, exit_status, envp);
	cleanup_hdoc(&data.tokens);
	free_tokens(&data.tokens);
	cleanup_ast(&data.tree);
	return (EXIT_SUCCESS);
}

int	run_minishell(char **envp)
{
	struct sigaction	sa;
	char				*user_input;
	unsigned char		exit_status;

	_connect_to_signals(&sa);
	exit_status = 0;
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
		_process_command(&user_input, &exit_status, envp);
		free(user_input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
