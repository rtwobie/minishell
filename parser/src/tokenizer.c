/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:28:09 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/28 20:24:35 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static int	_skip_whitespace(const char *user_input, size_t	iterator)
{
	while (user_input[iterator])
		++iterator;
	return (iterator);
}

void	read_input(const char *user_input)
{
	size_t	i;

	i = 0
	while (user_input[i])
	{
		_skip_whitespace(user_input, i);
	}
}
