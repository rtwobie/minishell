/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:01:23 by rtwobie           #+#    #+#             */
/*   Updated: 2025/09/11 16:02:21 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "tokenizer.h"

# define HDOCDIR "./minihdoc_"

int	heredoc(t_token **tokens, unsigned char *exit_status, char **envp);
int	cleanup_hdoc(t_token **tokens);
int	hdoc_envvar(char **input, unsigned int skip, unsigned char *exit_status,
		char **envp);

#endif // !HEREDOC_H
