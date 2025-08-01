/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:09:07 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/30 17:44:17 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_token t_token;

int	heredoc_test(t_token **tokens);

#endif // !HEREDOC_H
