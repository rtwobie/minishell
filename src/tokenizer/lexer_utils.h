/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:01:53 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/23 18:03:14 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

enum e_state
{
	START,
	WHITESPACE,
	IN_SINGLE_QUOTES,
	IN_DOUBLE_QUOTES,
	IN_PIPE_OPERATOR,
	IN_OUTPUT_OPERATOR,
	IN_INPUT_OPERATOR,
	WORD,
	END,
};

int	ft_isoperator(char c);
int	ft_isword(char c);

#endif // !LEXER_UTILS_H
