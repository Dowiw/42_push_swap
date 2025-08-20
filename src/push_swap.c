/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:15:18 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/17 17:15:21 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <unistd.h>

/**
 * - Does sorting for more than 5 size
 * - Contains radix as main logic
 */
void	large_sort(t_stack **stack_a, t_stack **stack_b, int size)
{
	int	max_bits;
	int	i;
	int	j;
	int	num;

	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			num = (*stack_a)->correct_idx;
			if (((num >> i) & 1) == 0)
				do_pb(stack_a, stack_b);
			else
				do_ra(stack_a);
			j++;
		}
		while (*stack_b)
			do_pa(stack_a, stack_b);
		i++;
	}
}

int	is_sorted(t_stack **stack_a)
{
	t_stack	*cursor;

	cursor = *stack_a;
	while (cursor != NULL && cursor->next != NULL)
	{
		if (cursor->correct_idx > cursor->next->correct_idx)
			return (0);
		cursor = cursor->next;
	}
	return (1);
}

/**
 * - Does the sorting
 */
void	do_push_swap(t_stack **stack_a, t_stack **stack_b)
{
	int		size;
	t_stack	*cursor;

	if (is_sorted(stack_a))
		return ;
	size = get_stack_size(stack_a);
	cursor = *stack_a;
	if (size == 2 && cursor->correct_idx < cursor->next->correct_idx)
		do_sa(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size == 4)
		sort_four(stack_a, stack_b);
	else if (size == 5)
		sort_five(stack_a, stack_b);
	else
		large_sort(stack_a, stack_b, size);
}
