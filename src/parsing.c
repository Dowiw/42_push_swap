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
#include <unistd.h>
#include <limits.h>

/**
 * - Function that fills up stack A
 * - Uses parsing each arg (multiple and single)
 */
void	fill_stack_a(t_stack **stack_a, int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!parse_and_push(stack_a, av[i], &j))
				j++;
		}
		i++;
	}
	if (*stack_a && stack_a)
		get_index(stack_a);
}

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

/**
 * - Parses string to numbers
 * - Checks for int_min & int_max
 * - Uses j index from stack_a filler
 */
int	parse_and_push(t_stack **stack_a, char *s, int *j)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	while (s[*j] == ' ')
		(*j)++;
	if (s[*j] == '-' || s[*j] == '+')
	{
		if (s[*j] == '-')
			sign *= -1;
		(*j)++;
	}
	if (ft_isdigit(s[*j]))
	{
		while (ft_isdigit(s[*j]))
			num = num * 10 + (s[(*j)++] - '0');
		num *= sign;
		if (num < INT_MIN || num > INT_MAX)
			error_free_exit(stack_a, NULL);
		check_and_alloc(stack_a, num);
		return (1);
	}
	return (0);
}

/**
 * - Check if there are duplicates before allocating
 * - Allocates node if none (protected)
 */
void	check_and_alloc(t_stack **stack_a, int num)
{
	t_stack	*node;
	t_stack	*cursor;

	cursor = *stack_a;
	while (cursor != NULL)
	{
		if (cursor->number == num)
			error_free_exit(stack_a, NULL);
		cursor = cursor->next;
	}
	if (!(stack_a && *stack_a))
		node = stack_new_node(num, NULL);
	else
	{
		cursor = *stack_a;
		while (cursor->next != NULL)
			cursor = cursor->next;
		node = stack_new_node(num, cursor);
	}
	if (!node)
		error_free_exit(stack_a, NULL);
	stack_push_bottom(stack_a, node);
}
