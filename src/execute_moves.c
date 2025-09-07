/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:05:25 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/07 23:56:27 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

/**
 * - Helper for remaining rotates
 */
static void	execute_remaining(int ra, int rb, t_stack **a, t_stack **b)
{
	while (ra > 0)
	{
		do_ra(a, 1);
		ra--;
	}
	while (ra < 0)
	{
		do_rra(a, 1);
		ra++;
	}
	while (rb > 0)
	{
		do_rb(b, 1);
		rb--;
	}
	while (rb < 0)
	{
		do_rrb(b, 1);
		rb++;
	}
}

/**
 * - Execute moves based on given moves
 */
void	execute_moves(t_moves *moves, t_stack **a, t_stack **b)
{
	int	ra;
	int	rb;
	int	both;

	ra = moves->rotates_a;
	rb = moves->rotates_b;
	both = moves->both;
	while (both > 0)
	{
		do_rr(a, b);
		ra--;
		rb--;
		both--;
	}
	while (both < 0)
	{
		do_rrr(a, b);
		ra++;
		rb++;
		both++;
	}
	execute_remaining(ra, rb, a, b);
}
