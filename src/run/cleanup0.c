/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:06:58 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/26 16:48:52 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "parser.h"

void	free_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		++i;
	}
	free(args);
	args = NULL;
}

void	free_redir(void *content)
{
	t_redir_node	*redir;

	redir = (t_redir_node *)content;
	free(redir->filename);
	free(redir);
}

void	free_command_node(t_command_node *cmd)
{
	ft_lstclear(&cmd->redir, free_redir);
	free_args(cmd->argv);
	free(cmd);
}

void	cleanup_ast(t_ast_node **ast)
{
	if (!*ast)
		return ;
	if ((*ast)->type == NODE_TYPE_COMMAND)
		free_command_node((*ast)->data.command);
	else if ((*ast)->type == NODE_TYPE_PIPE)
	{
		if ((*ast)->data.pipe)
		{
			cleanup_ast(&(*ast)->data.pipe->left);
			cleanup_ast(&(*ast)->data.pipe->right);
			free((*ast)->data.pipe);
		}
	}
	free(*ast);
}
