/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:27:57 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/31 19:03:51 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "run.h"

static int	_is_executable(char *exec_path)
{
	struct stat	sb;

	if (stat(exec_path, &sb) == -1)
		return (0);
	if (S_ISDIR(sb.st_mode))
		return (errno = EISDIR, 0);
	if (!S_ISREG(sb.st_mode))
		return (0);
	if (access(exec_path, X_OK) == 0)
		return (1);
	return (0);
}

static char	*_strjoin_path(char	*path, char *program)
{
	char	*program_name;
	char	*full_path;

	program_name = ft_strjoin("/", program);
	if (!program_name)
		return (NULL);
	full_path = ft_strjoin(path, program_name);
	if (!full_path)
		return (free(program_name), NULL);
	free(program_name);
	return (full_path);
}

static char	*_set_executable_path(char *program, char *path_env)
{
	size_t	i;
	char	**path_dirs;
	char	*executable_path;

	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		executable_path = _strjoin_path(path_dirs[i], program);
		if (!executable_path)
			return (free_args(path_dirs), NULL);
		if (_is_executable(executable_path))
			return (free_args(path_dirs), executable_path);
		free(executable_path);
		++i;
	}
	free_args(path_dirs);
	return (ft_strdup(program));
}

char	*search_program(char *program)
{
	char		*path_env;

	if (ft_strchr(program, '/'))
	{
		if (!_is_executable(program))
			return (perror(program), NULL);
		return (ft_strdup(program));
	}
	path_env = getenv("PATH");
	program = _set_executable_path(program, path_env);
	if (!program)
		return (NULL);
	if (!_is_executable(program))
	{
		print_err(ERR_CMD_NOTFOUND, program);
		free(program);
		return (NULL);
	}
	return (program);
}
