/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:48:59 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/22 19:20:00 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenizer_internal.h"

int	ft_isoperator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	ft_isword(unsigned char c)
{
	if (c == '\"' || c == '\'' || c == '|' || c == '<' || c == '>')
		return (0);
	else if (c > 32 && c != 127)
		return (1);
	return (0);
}

char	*_skip_whitespace(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			break ;
		++str;
	}
	return (str);
}

enum e_state	_check_state(char c)
{
	enum e_state	state;

	state = 0;
	if (ft_isspace(c))
		state = WHITESPACE;
	else if (c == '\'')
		state = IN_SINGLE_QUOTES;
	else if (c == '\"')
		state = IN_DOUBLE_QUOTES;
	else if (c == '|' || c == '>' || c == '<')
		state = IN_OPERATOR;
	else if (c == '\0')
		state = END;
	else if (ft_isword((unsigned char)c))
		state = WORD;
	return (state);
}
