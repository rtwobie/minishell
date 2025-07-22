/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:38:24 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/22 19:44:52 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_internal.h"

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
		node->data.command_node = (t_command_node *)data;
	else if (node->type == NODE_TYPE_PIPE)
		node->data.pipe_node = (t_pipe_node *)data;
	return (node);
}
