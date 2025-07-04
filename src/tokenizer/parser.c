/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:41:08 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/04 17:26:42 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "libft.h"
#include "structs.h"
#include "parser.h"

static int	_is_operator(enum e_token_type type)
{
	return (
		type == TOKEN_PIPE || \
		type == TOKEN_REDIRECT_IN || \
		type == TOKEN_REDIRECT_OUT || \
		type == TOKEN_HERE_DOC || \
		type == TOKEN_REDIRECT_OUT_APPEND
	);
}

static int	_count_args(t_token *tokens)
{
	int	size;

	size = 0;
	while (tokens && !_is_operator(tokens->type))
	{
		++size;
		tokens = tokens->next;
	}
	return (size);
}

static char	**_init_args(t_token **tokens, size_t size)
{
	char	**args;
	t_token *current;
	size_t	i;

	args = ft_calloc(size + 1, sizeof(*args));
	if (!args)
		return (NULL);
	i = 0;
	current = *tokens;
	while (current && i < size)
	{
		args[i] = ft_strdup(current->value);
		if (!args[i])
			free_args(args);
		++i;
		current = current->next;
	}
	*tokens = current;
	args[i] = NULL;
	return (args);
}

static enum  e_output	_set_output(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	if (!current)
		return (STD_OUT);
	if (current->value)
	{
		current = current->next;
		if (!current)
			return (STD_OUT);
	}
	if (current->type == TOKEN_PIPE)
		return (PIPE_OUT);
	else if (current->type == TOKEN_REDIRECT_OUT)
		return (FILE_OUT);
	else if (current->type == TOKEN_REDIRECT_OUT_APPEND)
		return (FILE_APPEND_OUT);
	return (STD_OUT);
}

static int	_init_cmd(t_list **cmd_list, t_token **tokens)
{
	t_token		*current;
	t_command	*cmd;

	current = *tokens;
	cmd = ft_calloc(1 ,sizeof(*cmd));
	if (!cmd)
		return (EXIT_FAILURE);
	cmd->program = ft_strdup(current->value);
	cmd->argc = _count_args(current);
	cmd->argv = _init_args(&current, (size_t)cmd->argc);
	cmd->output = _set_output(&current);
	if (!cmd->program || !cmd->argv)
	{
		free_cmd(cmd);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(cmd_list, ft_lstnew(cmd));
	return (EXIT_SUCCESS);
}

int	parser(t_list **cmd_list, t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!tokens)
		return (EXIT_SUCCESS);
	if (_init_cmd(cmd_list, &current))
		return (EXIT_FAILURE);
	print_cmd((*cmd_list)->content);
	return (EXIT_SUCCESS);
}

// NOTE: COMMAND STRUCT
// D --> E[Command 1 Structure (Node 1)]
// E --> E1[Program: "echo"]
// E --> E2[Arguments: ["hello", NULL]]
// E --> E3[Output: PIPE]
//
// reads a command
// then arguments until an operator or end of the list is hit
