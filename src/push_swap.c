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

// Find the position where a value should be inserted in stack B (descending order)
static int	find_target_pos_b(t_stack **stack_b, int value)
{
	t_stack	*current;
	t_stack	*max_node;
	int		pos;
	int		target_pos;

	if (!*stack_b)
		return (0);

	// Find max value in stack B
	max_node = *stack_b;
	current = *stack_b;
	while (current)
	{
		if (current->number > max_node->number)
			max_node = current;
		current = current->next;
	}

	// If value is bigger than max or smaller than min, place above max
	current = *stack_b;
	pos = 0;
	while (current && current != max_node)
	{
		pos++;
		current = current->next;
	}

	// Check if value fits between existing values (descending order)
	current = *stack_b;
	target_pos = 0;
	while (current && current->next)
	{
		if (value < current->number && value > current->next->number)
			return (target_pos + 1);
		target_pos++;
		current = current->next;
	}

	return (pos); // Place above max
}

// Find the position where a value should be inserted in stack A (ascending order)
static int	find_target_pos_a(t_stack **stack_a, int value)
{
	t_stack	*current;
	t_stack	*min_node;
	int		pos;
	int		target_pos;

	if (!*stack_a)
		return (0);

	// Find min value in stack A
	min_node = *stack_a;
	current = *stack_a;
	while (current)
	{
		if (current->number < min_node->number)
			min_node = current;
		current = current->next;
	}

	// Check if value fits between existing values (ascending order)
	current = *stack_a;
	target_pos = 0;
	while (current && current->next)
	{
		if (value > current->number && value < current->next->number)
			return (target_pos + 1);
		target_pos++;
		current = current->next;
	}

	// If value doesn't fit between, place above min
	current = *stack_a;
	pos = 0;
	while (current && current != min_node)
	{
		pos++;
		current = current->next;
	}

	return (pos);
}

// Calculate cost to move element at given position to target position
static int	calculate_move_cost(int pos, int target_pos, int size_a, int size_b)
{
	int	cost_a;
	int	cost_b;
	int	total_cost;

	// Calculate rotations needed for stack A
	if (pos <= size_a / 2)
		cost_a = pos;
	else
		cost_a = size_a - pos;

	// Calculate rotations needed for stack B
	if (target_pos <= size_b / 2)
		cost_b = target_pos;
	else
		cost_b = size_b - target_pos;

	// Check if we can use simultaneous rotations
	if ((pos <= size_a / 2 && target_pos <= size_b / 2) ||
		(pos > size_a / 2 && target_pos > size_b / 2))
	{
		if (cost_a > cost_b)
			total_cost = cost_a;
		else
			total_cost = cost_b;
	}
	else
		total_cost = cost_a + cost_b;

	return (total_cost + 1); // +1 for the push operation
}

// Find the cheapest element to move from stack A to stack B
static int	find_cheapest_move(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*current;
	int		pos;
	int		cheapest_pos;
	int		cheapest_cost;
	int		current_cost;
	int		target_pos;
	int		size_a;
	int		size_b;

	size_a = get_stack_size(stack_a);
	size_b = get_stack_size(stack_b);
	current = *stack_a;
	pos = 0;
	cheapest_pos = 0;
	cheapest_cost = 2147483647; // INT_MAX

	while (current)
	{
		target_pos = find_target_pos_b(stack_b, current->number);
		current_cost = calculate_move_cost(pos, target_pos, size_a, size_b);

		if (current_cost < cheapest_cost)
		{
			cheapest_cost = current_cost;
			cheapest_pos = pos;
		}

		current = current->next;
		pos++;
	}

	return (cheapest_pos);
}

// Execute rotations to bring element to top of stack A and target position to top of stack B
static void	execute_rotations(t_stack **stack_a, t_stack **stack_b, int pos_a, int target_pos_b)
{
	int	size_a = get_stack_size(stack_a);
	int	size_b = get_stack_size(stack_b);
	int	rot_a = (pos_a <= size_a / 2) ? pos_a : size_a - pos_a;
	int	rot_b = (target_pos_b <= size_b / 2) ? target_pos_b : size_b - target_pos_b;

	// Use simultaneous rotations when possible
	if (pos_a <= size_a / 2 && target_pos_b <= size_b / 2)
	{
		while (rot_a > 0 && rot_b > 0)
		{
			do_rr(stack_a, stack_b);
			rot_a--;
			rot_b--;
		}
		while (rot_a > 0)
		{
			do_ra(stack_a, 1);
			rot_a--;
		}
		while (rot_b > 0)
		{
			do_rb(stack_b, 1);
			rot_b--;
		}
	}
	else if (pos_a > size_a / 2 && target_pos_b > size_b / 2)
	{
		while (rot_a > 0 && rot_b > 0)
		{
			do_rrr(stack_a, stack_b);
			rot_a--;
			rot_b--;
		}
		while (rot_a > 0)
		{
			do_rra(stack_a, 1);
			rot_a--;
		}
		while (rot_b > 0)
		{
			do_rrb(stack_b, 1);
			rot_b--;
		}
	}
	else
	{
		// Different directions, no simultaneous rotation
		if (pos_a <= size_a / 2)
		{
			while (rot_a > 0)
			{
				do_ra(stack_a, 1);
				rot_a--;
			}
		}
		else
		{
			while (rot_a > 0)
			{
				do_rra(stack_a, 1);
				rot_a--;
			}
		}

		if (target_pos_b <= size_b / 2)
		{
			while (rot_b > 0)
			{
				do_rb(stack_b, 1);
				rot_b--;
			}
		}
		else
		{
			while (rot_b > 0)
			{
				do_rrb(stack_b, 1);
				rot_b--;
			}
		}
	}
}

// Move elements back from stack B to stack A in correct positions
static void	push_back_to_a(t_stack **stack_a, t_stack **stack_b)
{
	int	target_pos;
	int	size_a;

	while (*stack_b)
	{
		target_pos = find_target_pos_a(stack_a, (*stack_b)->number);
		size_a = get_stack_size(stack_a);

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

		do_pa(stack_b, stack_a);
	}
}

// Bring minimum element to top of stack A
static void	final_rotation(t_stack **stack_a)
{
	t_stack	*current;
	t_stack	*min_node;
	int		min_pos;
	int		pos;
	int		size;

	if (!*stack_a)
		return ;

	min_node = *stack_a;
	current = *stack_a;
	min_pos = 0;
	pos = 0;

	// Find minimum value and its position
	while (current)
	{
		if (current->number < min_node->number)
		{
			min_node = current;
			min_pos = pos;
		}
		current = current->next;
		pos++;
	}

	size = get_stack_size(stack_a);

	// Rotate to bring minimum to top
	if (min_pos <= size / 2)
	{
		while (min_pos > 0)
		{
			do_ra(stack_a, 1);
			min_pos--;
		}
	}
	else
	{
		while (min_pos < size)
		{
			do_rra(stack_a, 1);
			min_pos++;
		}
	}
}

// Main function implementing the Turk Algorithm for large sorts
void	large_sort(t_stack **stack_a, t_stack **stack_b)
{
	int		cheapest_pos;
	int		target_pos;
	t_stack	*current;
	int		i;

	// Step 1: Push first 2 elements to stack B
	do_pb(stack_a, stack_b);
	do_pb(stack_a, stack_b);

	// Step 2: Push elements using cost calculation until only 3 remain
	while (get_stack_size(stack_a) > 3)
	{
		cheapest_pos = find_cheapest_move(stack_a, stack_b);

		// Find the value at cheapest position
		current = *stack_a;
		i = 0;
		while (i < cheapest_pos && current)
		{
			current = current->next;
			i++;
		}

		target_pos = find_target_pos_b(stack_b, current->number);
		execute_rotations(stack_a, stack_b, cheapest_pos, target_pos);
		do_pb(stack_a, stack_b);
	}

	// Step 3: Sort the remaining 3 elements in stack A
	sort_three(stack_a);

	// Step 4: Push everything back from B to A
	push_back_to_a(stack_a, stack_b);

	// Step 5: Final rotation to bring minimum to top
	final_rotation(stack_a);
}

/**
 * -
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
