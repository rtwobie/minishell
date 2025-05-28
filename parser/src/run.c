/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:39:23 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/28 19:47:36 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "parser_utils.h"
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


void print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		++i;
	}
	printf("Number of Tokens: %i\n", i);
}

void	read_input(const char *user_input);

static int	_execute_command(const char *user_input)
{
	// Tokenize input
	// look for cmd
	// if cmd is built-in give search for built-in function
	//
	// free tokens
	read_input(user_input);
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
