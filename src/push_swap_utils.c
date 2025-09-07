/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:36:02 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/02 11:36:03 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <limits.h>

/**
 * - Get the node with the smallest value
 */
t_stack	*get_smallest_node(t_stack **stack)
{
	int		smallest;
	int		current_num;
	t_stack	*current;

	smallest = INT_MAX;
	current = *stack;
	while (current)
	{
		current_num = current->number;
		if (current_num < smallest)
			smallest = current_num;
		current = current->next;
	}
	current = *stack;
	while (current && current->number != smallest)
		current = current->next;
	return (current);
}

/**
 * - Get the node with the largest value
 */
t_stack	*get_largest_node(t_stack **stack)
{
	int		largest;
	int		current_num;
	t_stack	*current;

	largest = INT_MIN;
	current = *stack;
	while (current)
	{
		current_num = current->number;
		if (current_num > largest)
			largest = current_num;
		current = current->next;
	}
	current = *stack;
	while (current && current->number != largest)
		current = current->next;
	return (current);
}

/**
 * - Find index of smallest number in stack
 */
int	find_min_pos(t_stack **stack)
{
	int		i;
	int		min;
	int		min_pos;
	t_stack	*current;

	current = *stack;
	min = current->number;
	min_pos = 0;
	i = 0;
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
	return (min_pos);
}

/**
 * - If value is greater or less than numbers, put on top of
 * 	smallest number in a
 * - Else, look for a snug fit between two values of a
 * - Or just push if conditions not met (0)
 */
int	find_target_pos_a(t_stack **a, int value)
{
	int		smallest;
	int		largest;
	int		i;
	t_stack	*cursor;

	cursor = *a;
	smallest = get_smallest_node(a)->number;
	largest = get_largest_node(a)->number;
	if (value > largest || value < smallest)
		return (find_min_pos(a));
	i = 0;
	while (cursor && cursor->next)
	{
		if (cursor->number < value && value < cursor->next->number)
			return (i + 1);
		cursor = cursor->next;
		i++;
	}
	if (cursor && cursor->number < value && value < (*a)->number)
		return (0);
	return (i + 1);
}

/**
 * - Simple heuristic:
 *	If 55% of the stack has numbers with close indexes, go reverse
 */
int	check_opposite(t_stack **a)
{
	int		size_a;
	int		count;
	int		diff;
	t_stack	*cursor;

	diff = 0;
	count = 0;
	size_a = stack_size(a);
	cursor = *a;
	while (cursor && cursor->next)
	{
		diff = cursor->correct_idx - cursor->next->correct_idx;
		if (diff == 1 || diff == 2 || diff == 3 || diff == 4)
			count++;
		cursor = cursor->next;
	}
	if (count * 10 >= size_a * 5.5)
		return (1);
	return (0);
}
