/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:15:18 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/20 16:37:25 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <unistd.h>
#include <limits.h>

/**
 * - Does sorting for more than 5 size
 * - Contains radix as main logic
 */
void	large_sort(t_stack **a, t_stack **b, int size)
{

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
	if (size == 2 && cursor->correct_idx > cursor->next->correct_idx)
		do_sa(stack_a, 1);
	else if (size == 3)
		sort_three(stack_a);
	else if (size == 4)
		sort_four(stack_a, stack_b);
	else if (size == 5)
		sort_five(stack_a, stack_b);
	else
		large_sort(stack_a, stack_b, size);
}
