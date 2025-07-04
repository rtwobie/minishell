/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:41:21 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/25 20:16:58 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

t_token	*new_token(enum e_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

t_token	*get_last_token(t_token *lst)
{
	while (lst != NULL)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	add_token(t_token **lst, t_token *token)
{
	if (*lst == NULL)
		*lst = token;
	else
		get_last_token(*lst)->next = token;
}

void	free_tokens(t_token **lst)
{
	t_token	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = temp->next;
		free(temp->value);
		free(temp);
	}
	*lst = NULL;
}
