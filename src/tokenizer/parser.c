/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:41:08 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/02 18:35:13 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "structs.h"
#include "parser.h"

static void	_print_cmd(t_command *cmd)
{
	size_t	i;

	i = 0;
	printf("executing program: %s\n", cmd->program);
	printf("with arguments:\n");
	while (cmd->args[i])
	{
		printf("\t%s\n", cmd->args[i]);
		++i;
	}
	printf("to output: %u\n", cmd->output);
}

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

static char	**_init_args(t_token **tokens)
{
	char	**args;
	t_token *current;
	size_t	i;
	size_t	size;

	size = 0;
	current = *tokens;
	while (current && !_is_operator(current->type))
	{
		++size;
		current = current->next;
	}
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
	current = current->next;
	cmd->args = _init_args(&current);
	cmd->output = _set_output(&current);
	if (!cmd->program || !cmd->args)
	{
		free_cmd(cmd);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(cmd_list, ft_lstnew(cmd));
	return (EXIT_SUCCESS);
}

int	parser(t_token *tokens)
{
	t_token *current;
	t_list	*cmd_list;

	cmd_list = NULL;
	current = tokens;
	if (!tokens)
		return (EXIT_SUCCESS);
	if (_init_cmd(&cmd_list, &current))
		return (EXIT_FAILURE);
	_print_cmd(cmd_list->content);
	ft_lstclear(&cmd_list, free_cmd);
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
