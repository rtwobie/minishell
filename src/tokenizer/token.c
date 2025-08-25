/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:17:55 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/22 16:55:50 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "tokenizer_internal.h"
#include "tokenizer.h"

int	save_token(t_token **list, char *str, size_t size, enum e_token_type type)
{
	char	*value;

	value = malloc((size + 1) * (sizeof(*value)));
	if (!value)
		return (EXIT_FAILURE);
	ft_strlcpy(value, str, size + 1);
	add_token(list, new_token(type, value));
	free(value);
	return (EXIT_SUCCESS);
}
