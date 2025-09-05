/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:28:38 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/02 15:35:03 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static t_actions	check_for_commons(t_moves *moves, unsigned int i)
{
	if (moves->seq[i] == RA && moves->seq[i + 1] == RB
		|| moves->seq[i] == RB && moves->seq[i + 1] == RA)
		return (RR);
	else if (moves->seq[i] == RRA && moves->seq[i + 1] == RRB
		|| moves->seq[i] == RRB && moves->seq[i + 1] == RRA)
		return (RRR);
	else if (moves->seq[i] == SA && moves->seq[i + 1] == SB
		|| moves->seq[i] == SB && moves->seq[i + 1] == SA)
		return (SS);
	return (SKIP);
}

/**
 * - Recursively check if the numbers above and below the current moves
 * 	have ra and rb, and etc. for other combined moves
 */
static void	recur_common(t_moves *moves, unsigned int i, unsigned int total)
{
	t_actions	combined;

	if (i + 1 >= total)
		return ;
	combined = check_for_commons(moves, i);
	if (combined == RR || combined == RRR || combined == SS)
	{
		moves->seq[i] = combined;
		moves->seq[i + 1] = SKIP;
		moves->total_moves = --total;
		if (i > 0)
			recur_common(moves, i - 1, moves->total_moves);
		recur_common(moves, i, moves->total_moves);
	}
	else
		recur_common(moves, i + 1, total);
}

/**
 * - Container for optimizations before execution (for scaling)
 */
static void	optimize_moves(t_moves *moves)
{
	recur_common(moves, 0, moves->total_moves);
}

/**
 * - Perform the move based on the enum given
 */
void	perform_move(t_actions move, t_stack **a, t_stack **b)
{
	if (move == RA)
		do_ra(a, 1);
	else if (move == RRA)
		do_rra(a, 1);
	else if (move == RB)
		do_rb(b, 1);
	else if (move == RRB)
		do_rrb(b, 1);
	else if (move == RR)
		do_rr(a, b);
	else if (move == RRR)
		do_rrr(a, b);
	else if (move == PB)
		do_pb(a, b);
	else if (move == PA)
		do_pa(b, a);
	else if (move == SA)
		do_sa(a, 1);
	else if (move == SB)
		do_sb(b, 1);
	else if (move == SS)
		do_ss(a, b);
	else if (move == SKIP || move == END)
		return ;
}

/**
 * - Execute moves minimally
 * - Do optimizations before performing
 */
void	execute_moves(t_moves *moves, t_stack **a, t_stack **b)
{
	unsigned int	i;

	i = 0;
	optimize_moves(moves);
	while (i < moves->total_moves && moves->seq[i] != END)
	{
		perform_move(moves->seq[i], a, b);
		i++;
	}
}
