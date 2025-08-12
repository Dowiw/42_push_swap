/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:15:00 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/12 10:15:01 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

/**
 * - Checker that looks for valid integers in an arg
 * - Each int: skips space ' ', a sign '+' '-' and digits
 * - Returns 0 if anything else is found
 */
int	is_valid_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] != '\0')
	{
		while (arg[i] == ' ')
			i++;
		if (ft_issign(arg[i]))
			i++;
		if (!ft_isdigit(arg[i]))
			return (0);
		while (ft_isdigit(arg[i]))
			i++;
		if (arg[i] && arg[i] != ' ')
			return (0);
	}
	return (1);
}

/**
 * - Checks for valid arguments in ./push_swap ...
 * - Will check for ./push_swap "" (return error)
 * - Will check each argument ac > 2
 */
int	are_valid_args(char **av)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	if (!av[i])
		return (0);
	while (av[i][j] == ' ')
		j++;
	if (av[i][j] == '\0')
		return (0);
	while (av[i] != NULL)
	{
		if (!is_valid_arg(av[i]))
			return (0);
		i++;
	}
	return (1);
}
