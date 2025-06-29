/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:14:32 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/29 15:38:09 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum e_token_type
{
	TOKEN_LITERAL,
	TOKEN_SINGLE_QUOTES,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HERE_DOC,
	TOKEN_REDIRECT_OUT_APPEND,
	TOKEN_ENVIRONMENT_VARIABLES,
	TOKEN_EXIT_STATUS,
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}	t_token;

#endif // !STRUCTS_H
