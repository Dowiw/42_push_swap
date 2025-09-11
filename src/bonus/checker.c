/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:48:49 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/10 09:48:50 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include "get_next_line.h"
#include <unistd.h>

/**
 * - Helper for exiting and freeing things
 * 0 for OK, 1 for KO, 2 for Error to STDERR and exits
 */
static void	free_and_write(int flag, t_stack **a, t_stack **b, char **move)
{
	if (move && *move)
		free(*move);
	free_stacks(a, b);
	get_next_line(-1);
	if (flag == 0)
		write(1, "OK\n", 3);
	else if (flag == 1)
		write(1, "KO\n", 3);
	else if (flag == 2)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}

/**
 * - strcmp: returns negative if s1 < s2
 * 	returns positive if s1 > s2
 * 	0 if equal
 */
static int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 *
 */
static void	check_and_perform(char **move, t_stack **a, t_stack **b)
{
	if (ft_strcmp("ra\n", (*move)) == 0)
		do_ra(a, 0);
	else if (ft_strcmp("rb\n", (*move)) == 0)
		do_rb(b, 0);
	else if (ft_strcmp("rr\n", (*move)) == 0)
		do_rr(a, b, 0);
	else if (ft_strcmp("rra\n", (*move)) == 0)
		do_rra(a, 0);
	else if (ft_strcmp("rrb\n", (*move)) == 0)
		do_rrb(b, 0);
	else if (ft_strcmp("rrr\n", (*move)) == 0)
		do_rrr(a, b, 0);
	else if (ft_strcmp("pb\n", (*move)) == 0)
		do_pb(a, b, 0);
	else if (ft_strcmp("pa\n", (*move)) == 0)
		do_pa(b, a, 0);
	else if (ft_strcmp("sa\n", (*move)) == 0)
		do_sa(a, 0);
	else if (ft_strcmp("sb\n", (*move)) == 0)
		do_sb(b, 0);
	else if (ft_strcmp("ss\n", (*move)) == 0)
		do_ss(a, b, 0);
	else
		free_and_write(2, a, b, move);
}

/**
 * - Perform moves on stack taken from stdin
 * - If moves are not valid or does not make sense
 */
static void	perform_moves(t_stack **a, t_stack **b)
{
	char	*move;

	move = get_next_line(STDIN_FILENO);
	while (move != NULL)
	{
		check_and_perform(&move, a, b);
		free(move);
		move = get_next_line(STDIN_FILENO);
	}
	if (is_sorted(a))
		free_and_write(0, a, b, &move);
	else
		free_and_write(1, a, b, &move);
}

/**
 * - Main
 */
int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (ac < 2)
		return (0);
	else if (!are_valid_args(av))
		error_free_exit(NULL, NULL);
	stack_a = NULL;
	stack_b = NULL;
	fill_stack_a(&stack_a, ac, av);
	perform_moves(&stack_a, &stack_b);
	return (0);
}
