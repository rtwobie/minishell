/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:27:57 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/20 17:40:10 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "builtin.h"
#include "libft.h"
#include "error.h"
#include "run.h"

static int	_check_executable(char *exec_path)
{
	struct stat	sb;

	if (stat(exec_path, &sb) == -1)
		return (127);
	if (S_ISDIR(sb.st_mode))
		return (errno = EISDIR, 126);
	if (!S_ISREG(sb.st_mode))
		return (127);
	if (access(exec_path, X_OK) == -1)
		return (errno = EACCES, 126);
	return (EXIT_SUCCESS);
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

	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		executable_path = _strjoin_path(path_dirs[i], program);
		if (!executable_path)
			return (free_args(path_dirs), NULL);
		if (_check_executable(executable_path) == EXIT_SUCCESS)
			return (free_args(path_dirs), executable_path);
		free(executable_path);
		++i;
	}
	free_args(path_dirs);
	return (ft_strdup(program));
}

int	search_program(char *lookup, char **program, char **envp)
{
	char		*path_env;
	int			status;

	if (ft_strchr(lookup, '/'))
	{
		status = _check_executable(lookup);
		if (status)
			return (perror(lookup), status);
		*program = ft_strdup(lookup);
		if (!*program)
			return (perror("malloc"), EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	path_env = ft_getenv(envp, "PATH");
	*program = _set_executable_path(lookup, path_env);
	if (!*program)
		return (print_err(ERR_CMD_NOTFOUND, lookup), EXIT_FAILURE);
	status = _check_executable(*program);
	if (status)
	{
		print_err(ERR_CMD_NOTFOUND, *program);
		free(*program);
		return (status);
	}
	return (EXIT_SUCCESS);
}
