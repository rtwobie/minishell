/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:39:38 by fgorlich          #+#    #+#             */
/*   Updated: 2025/08/04 21:37:25 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVVAR_H
# define ENVVAR_H

# include <stdlib.h>
# include "tokenizer.h"
# include <stddef.h>
# include <stdlib.h>
# include "error.h"
# include "libft.h"
# include "tokenizer.h"
# include "pipe.h"
# include "tokenizer_internal.h"

int		envvar(t_token **tokens, unsigned int skip);
int		_get_env_tok(char **idx);
char	*_use_getent(char *idx, size_t i);
char	*rm_braces(char **idx, size_t *i);
void	replace_and_exit_envvar(t_token **current);
int		dollars(t_token **tokens, unsigned int *skip, unsigned int *i);

#endif
