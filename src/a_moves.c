/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 08:10:12 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/21 10:10:42 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <unistd.h>

/**
 * - Swap the first 2 elements of stack a
 * - Put the bool 1 to write the instruction, 0 for no
 */
void	do_sa(t_stack **stack_a, int bool)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	first = *stack_a;
	second = first->next;
	first->next = second->next;
	first->prev = second;
	if (second->next)
		second->next->prev = first;
	second->next = first;
	second->prev = NULL;
	*stack_a = second;
	if (bool)
		write(1, "sa\n", 3);
}

/**
 * - Push the top of stack b to stack a
 */
void	do_pa(t_stack **stack_b, t_stack **stack_a)
{
	t_stack	*top_b;

	if (!stack_b || !*stack_b)
		return ;
	top_b = *stack_b;
	*stack_b = top_b->next;
	if (*stack_b)
		(*stack_b)->prev = NULL;
	top_b->next = NULL;
	top_b->prev = NULL;
	if (!*stack_a)
		*stack_a = top_b;
	else
		stack_push_top(stack_a, top_b);
	write(1, "pa\n", 3);
}

/**
 * - Shift elements up of stack a by one
 * - Put the bool 1 to write the instruction, 0 for no
 */
void	do_ra(t_stack **stack_a, int bool)
{
	t_stack	*top_a;
	t_stack	*bottom_a;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	top_a = *stack_a;
	bottom_a = *stack_a;
	while (bottom_a->next != NULL)
		bottom_a = bottom_a->next;
	*stack_a = top_a->next;
	(*stack_a)->prev = NULL;
	bottom_a->next = top_a;
	top_a->prev = bottom_a;
	top_a->next = NULL;
	if (bool)
		write(1, "ra\n", 3);
}

/**
 * - Shift elements of stack a down by one
 * - Put the bool 1 to write the instruction, 0 for no
 */
void	do_rra(t_stack **stack_a, int bool)
{
	t_stack	*top_a;
	t_stack	*bottom_a;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	top_a = *stack_a;
	bottom_a = *stack_a;
	while (bottom_a->next != NULL)
		bottom_a = bottom_a->next;
	bottom_a->next = top_a;
	bottom_a->prev->next = NULL;
	bottom_a->prev = NULL;
	top_a->prev = bottom_a;
	*stack_a = bottom_a;
	if (bool)
		write(1, "rra\n", 4);
}
