/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:15:25 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/20 15:15:31 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stddef.h>

/** Converts the enum to its string literal. (for debugging)
 *
 *	@param type: 	The enum type.
 *
 *	@returns:		The name of the enum as string.
 */
char	*token_type_to_string(enum e_token_type type)
{
	if (type == TOKEN_LITERAL)
		return ("TOKEN_LITERAL");
	else if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	else if (type == TOKEN_HERE_DOC)
		return ("TOKEN_HERE_DOC");
	else if (type == TOKEN_REDIRECT_OUT_APPEND)
		return ("TOKEN_REDIRECT_OUT_APPEND");
	else if (type == TOKEN_ENVIRONMENT_VARIABLES)
		return ("TOKEN_ENVIRONMENT_VARIABLES");
	else if (type == TOKEN_EXIT_STATUS)
		return ("TOKEN_EXIT_STATUS");
	return (NULL);
}
