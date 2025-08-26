/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:17:12 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/20 12:17:13 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <unistd.h>

void	sort_three(t_stack **a)
{
	int	first;
	int	second;
	int	third;

	first = (*a)->correct_idx;
	second = (*a)->next->correct_idx;
	third = (*a)->next->next->correct_idx;
	if (first > second && second < third && first < third)
		do_sa(a, 1);
	else if (first > second && second > third)
	{
		do_sa(a, 1);
		do_rra(a, 1);
	}
	else if (first > third && second < first && second < third)
		do_ra(a, 1);
	else if (second > first && second > third && third > first)
	{
		do_sa(a, 1);
		do_ra(a, 1);
	}
	else if (first < second && second > third && first > third)
		do_rra(a, 1);
}

void	sort_four(t_stack **a, t_stack **b)
{
	int		min;
	t_stack	*cursor;

	min = 0;
	cursor = *a;
	while (cursor->correct_idx != min)
	{
		do_ra(a, 1);
		cursor = cursor->next;
	}
	do_pb(a, b);
	sort_three(a);
	do_pa(b, a);
}

void	sort_five(t_stack **a, t_stack **b)
{
	int		min;
	int		second_min;
	int		nums_pushed;
	t_stack	*cursor;

	min = 0;
	second_min = 1;
	nums_pushed = 0;
	while (nums_pushed < 2)
	{
		cursor = *a;
		if (cursor->correct_idx == min || cursor->correct_idx == second_min)
		{
			do_pb(a, b);
			nums_pushed++;
		}
		else
			do_ra(a, 1);
	}
	sort_three(a);
	cursor = *b;
	if (cursor->correct_idx < cursor->next->correct_idx)
		do_sb(b, 1);
	do_pa(b, a);
	do_pa(b, a);
}
