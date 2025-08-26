/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:36:35 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/26 16:51:19 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "run.h"
#include "tokenizer.h"

char	*match(t_token **token_ptr, enum e_token_type expected_token)
{
	t_token	*current;

	current = *token_ptr;
	if (current->type != expected_token)
		return (NULL);
	else
		*token_ptr = current->next;
	return (current->value);
}

int	_free_on_error(t_list **arg_list, t_list **redirects)
{
	ft_lstclear(arg_list, free);
	ft_lstclear(redirects, free_redir);
	return (EXIT_FAILURE);
}
