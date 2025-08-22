/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:16:50 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 19:20:19 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "run.h"
#include "tokenizer.h"
#include "tokenizer_internal.h"

int	_is_redirection(enum e_token_type type)
{
	return (
		type == TOKEN_REDIRECT_IN || \
		type == TOKEN_REDIRECT_OUT || \
		type == TOKEN_HERE_DOC || \
		type == TOKEN_REDIRECT_OUT_APPEND
	);
}

int	_remove_and_combine(t_token **token_ptr)
{
	char	*combined;
	t_token	*temp;

	temp = (*token_ptr)->next;
	(*token_ptr)->next = (*token_ptr)->next->next;
	free_token(temp);
	if (!(*token_ptr)->next)
		return (EXIT_FAILURE);
	combined = ft_strjoin((*token_ptr)->value, (*token_ptr)->next->value);
	if (!combined)
		return (EXIT_FAILURE);
	free((*token_ptr)->value);
	(*token_ptr)->value = combined;
	temp = (*token_ptr)->next;
	(*token_ptr)->next = (*token_ptr)->next->next;
	free_token(temp);
	return (EXIT_SUCCESS);
}
