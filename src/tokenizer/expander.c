/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:31:43 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/29 16:37:21 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "structs.h"

static int	_is_operator(enum e_token_type type)
{
	return (
		type == TOKEN_PIPE || \
		type == TOKEN_REDIRECT_IN || \
		type == TOKEN_REDIRECT_OUT || \
		type == TOKEN_HERE_DOC || \
		type == TOKEN_REDIRECT_OUT_APPEND
	);
}

static int	_reedit(t_token **tokens)
{
	char	*new_value;
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (_is_operator(current->type))
		{
			free(current->value);
			current->value = NULL;
		}
		else if (current->type == TOKEN_SINGLE_QUOTES)
		{
			new_value = ft_strtrim(current->value, "\'");
			if (!new_value)
				return (EXIT_FAILURE);
			free(current->value);
			current->value = new_value;
		}
		else if (current->type == TOKEN_DOUBLE_QUOTES)
		{
			new_value = ft_strtrim(current->value, "\"");
			if (!new_value)
				return (EXIT_FAILURE);
			free(current->value);
			current->value = new_value;
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

// static int	_expand(t_token **tokens)
// {
// 	t_token *current;
//
// 	current = *tokens;
//
//
// 	if (current->type == TOKEN_LITERAL || current->type == TOKEN_DOUBLE_QUOTES)
// 	{
// 		size_t	i;
//
// 		i = 0;
// 		while (current->value[i])
// 		{
// 			++i;
// 		}
// 		// TODO:	get the variable after $
// 		//			best approach might be to read str and write new one at the same time
// 		//			so first read str for $
// 		//			then read again and write
// 		//			when $ found then save getenv(variable) into string
// 		//			write expandion into the new string
// 		//			repeat until end of string
// 	}
//
// 	return (EXIT_SUCCESS);
// }

int	expander(t_token **tokens)
{
	if (_reedit(tokens))
		return (EXIT_FAILURE);
	// if (_expand(tokens))
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
