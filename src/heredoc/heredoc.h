/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:09:07 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/04 19:00:37 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# define HDOCDIR "./minihdoc_"

typedef struct s_token	t_token;

int	heredoc(t_token **tokens);
int	cleanup_hdoc(t_token **tokens);

#endif // !HEREDOC_H
