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
#include <stdlib.h>
#include <stdio.h>

int	ft_abs(int num)
{
	if (num > 0)
		return (num * -1);
	return (num);
}

/**
 */
t_moves	calculate_moves(int target_a, int pos_b, int size_a, int size_b)
{
	t_moves	temp;
	int	moves_a;
	int	moves_b;
	int	common;

	moves_a = 0;
	moves_b = 0;
	common = 0;
	if (target_a <= size_a / 2)
		moves_a = target_a;
	else
		moves_a = target_a - size_a;
	if (pos_b <= size_b / 2)
		moves_b = pos_b;
	else
		moves_b = pos_b - size_b;
	if (moves_a > 0 && moves_b > 0)
		common = (moves_a < moves_b) * moves_a + (moves_a >= moves_b) * moves_b;
	else if (moves_a < 0 && moves_b < 0)
		common = (moves_a > moves_b) * moves_a + (moves_a <= moves_b) * moves_b;
	temp.total_moves = ft_abs(moves_a) + ft_abs(moves_b) - ft_abs(common);
	temp.both = common;
	temp.rotates_a = moves_a;
	temp.rotates_b = moves_b;
	return (temp);
}

/**
 * - Find the best move for all numbers in stack b
 * - Use Turk heart of determining ra_rb, rra_rrb, ra_rrb, rra_rb
 */
t_moves	find_best_moves(t_stack **a, t_stack **b)
{
	int		target_a;
	int		pos;
	t_moves	best;
	t_moves	temp;
	t_stack	*current;

	pos = 0;
	best.rotates_b = 0;
	best.rotates_a = 0;
	best.both = 0;
	best.total_moves = INT_MAX;
	temp.both = 0; temp.rotates_a = 0; temp.rotates_b = 0; temp.total_moves = 0;
	current = *b;
	while (current)
	{
		target_a = find_target_pos_a(a, current->number);
		temp = calculate_moves(target_a, pos, stack_size(a), stack_size(b));
		if (temp.total_moves < best.total_moves)
			best = temp;
		pos++;
		current = current->next;
	}
	return (best);
}

void	execute_moves(t_moves *moves, t_stack **a, t_stack **b)
{
    int ra = moves->rotates_a;
    int rb = moves->rotates_b;
    int both = moves->both;

    while (both > 0) { do_rr(a, b); ra--; rb--; both--; }
    while (both < 0) { do_rrr(a, b); ra++; rb++; both++; }
    while (ra > 0) { do_ra(a, 1); ra--; }
    while (ra < 0) { do_rra(a, 1); ra++; }
    while (rb > 0) { do_rb(b, 1); rb--; }
    while (rb < 0) { do_rrb(b, 1); rb++; }
}

/**
 * - Perform Turk when pushing back to a
 */
void	push_back_to_a(t_stack **a, t_stack **b)
{
	int		i;
	int		min_pos;
	t_moves	best_moves;

	while (stack_size(b) > 0) // To debug
	{
		// t_moves	temp; temp.rotates_a = 0; temp.rotates_b = 0; temp.both = 0; temp.total_moves = 0;
		// best_moves.rotates_a = 0; best_moves.rotates_b = 0; best_moves.both = 0; best_moves.total_moves = INT_MAX;
		// int size_a = stack_size(a);
		// int size_b = stack_size(b);
		// int pos = 0;

		// // super greedy, get every single move for every single b
		// for (t_stack *cur = *b; cur; cur = cur->next, pos++)
		// {
		// 	int target_pos_a = find_target_pos_a(a, cur->number);
		// 	temp.rotates_a = (target_pos_a <= size_a / 2) ? target_pos_a : target_pos_a - size_a;
		// 	temp.rotates_b = (pos <= size_b / 2) ? pos : pos - size_b;
		// 	temp.both = 0;
		// 	if (temp.rotates_a > 0 && temp.rotates_b > 0)
		// 		temp.both = (temp.rotates_a < temp.rotates_b) ? temp.rotates_a : temp.rotates_b;
		// 	else if (temp.rotates_a < 0 && temp.rotates_b < 0)
		// 		temp.both = (temp.rotates_a > temp.rotates_b) ? temp.rotates_a : temp.rotates_b;
		// 	temp.total_moves = abs(temp.rotates_a) + abs(temp.rotates_b) - abs(temp.both);
		// 	if (temp.total_moves < best_moves.total_moves)
		// 	{
		// 		best_moves.total_moves = temp.total_moves;
		// 		best_moves.rotates_a = temp.rotates_a;
		// 		best_moves.rotates_b = temp.rotates_b;
		// 		best_moves.both = temp.both;
		// 	}
		// }

		// int best_common = best_moves.both;
		// int best_moves_a = best_moves.rotates_a;
		// int	best_moves_b = best_moves.rotates_b;

		// // Perform common rotations
		// while (best_common > 0)
		// {
		// 	do_rr(a, b);
		// 	best_moves_a--;
		// 	best_moves_b--;
		// 	best_common--;
		// }
		// while (best_common < 0)
		// {
		// 	do_rrr(a, b);
		// 	best_moves_a++;
		// 	best_moves_b++;
		// 	best_common++;
		// }
		// // Finish remaining rotations for A
		// while (best_moves_a > 0) { do_ra(a, 1); best_moves_a--; }
		// while (best_moves_a < 0) { do_rra(a, 1); best_moves_a++; }
		// // Finish remaining rotations for B
		// while (best_moves_b > 0) { do_rb(b, 1); best_moves_b--; }
		// while (best_moves_b < 0) { do_rrb(b, 1); best_moves_b++; }

		// Push from B to A
		best_moves = find_best_moves(a, b);
		execute_moves(&best_moves, a, b);
		do_pa(b, a);
	}
	min_pos = find_min_pos(a);
	i = 0;
	if (min_pos <= stack_size(a) / 2)
	{
		while (i++ < min_pos)
			do_ra(a, 1);
	}
	else
	{
		while (i++ < stack_size(a) - min_pos)
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
	s_size = stack_size(&a);
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
	int				gap;
	unsigned int	i;

	i = 0;
	gap = 40;
	while (stack_size(a) > 1)
	{
		if ((*a)->correct_idx <= i)
		{
			do_pb(a, b);
			do_rb(b, 1);
			++i;
		}
		else if ((*a)->correct_idx <= i + gap)
		{
			do_pb(a, b);
			++i;
		}
		else if (check_opposite(*a))
			do_rra(a, 1);
		else
			do_ra(a, 1);
	}
	push_back_to_a(a, b);
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
	size = stack_size(a);
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
