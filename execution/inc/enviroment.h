/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:33:13 by mmagrin           #+#    #+#             */
/*   Updated: 2025/05/27 17:01:16 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

/*enviroment*/
t_env	**ft_init_env(char *envp[]);
t_env	*ft_create_node(void *content);
/*env_utils*/
char	*ft_extract_key(char *env_str);
char	*ft_extract_value(char *env_str);
int		ft_strch_i(char *str, char c);
void	ft_env_add_back(t_env **env, t_env *new);

#endif
