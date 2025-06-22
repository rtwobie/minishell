/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:21:50 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/20 23:50:33 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum e_state
{
	START,
	WHITESPACE,
	IN_SINGLE_QUOTES,
	IN_DOUBLE_QUOTES,
	OPERATOR,
	WORD,
	END,
};

void	lexer(char *user_input);

#endif // !STRUCTS_H
