
#include <stddef.h>
#include <stdlib.h>
#include "error.h"
#include "libft.h"
#include "tokenizer.h"
#include "pipe.h"
#include "tokenizer_internal.h"


int	_get_env_tok(char **idx);
char	*_use_getent(char *idx, size_t i);
char	*rm_braces(char **idx, size_t *i);

void	envvar(t_token **tokens)
{
	unsigned int		i;
	char				*temp;
	char				*new;


	i = 0;
	if ((*tokens)->type != TOKEN_DOUBLE_QUOTES && (*tokens)->type != TOKEN_LITERAL)
		return ;
	while ((*tokens)->value[i] && (*tokens)->value[i] != '$')
		++i;
	if ((*tokens)->value[i] == '$')
	{
		temp = ft_substr((*tokens)->value, 0 ,i);
		(*tokens)->value = ft_substr((*tokens)->value, i, ft_strlen((*tokens)->value));
		if (_get_env_tok(&((*tokens)->value)) == EXIT_FAILURE)
			return ;
		new = ft_strjoin(temp, (*tokens)->value);
		free((*tokens)->value);
		(*tokens)->value = new;
	}
}
char	*_use_getent(char *idx, size_t i)
{
	char	*join;
	char	*temp;

	join = getenv(ft_substr(idx, 0, i));
	if (!join)
		perror("ENV VAR not found");
	temp = ft_substr(idx, (unsigned int)i, ft_strlen(idx));
	idx = ft_strjoin(join, temp);
	free(temp);
	return (idx);
}

int	_get_env_tok(char **idx)
{
	size_t		i;

	i = 0;
	if ((*idx)[1] == '{')
		*idx = rm_braces(idx, &i);
	else
	{
		++(*idx);
		while ((*idx)[++i] && (ft_isalnum((*idx)[i]) || (*idx)[i] == '_')) // is enum WORD maybe better
			;
	}
	if (!*idx)
		return (EXIT_FAILURE);
	*idx = _use_getent(*idx, i);
	return (EXIT_SUCCESS);
}

char	*rm_braces(char **idx, size_t *j)
{
	unsigned int	i;
	char		*temp1;
	char		*temp2;

	i = 0;
	while ((*idx)[i] && (*idx)[i] != '}')
		i++;
	if (!(*idx)[i])
			return (perror("Syntax error in env_tok"), NULL); // better error handling needed
	temp1 = ft_substr((*idx), 2, i - 2);
	temp2 = ft_substr((*idx), i + 1, ft_strlen((*idx)) - i);
	*idx = ft_strjoin(temp1, temp2);
	*j = i - 2;
	return (*idx);
}


// ich denke, dass ich einen parser für curly braces implementieren sollte, damit es einheitlicher wird, weniger hardcode hat und weniger spaghetti aussieht.
