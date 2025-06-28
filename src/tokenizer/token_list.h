/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:56:21 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/25 20:16:52 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "structs.h"

t_token	*new_token(enum e_token_type type, char *value);
t_token	*get_last_token(t_token *lst);
void	add_token(t_token **lst, t_token *token);
void	free_tokens(t_token **lst);
void	print_tokens(t_token *tokens);

#endif // !TOKEN_LIST_H
