/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:27:51 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/27 19:32:02 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	_count_words(const char *s)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			++s;
		if (!*s)
			break ;
		while (*s && !ft_isspace(*s))
			++s;
		++words;
	}
	return (words);
}

static void	*_free_all(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
	return (NULL);
}

char	**tokenize(const char *s)
{
	char	**words;
	char	**start;
	size_t	word_count;
	size_t	word_len;

	word_count = _count_words(s);
	words = malloc(sizeof(*words) * (word_count + 1));
	if (!words)
		return (NULL);
	start = words;
	words[word_count] = NULL;
	while (word_count--)
	{
		while (*s && ft_isspace(*s))
			++s;
		word_len = 0;
		while (s[word_len] && !ft_isspace(s[word_len]))
			++word_len;
		*words = ft_substr(s, 0, word_len);
		if (!*words)
			return (_free_all(start));
		s += word_len;
		++words;
	}
	return (start);
}
