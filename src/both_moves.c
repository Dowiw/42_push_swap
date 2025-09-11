/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   both_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:11:32 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/17 17:11:33 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <unistd.h>

void	do_ss(t_stack **stack_a, t_stack **stack_b, int bool)
{
	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	do_sa(stack_a, 0);
	do_sb(stack_b, 0);
	if (bool)
		write(1, "ss\n", 3);
}

void	do_rr(t_stack **stack_a, t_stack **stack_b, int bool)
{
	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	do_ra(stack_a, 0);
	do_rb(stack_b, 0);
	if (bool)
		write(1, "rr\n", 3);
}

void	do_rrr(t_stack **stack_a, t_stack **stack_b, int bool)
{
	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	do_rra(stack_a, 0);
	do_rrb(stack_b, 0);
	if (bool)
		write(1, "rrr\n", 4);
}
