/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:17:55 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/26 18:18:11 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "structs.h"
#include "token_list.h"

static enum e_token_type	_get_token_type(char *value)
{
	if (!ft_strcmp(value, "exit"))
		return (TOKEN_EXIT_STATUS);
	else if (!ft_strcmp(value, "|"))
		return (TOKEN_PIPE);
	else if (!ft_strcmp(value, "<"))
		return (TOKEN_REDIRECT_IN);
	else if (!ft_strcmp(value, ">"))
		return (TOKEN_REDIRECT_OUT);
	else if (!ft_strcmp(value, ">>"))
		return (TOKEN_REDIRECT_OUT_APPEND);
	else if (!ft_strcmp(value, "<<"))
		return (TOKEN_HERE_DOC);
	else if (value[0] == '\'')
		return (TOKEN_SINGLE_QUOTES);
	else if (value[0] == '\"')
		return (TOKEN_DOUBLE_QUOTES);
	return (TOKEN_LITERAL);
}

int	save_token(char *str, size_t size, t_token **tokens)
{
	char	*value;

	value = malloc((size + 1) * (sizeof(*value)));
	if (!value)
		return (EXIT_FAILURE);
	ft_strlcpy(value, str, size + 1);
	add_token(tokens, new_token(_get_token_type(value), value));
	free(value);
	return (EXIT_SUCCESS);
}
