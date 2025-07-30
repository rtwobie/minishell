
#include <stdlib.h>
#include "error.h"
#include "libft.h"
#include "tokenizer.h"


void	envvar(t_token **tokens)
{
	const char	*var = (*tokens)->value + 1;
	getenv(var);
}
