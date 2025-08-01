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

int		envvar(t_token **tokens);
int		_get_env_tok(char **idx);
char	*_use_getent(char *idx, size_t i);
char	*rm_braces(char **idx, size_t *i);
void	replace_and_exit_envvar(t_token **current);

#endif
