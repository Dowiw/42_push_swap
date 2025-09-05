/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:15:31 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/12 10:15:32 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * - Checks if character is a digit
 * - `c >= '0' && c <= '9'`
 */
int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * - Checks if character is a sign
 * - `c == '+' || c == '-'`
 */
int	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

/**
 * - Checks if stack is sorted
 */
int	is_sorted(t_stack **a)
{
	t_stack	*cursor;

	cursor = *a;
	while (cursor != NULL && cursor->next != NULL)
	{
		if (cursor->correct_idx > cursor->next->correct_idx)
			return (0);
		cursor = cursor->next;
	}
	return (1);
}

/**
 * - Function that writes `"Error\n"` to STDERR.
 * - Frees the allocated stacks.
 * - End: terminates the program with `exit(EXIT_FAILURE)`
 */
void	error_free_exit(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*cursor;

	cursor = NULL;
	while (stack_a && *stack_a)
	{
		cursor = (*stack_a)->next;
		free(*stack_a);
		*stack_a = cursor;
	}
	while (stack_b && *stack_b)
	{
		cursor = (*stack_b)->next;
		free(*stack_b);
		*stack_b = cursor;
	}
	write(STDERR_FILENO, "Error\n", 6);
	exit(1);
}
