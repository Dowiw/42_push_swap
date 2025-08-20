/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 08:10:21 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/18 08:10:22 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <unistd.h>

/**
 * - Swap the first 2 elements of stack b
 */
void	do_sb(t_stack **stack_b)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	first = *stack_b;
	second = first->next;
	first->next = second->next;
	first->prev = second;
	second->next = first;
	second->prev = NULL;
	if (second->next)
		second->next->prev = first;
	*stack_b = second;
	write(1, "sb\n", 3);
}

/**
 * - Push the top of stack a to stack b
 */
void	do_pb(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*top_a;

	if (!stack_a || !*stack_a)
		return ;
	top_a = *stack_a;
	*stack_a = top_a->next;
	if (*stack_a)
		(*stack_a)->prev = NULL;
	top_a->next = NULL;
	top_a->prev = NULL;
	if (!*stack_b)
		*stack_b = top_a;
	else
		stack_push_top(stack_b, top_a);
	write(1, "pb\n", 3);
}

/**
 * - Shift elements of up stack b by one
 */
void	do_rb(t_stack **stack_b)
{
	t_stack	*top_b;
	t_stack	*bottom_b;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	top_b = *stack_b;
	bottom_b = *stack_b;
	while (bottom_b->next != NULL)
		bottom_b = bottom_b->next;
	*stack_b = top_b->next;
	(*stack_b)->prev = NULL;
	bottom_b->next = top_b;
	top_b->prev = bottom_b;
	top_b->next = NULL;
	write(1, "rb\n", 3);
}

/**
 * - Shift elements of stack b down by one
 */
void	do_rrb(t_stack **stack_b)
{
	t_stack	*top_b;
	t_stack	*bottom_b;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	top_b = *stack_b;
	bottom_b = *stack_b;
	while (bottom_b->next != NULL)
		bottom_b = bottom_b->next;
	bottom_b->next = top_b;
	bottom_b->prev->next = NULL;
	bottom_b->prev = NULL;
	top_b->prev = bottom_b;
	*stack_b = bottom_b;
	write(1, "rrb\n", 4);
}
