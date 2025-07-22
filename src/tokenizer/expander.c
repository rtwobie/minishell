/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:31:43 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/19 18:33:10 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "tokenizer.h"

static int	_reedit(t_token **tokens)
{
	char	*new_value;
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_SINGLE_QUOTES)
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
	// expand variables
	// condense TOKEN_SINGLE_QUOTES and TOKEN_DOUBLE_QUOTES to TOKEN_LITERAL
	return (EXIT_SUCCESS);
}
