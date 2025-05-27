/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:48:24 by mmagrin           #+#    #+#             */
/*   Updated: 2025/05/27 17:00:53 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

int	ft_strch_i(char *str, char c)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*ft_extract_key(char *env_str)
{
	int		i;
	char	*key;

	i = ft_strch_i(env_str, '=');
	if (i == -1)
		return (NULL);
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, env_str, i + 1);
	return (key);
}

char	*ft_extract_value(char *env_str)
{
	char	*value;
	char	*ptr;

	ptr = ft_strchr(env_str, '=');
	if (!ptr)
		return (ft_strdup(""));
	value  = ft_strdup(ptr + 1);
	return (value);
}

void	ft_env_add_back(t_env **env, t_env *new)
{
	t_env *curr;

	if (!*env)
	{
		*env = new;
		return;
	}
	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}
