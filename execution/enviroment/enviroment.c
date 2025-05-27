/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:34:23 by mmagrin           #+#    #+#             */
/*   Updated: 2025/05/27 16:14:51 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

t_env	*ft_create_node(t_env **env, void *content);
char	*ft_extract_key(char *env_str);
char	*ft_extract_value(char *env_str, char *key);

t_env	**ft_init_env(char *envp[])
{
	int		i;
	t_env	**env;
	t_env	*new;

	env = malloc(sizeof(t_env *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new = ft_create_node(env, envp[i]);
		new->next = *env;
		*env = new;
		i++;
	}
	return (env);
}

t_env	*ft_create_node(t_env **env, void *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_extract_key(content);
	new_node->value = ft_extract_value(content, new_node->key);
	new_node->next = NULL;
	return (new_node);
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

char	*ft_extract_value(char *env_str, char *key)
{
	char	*value;
	char	*

	value = ft_strtrim(env_str, key);
	return (value);
}
