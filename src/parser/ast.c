/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:38:24 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/19 15:44:34 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_internal.h"

t_ast_node	*create_ast_node(t_nodetype type, union u_node data)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->type = type;
	node->data.
}
