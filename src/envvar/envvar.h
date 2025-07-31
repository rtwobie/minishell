#ifndef ENVVAR_H
# define ENVVAR_H

# include <stdlib.h>
# include "error.h"
# include "libft.h"
# include "tokenizer.h"


void	envvar(t_token **tokens);
char	*_use_getent(char *idx, size_t i);
int	_get_env_tok(char **idx);


#endif
