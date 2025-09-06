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
    t_stack *cur = *a;
    t_stack *largest = *a;
    t_stack *smallest = *a;
    int pos = 0, best_pos = 0, i = 0, size = stack_size(a);

    // Find largest and smallest node
    cur = *a;
    while (cur)
    {
        if (cur->number > largest->number)
            largest = cur;
        if (cur->number < smallest->number)
            smallest = cur;
        cur = cur->next;
    }

    // If value is greater than all or less than all, put after largest
if (value > largest->number || value < smallest->number)
{
    cur = *a;
    best_pos = 0;
    while (cur && cur->number != smallest->number)
    {
        cur = cur->next;
        best_pos++;
    }
    return best_pos;
}

    // Otherwise, find the first place where value fits between cur and cur->next
    cur = *a;
    for (i = 0; i < size; i++)
    {
        t_stack *next = cur->next ? cur->next : *a;
        if (cur->number < value && value < next->number)
            return (i + 1) % size;
        cur = cur->next;
    }
    return 0;
}
