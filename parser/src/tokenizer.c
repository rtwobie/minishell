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

void	read_input(const char *user_input)
{
	char	*i;

	i = (char *)user_input;
	while (*i)
	{
		while (*i && ft_isspace(*i))
			++i;
		while (*i
	}
}
