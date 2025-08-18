/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:39:23 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/18 22:01:40 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

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

static int	_init_data(t_data *data, char **envp)
{
	data->envp = envp;
	data->tokens = NULL;
	data->tree = NULL;
	data->stdfd[0] = STDIN_FILENO;
	data->stdfd[1] = STDOUT_FILENO;
	data->restorefd[0] = dup(STDIN_FILENO);
	data->restorefd[1] = dup(STDOUT_FILENO);
	if (data->restorefd[0] < 0 || data->restorefd[1] < 0)
	{
		(close(data->restorefd[0]), close(data->restorefd[1]));
		return (perror("dup failed"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	_process_command(char **user_input, unsigned char *exit_status,
char ***envp, t_list **env_history)
{
	t_data	data;

	if (_init_data(&data, *envp))
		return (EXIT_FAILURE);
	data.env_history = *env_history;
	if (lexer(*user_input, &data.tokens))
		return (EXIT_FAILURE);
	free(*user_input);
	*user_input = NULL;
	if (expander(&data.tokens, exit_status, &data))
		return (free_tokens(&data.tokens), EXIT_FAILURE);
	if (heredoc(&data.tokens))
		return (free_tokens(&data.tokens), EXIT_FAILURE);
	print_all_tokens(data.tokens); // DEBUG
	if (parser(data.tokens, &data.tree))
		return (free_tokens(&data.tokens), EXIT_FAILURE);
	print_ast(data.tree, 0); // DEBUG
	executor(&data, exit_status);
	*envp = data.envp;
	*env_history = data.env_history;
	cleanup_hdoc(&data.tokens);
	cleanup_data(&data);
	return (EXIT_SUCCESS);
}

int	run_minishell(char **envp)
{
	struct sigaction	sa;
	char				*user_input;
	unsigned char		exit_status;
	t_list				*env_history;

	_connect_to_signals(&sa);
	exit_status = 0;
	env_history = NULL;
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
		_process_command(&user_input, &exit_status, &envp, &env_history);
		free(user_input);
	}
	rl_clear_history();
	ft_lstclear(&env_history, free);
	free_args(envp);
	return (EXIT_SUCCESS);
}

char	**cpy_envp(char	**envp)
{
	char	**new_envp;
	size_t		count;
	size_t		i;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}
