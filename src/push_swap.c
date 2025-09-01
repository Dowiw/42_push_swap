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
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int find_target_pos_a(t_stack **a, int value)
{
	t_stack *current = *a;
	int pos = 0;

	// If value is less than all, or greater than all, insert before the smallest
	int min = current->number;
	int max = current->number;
	t_stack *tmp = current;
	while (tmp)
	{
		if (tmp->number < min)
			min = tmp->number;
		if (tmp->number > max)
			max = tmp->number;
		tmp = tmp->next;
	}
	if (value < min || value > max)
	{
		// Find position of the smallest value
		tmp = current;
		int min_pos = 0, i = 0;
		while (tmp)
		{
			if (tmp->number == min)
				min_pos = i;
			tmp = tmp->next;
			i++;
		}
		return min_pos;
	}

	// Otherwise, find the first node where current->number > value and previous < value
	while (current && current->next)
	{
		if (current->number < value && current->next->number > value)
			return pos + 1;
		pos++;
		current = current->next;
	}
	return 0; // fallback
}

int find_min_pos(t_stack **a)
{
	t_stack *current = *a;
	int min = current->number;
	int min_pos = 0, i = 0;

	while (current)
	{
		if (current->number < min)
		{
			min = current->number;
			min_pos = i;
		}
		current = current->next;
		i++;
	}
	return min_pos;
}

int get_max_b(t_stack **b)
{
	t_stack *cur = *b;
	int max = cur ? cur->number : INT_MIN;
	while (cur)
	{
		if (cur->number > max)
			max = cur->number;
		cur = cur->next;
	}
	return max;
}

/**
 * - Perform Turk when pushing back to a
 */
void push_back_to_a(t_stack **a, t_stack **b)
{
	while (get_stack_size(b) > 0)
	{
		int min_total_moves = INT_MAX;
		int best_moves_a = 0, best_moves_b = 0, best_common = 0;
		int size_a = get_stack_size(a);
		int size_b = get_stack_size(b);
		int pos = 0;

		// super greedy, get every single move for every single b
		for (t_stack *cur = *b; cur; cur = cur->next, pos++)
		{
			int target_pos_a = find_target_pos_a(a, cur->number);
			int moves_a = (target_pos_a <= size_a / 2) ? target_pos_a : target_pos_a - size_a;
			int moves_b = (pos <= size_b / 2) ? pos : pos - size_b;
			int common = 0;
			if (moves_a > 0 && moves_b > 0)
				common = (moves_a < moves_b) ? moves_a : moves_b;
			else if (moves_a < 0 && moves_b < 0)
				common = (moves_a > moves_b) ? moves_a : moves_b;
			int total_moves = abs(moves_a) + abs(moves_b) - abs(common);
			if (total_moves < min_total_moves)
			{
				min_total_moves = total_moves;
				best_moves_a = moves_a;
				best_moves_b = moves_b;
				best_common = common;
			}
		}

		// Perform common rotations
		while (best_common > 0)
		{
			do_rr(a, b);
			best_moves_a--;
			best_moves_b--;
			best_common--;
		}
		while (best_common < 0)
		{
			do_rrr(a, b);
			best_moves_a++;
			best_moves_b++;
			best_common++;
		}
		// Finish remaining rotations for A
		while (best_moves_a > 0) { do_ra(a, 1); best_moves_a--; }
		while (best_moves_a < 0) { do_rra(a, 1); best_moves_a++; }
		// Finish remaining rotations for B
		while (best_moves_b > 0) { do_rb(b, 1); best_moves_b--; }
		while (best_moves_b < 0) { do_rrb(b, 1); best_moves_b++; }

		// Push from B to A
		do_pa(b, a);
	}

	// Final rotation: bring the smallest value to the top of A
	int min_pos = find_min_pos(a);
	if (min_pos <= get_stack_size(a) / 2)
	{
		for (int i = 0; i < min_pos; i++)
			do_ra(a, 1);
	}
	else
	{
		for (int i = 0; i < get_stack_size(a) - min_pos; i++)
			do_rra(a, 1);
	}
}

int	check_opposite(t_stack *a)
{
	int	s_size;
	int	count;
	int	diff;

	diff = 0;
	count = 0;
	s_size = get_stack_size(&a);
	while (a && a->next)
	{
		diff = a->correct_idx - a->next->correct_idx;
		if (diff == 2 || diff == 3 || diff == 4)
			count++;
		a = a->next;
	}
	if (count * 10 >= s_size * 6)
		return (1);
	return (0);
}

/**
 * - Heart
 */
void	large_sort(t_stack **a, t_stack **b)
{
	unsigned int	i = 0;
	int	range = 37;

	while (get_stack_size(a) > 1)
	{
		if ((*a)->correct_idx <= i)
		{
			do_pb(a, b);
			do_rb(b, 1);
			++i;
		}
		else if ((*a)->correct_idx <= i + range)
		{
			do_pb(a, b);
			++i;
		}
		else if (check_opposite(*a))
			do_rra(a, 1);
		else
			do_ra(a, 1); // about 2200
	}
	push_back_to_a(a, b); // should also be the same
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
	size = get_stack_size(a);
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
