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

#include <stdio.h>

typedef struct s_cost
{
	int		r_r;
	int		total_rr;
	int		ra_rrb;
	int		total_ra_rrb;
	int		rra_rb;
	int		total_rra_rb;
	int		rr_rr;
	int		total_rrr;
	int		rotates_a;
	int		rotates_b;
	int		best_cost;
}			t_cost;

// Find the position where a value should be inserted in stack B (descending order)
static int	find_target_pos_b(t_stack **stack_b, int value)
{
	t_stack	*current;
	int		pos;
	int		best_pos;
	int		max_smaller;
	int		max_pos;
	int		max_val;

	if (!*stack_b)
		return (0);
	current = *stack_b;
	pos = 0;
	best_pos = 0;
	max_smaller = INT_MIN;
	max_pos = 0;
	max_val = INT_MIN;
	while (current)
	{
		if (current->number < value && current->number > max_smaller)
		{
			max_smaller = current->number;
			best_pos = (pos + 1) % get_stack_size(stack_b);
		}
		if (current->number > max_val)
		{
			max_val = current->number;
			max_pos = (pos + 1) % get_stack_size(stack_b);
		}
		current = current->next;
		pos++;
	}
	return (max_smaller == INT_MIN) ? max_pos : best_pos;
}

// Find the position where a value should be inserted in stack A (ascending order)
static int	find_target_pos_a(t_stack **stack_a, int value)
{
	t_stack	*current;
	int		pos;
	int		best_pos;
	int		min_larger;
	int		min_pos;
	int		min_val;

	if (!*stack_a)
		return (0);
	current = *stack_a;
	pos = 0;
	best_pos = 0;
	min_larger = INT_MAX;
	min_pos = 0;
	min_val = INT_MAX;
	while (current)
	{
		if (current->number > value && current->number < min_larger)
		{
			min_larger = current->number;
			best_pos = pos;
		}
		if (current->number < min_val)
		{
			min_val = current->number;
			min_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (min_larger == INT_MAX) ? min_pos : best_pos;
}

// Get minimum cost of all totals
static int	get_min(t_cost *cost)
{
	int	total_rrr;
	int	total_rr;
	int	total_ra_rrb;
	int	total_rra_rb;
	int	min;

	total_rr = cost->total_rr;
	total_rrr = cost->total_rrr;
	total_ra_rrb = cost->total_ra_rrb;
	total_rra_rb = cost->total_rra_rb;
	min = total_rr;
	min = (total_rrr < min) * total_rrr + (total_rrr >= min) * min;
	min = (total_ra_rrb < min) * total_ra_rrb + (total_ra_rrb >= min) * min;
	min = (total_rra_rb < min) * total_rra_rb + (total_rra_rb >= min) * min;
	return (min);
}

// Calculate cost to move element at given position to target position
static t_cost	calculate_move_cost(int pos_a, int pos_b, int size_a, int size_b)
{
	int		ra;
	int		rra;
	int		rb;
	int		rrb;
	t_cost	cost;

	ra = pos_a;
	rra = size_a - pos_a;
	rb = pos_b;
	rrb = size_b - pos_b;
	cost.r_r = (ra < rb) * ra + (rb <= ra) * rb;
	cost.total_rr = (ra - cost.r_r) + (rb - cost.r_r) + cost.r_r;
	cost.rr_rr = (rra < rrb) * rra + (rrb <= rra) * rrb;
	cost.total_rrr = (rra - cost.rr_rr) + (rrb - cost.rr_rr) + cost.rr_rr;
	cost.total_ra_rrb = ra + rrb;
	cost.total_rra_rb = rra + rb;
	cost.best_cost = get_min(&cost);
	cost.rotates_a = (pos_a <= size_a / 2) * pos_a + (pos_a > size_a / 2) * (pos_a - size_a);
	cost.rotates_b = (pos_b <= size_b / 2) * pos_b + (pos_b > size_b / 2) * (pos_b - size_b);
	return (cost);
}

// Find the cheapest element to move from stack A to stack B
static t_cost	find_cheapest_move(t_stack **a, t_stack **b)
{
	int		pos_a;
	int		target_b;
	int		size_a;
	int		size_b;
	t_stack	*current;
	t_cost	current_cost;
	t_cost	best_cost;

	pos_a = 0;
	size_a = get_stack_size(a);
	size_b = get_stack_size(b);
	current = *a;
	best_cost.best_cost = INT_MAX;
	while (current)
	{
		target_b = find_target_pos_b(b, current->number);
		current_cost = calculate_move_cost(pos_a, target_b, size_a, size_b);
		if (current_cost.best_cost < best_cost.best_cost)
			best_cost = current_cost;
		current = current->next;
		pos_a++;
	}
	return (best_cost);
}

static void	remaining_rots(t_stack **a, t_stack **b, int rot_a, int rot_b)
{
	while (rot_a > 0)
	{
		do_ra(a, 1);
		rot_a--;
	}
	while (rot_a < 0)
	{
		do_rra(a, 1);
		rot_a++;
	}
	while (rot_b > 0)
	{
		do_rb(b, 1);
		rot_b--;
	}
	while (rot_b < 0)
	{
		do_rrb(b, 1);
		rot_b++;
	}
}

// Execute rotations to bring element to top of stack A and target position to top of stack B
static void	execute_rotations(t_stack **stack_a, t_stack **stack_b, t_cost *best_cost)
{
	int	rr_both;
	int	rrr_both;
	int	rot_a;
	int	rot_b;

	rot_a = best_cost->rotates_a;
	rot_b = best_cost->rotates_b;
	rr_both = (rot_a < rot_b) * rot_a + (rot_b >= rot_a) * rot_b;
	rrr_both = (-rot_a < -rot_b) * -rot_a + (-rot_b >= -rot_a) * -rot_b;
	while (rr_both-- > 0)
	{
		do_rr(stack_a, stack_b);
		rot_a--;
		rot_b--;
	}
	while (rrr_both-- > 0)
	{
		do_rrr(stack_a, stack_b);
		rot_a++;
		rot_b++;
	}
	remaining_rots(stack_a, stack_b, rot_a, rot_b);
}

// Optimized: Move elements back from stack B to stack A in correct positions
static void	push_back_to_a(t_stack **stack_a, t_stack **stack_b)
{
	int	target_pos;
	int	size_a;

	while (*stack_b)
	{
		target_pos = find_target_pos_a(stack_a, (*stack_b)->number);
		size_a = get_stack_size(stack_a);
		if (target_pos > 0)
		{
			if (target_pos <= size_a / 2)
			{
				while (target_pos > 0)
				{
					do_ra(stack_a, 1);
					target_pos--;
				}
			}
			else
			{
				while (target_pos < size_a)
				{
					do_rra(stack_a, 1);
					target_pos++;
				}
			}
		}
		do_pa(stack_b, stack_a);
	}
}

// Bring minimum element to top of stack A
static void	final_rotation(t_stack **stack_a)
{
	int		size;
	int		smallest_idx;
	t_stack	*smallest_node;
	t_stack	*cursor;

	size = get_stack_size(stack_a);
	smallest_idx = 0;
	smallest_node = get_smallest(stack_a);
	cursor = *stack_a;
	while (cursor && cursor != smallest_node)
	{
		smallest_idx++;
		cursor = cursor->next;
	}
	if (smallest_idx <= size / 2)
	{
		while (smallest_idx-- > 0)
			do_ra(stack_a, 1);
	}
	else
	{
		while (size - smallest_idx++ > 0)
			do_rra(stack_a, 1);
	}
}

/**
 * - Heart of the algorithm
 * - Inspired by Mechanical Turk with improvements
 */
void	large_sort(t_stack **stack_a, t_stack **stack_b)
{
	t_cost	best_cost;

	while (get_stack_size(stack_a) > 3)
	{
		best_cost = find_cheapest_move(stack_a, stack_b);
		if (best_cost.best_cost != 0)
			execute_rotations(stack_a, stack_b, &best_cost);
		do_pb(stack_a, stack_b);
	}
	sort_three(stack_a);
	push_back_to_a(stack_a, stack_b);
	final_rotation(stack_a);
}

/**
 * - Checks if stack is sorted
 */
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
		large_sort(stack_a, stack_b);
}
