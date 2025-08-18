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

/**
 * - Does sorting for 5 or less size
 * - Contains hardcoded algorithms
 */
void	small_sort(t_stack **stack_a, t_stack **stack_b, int size)
{
	t_stack	*cursor;

	cursor = *stack_a;
	if (size == 2 && cursor->correct_idx < cursor->next->correct_idx)
		do_sa(stack_a);
	else if (size == 3)
	{
		if
	}
	else if (size == 4)
		sort_four();
	else if (size == 5)
		sort_five();
}

/**
 * - Does sorting for more than 5 size
 * - Contains radix as main logic
 */
void	large_sort(t_stack **stack_a, t_stack **stack_b, int size)
{

}

/**
 * - Does the sorting
 */
void	do_push_swap(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = get_stack_size(stack_a);
	if (size <= 5)
		small_sort(stack_a, stack_b, size);
	else
		large_sort(stack_a, stack_b, size);
}
