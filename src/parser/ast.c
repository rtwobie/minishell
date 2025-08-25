/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:38:24 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/20 18:08:45 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
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
		node->data.command = (t_command_node *)data;
	else if (node->type == NODE_TYPE_PIPE)
		node->data.pipe = (t_pipe_node *)data;
	return (node);
}
