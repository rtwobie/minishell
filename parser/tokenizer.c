/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:28:09 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/29 20:45:03 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stddef.h>
#include <stdio.h>

static void	_skip_whitespace(const char *user_input, size_t	*iterator)
{
	while (user_input[*iterator] && ft_isspace(user_input[*iterator]))
		++(*iterator);
}

static t_token	_create_token(const char *user_input, size_t *iterator)
{
	t_token token = {0};
	size_t	i;

	i = 0;
	while (user_input[*iterator + i] && ft_isalnum(user_input[*iterator + i]))
		++i;
	if (i)
		ft_strlcpy(token.value, &user_input[*iterator], i);
	token.type = TOKEN_LITERAL;
	return (token);
}

void	read_input(const char *user_input)
{
	t_token tokens[100];
	size_t	i;

	i = 0;
	while (user_input[i])
	{
		_skip_whitespace(user_input, &i);
		tokens[0] = _create_token(user_input, &i);
		++i;
	}
	printf("value = %s\n", tokens[0].value);
}
