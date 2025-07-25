/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:06:58 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/23 16:13:26 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"

void	free_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		++i;
	}
	free(args);
}

void	free_redir(void *content)
{
	t_redirection_node	*redir;

	redir = (t_redirection_node *)content;
	free(redir->filename);
	free(redir);
}

void	free_command_node(t_command_node *node)
{
	ft_lstclear(&node->redir, free_redir);
	free_args(node->program_argv);
	free(node);
}

void	cleanup_ast(t_ast_node **ast)
{
	if (!*ast)
		return ;
	if ((*ast)->type == NODE_TYPE_COMMAND)
		free_command_node((*ast)->data.command_node);
	else if ((*ast)->type == NODE_TYPE_PIPE)
	{
		if ((*ast)->data.pipe_node)
		{
			cleanup_ast(&(*ast)->data.pipe_node->left);
			cleanup_ast(&(*ast)->data.pipe_node->right);
			free((*ast)->data.pipe_node);
		}

	}
	free(*ast);
}
