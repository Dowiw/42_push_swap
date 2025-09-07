/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:15:18 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/21 09:19:46 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <limits.h>
#include <stdlib.h>

/**
 * - For every target in stack a from position b:
 * 	find the moves taken for ra/rra and rb/rrb
 */
t_moves	calculate_moves(int target_a, int pos_b, int size_a, int size_b)
{
	t_moves	temp;
	int		moves_a;
	int		moves_b;
	int		common;

	moves_a = 0;
	moves_b = 0;
	common = 0;
	if (target_a <= size_a / 2)
		moves_a = target_a;
	else
		moves_a = target_a - size_a;
	if (pos_b <= size_b / 2)
		moves_b = pos_b;
	else
		moves_b = pos_b - size_b;
	if (moves_a > 0 && moves_b > 0)
		common = (moves_a < moves_b) * moves_a + (moves_a >= moves_b) * moves_b;
	else if (moves_a < 0 && moves_b < 0)
		common = (moves_a > moves_b) * moves_a + (moves_a <= moves_b) * moves_b;
	temp.total_moves = ft_abs(moves_a) + ft_abs(moves_b) - ft_abs(common);
	temp.both = common;
	temp.rotates_a = moves_a;
	temp.rotates_b = moves_b;
	return (temp);
}

/**
 * - Find the best move for all numbers in stack b
 * - Use Turk heart of determining ra_rb, rra_rrb, ra_rrb, rra_rb
 */
t_moves	find_best_moves(t_stack **a, t_stack **b)
{
	int		target_a;
	int		pos;
	t_moves	best;
	t_moves	temp;
	t_stack	*current;

	pos = 0;
	best.rotates_b = 0;
	best.rotates_a = 0;
	best.both = 0;
	best.total_moves = INT_MAX;
	current = *b;
	while (current)
	{
		target_a = find_target_pos_a(a, current->number);
		temp = calculate_moves(target_a, pos, stack_size(a), stack_size(b));
		if (temp.total_moves < best.total_moves)
			best = temp;
		pos++;
		current = current->next;
	}
	return (best);
}

/**
 * - Perform Turk when pushing back to a
 */
void	push_back_to_a(t_stack **a, t_stack **b)
{
	int		i;
	int		min_pos;
	t_moves	best_moves;

	while (stack_size(b) > 0)
	{
		best_moves = find_best_moves(a, b);
		execute_moves(&best_moves, a, b);
		do_pa(b, a);
	}
	min_pos = find_min_pos(a);
	i = 0;
	if (min_pos <= stack_size(a) / 2)
	{
		while (i++ < min_pos)
			do_ra(a, 1);
	}
	else
	{
		while (i++ < stack_size(a) - min_pos)
			do_rra(a, 1);
	}
}

/**
 * - Heart
 * - Logic to stack a: if a number is below i then put bottom
 * 	else if, between i and gap, put the number on top
 * 	else if, most of the remaining nums in a are descending, do rra
 * 	else, ra
 */
void	large_sort(t_stack **a, t_stack **b)
{
	int				gap;
	unsigned int	i;

	i = 0;
	gap = 100;
	while (stack_size(a) > 1)
	{
		if ((*a)->correct_idx <= i)
		{
			do_pb(a, b);
			do_rb(b, 1);
			i++;
		}
		else if ((*a)->correct_idx <= i + gap)
		{
			do_pb(a, b);
			i++;
		}
		else if (check_opposite(a))
			do_rra(a, 1);
		else
			do_ra(a, 1);
	}
	push_back_to_a(a, b);
}

/**
 * - Does the sorting
 */
void	do_push_swap(t_stack **a, t_stack **b)
{
	int		size;
	t_stack	*cursor;

	if (is_sorted(a))
		return ;
	size = stack_size(a);
	cursor = *a;
	if (size == 2 && cursor->correct_idx > cursor->next->correct_idx)
		do_sa(a, 1);
	else if (size == 3)
		sort_three(a);
	else if (size == 4)
		sort_four(a, b);
	else if (size == 5)
		sort_five(a, b);
	else
		large_sort(a, b);
}
