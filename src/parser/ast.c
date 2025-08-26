/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:38:24 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/26 16:45:01 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "parser_internal.h"
#include "run.h"
#include <stdlib.h>

char	**_arglist_to_strarr(t_list **arg_list)
{
	size_t	i;
	size_t	size;
	t_list	*current;
	char	**args;

	current = *arg_list;
	size = (size_t)ft_lstsize(current);
	args = ft_calloc(size + 1, sizeof(*args));
	if (!args)
		return (NULL);
	i = 0;
	while (i < size)
	{
		args[i] = ft_strdup(current->content);
		if (!args[i])
		{
			free_args(args);
			ft_lstclear(arg_list, free);
			return (NULL);
		}
		++i;
		current = current->next;
	}
	ft_lstclear(arg_list, free);
	return (args);
}

t_redir_node	*_create_redirection_node(t_token *token)
{
	t_redir_node	*node;

	if (!_is_redirection(token->type))
		return (NULL);
	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->filename = ft_strdup(token->value);
	if (!node->filename)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_ast_node	*_create_command_node(char **args, t_list **redirects)
{
	t_ast_node		*node;
	t_command_node	*cmd_data;

	cmd_data = malloc(sizeof(*cmd_data));
	if (!cmd_data)
		return (NULL);
	node = ft_calloc(1, sizeof(*node));
	if (!node)
	{
		free_args(args);
		ft_lstclear(redirects, free_redir);
		return (NULL);
	}
	cmd_data->argv = args;
	cmd_data->redir = *redirects;
	node->data.command = cmd_data;
	node->type = NODE_TYPE_COMMAND;
	return (node);
}

t_pipe_node	*_init_pipe_data(t_ast_node *left_node, t_ast_node *right_node)
{
	t_pipe_node	*pipe;

	pipe = ft_calloc(1, sizeof(*pipe));
	if (!pipe)
		return (NULL);
	pipe->left = left_node;
	pipe->right = right_node;
	return (pipe);
}

t_ast_node	*_create_ast_node(t_nodetype type, void *data)
{
	t_ast_node	*node;

	if (!data)
		return (NULL);
	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->type = type;
	if (node->type == NODE_TYPE_COMMAND)
		node->data.command = (t_command_node *)data;
	else if (node->type == NODE_TYPE_PIPE)
		node->data.pipe = (t_pipe_node *)data;
	return (node);
}
