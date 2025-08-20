/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:09:07 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/20 18:10:59 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# define HDOCDIR "./minihdoc_"

typedef struct s_token	t_token;

int	heredoc(t_token **tokens, unsigned char *exit_status);
int	cleanup_hdoc(t_token **tokens);
int	hdoc_envvar(char **input, unsigned int skip, unsigned char *exit_status);

#endif // !HEREDOC_H
