/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:40:25 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/29 23:02:34 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

/** Creates a node/token with the specified type and value.
 *
 *	@param type: 	The type of token. (see: --> structs.h)
 *	@param value:	The value of the token as a string.
 *
 *	@returns:		A pointer to a token.
 */
t_token	*create_token(enum e_token_type type, char *value)
{
	t_token *token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token *get_last_token(t_token *head)
{
	t_token *current_token;

	current_token = head;
	while (current_token != NULL && current_token->next != NULL)
		current_token = current_token->next;
	return (current_token);
}

void	add_token_back(t_token **head, enum e_token_type type, char *value)
{
	if (head == NULL)
		*head = create_token(type, value);
	else
		get_last_token(*head)->next = create_token(type, value);
}
