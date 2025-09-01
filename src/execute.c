#include "ft_push_swap.h"
#include <string.h>

/**
 * - Recursively check if the numbers above and below the current moves
 * 	have ra and rb, and etc. for other combined moves
 */
void	recursive_rr(t_moves *moves, unsigned int i, unsigned int total)
{
	if (i + 1 >= total)
		return ;
	if (strcmp(moves->seq[i], "ra") == 0 && strcmp(moves->seq[i + 1], "rb") == 0)
	{
		strcpy(moves->seq[i], "rr");
		for (unsigned int j = i + 1; j + 1 < total; j++)
			strcpy(moves->seq[j], moves->seq[j + 1]);
		moves->total_moves--;
		if (i > 0)
			recursive_rr(moves, i - 1, moves->total_moves);
		recursive_rr(moves, i, moves->total_moves);
	}
	// Combine rra + rrb -> rrr
	else if (strcmp(moves->seq[i], "rra") == 0 && strcmp(moves->seq[i + 1], "rrb") == 0)
	{
		strcpy(moves->seq[i], "rrr");
		for (unsigned int j = i + 1; j + 1 < total; j++)
			strcpy(moves->seq[j], moves->seq[j + 1]);
		moves->total_moves--;
		if (i > 0)
			recursive_rr(moves, i - 1, moves->total_moves);
		recursive_rr(moves, i, moves->total_moves);
	}
	// Combine sa + sb -> ss
	else if (strcmp(moves->seq[i], "sa") == 0 && strcmp(moves->seq[i + 1], "sb") == 0)
	{
		strcpy(moves->seq[i], "ss");
		for (unsigned int j = i + 1; j + 1 < total; j++)
			strcpy(moves->seq[j], moves->seq[j + 1]);
		moves->total_moves--;
		if (i > 0)
			recursive_rr(moves, i - 1, moves->total_moves);
		recursive_rr(moves, i, moves->total_moves);
	}
	else
		recursive_rr(moves, i + 1, total);
}

/**
 * - Container for optimizations before execution
 */
void	optimize_moves(t_moves *moves)
{
	recursive_rr(moves, 0, moves->total_moves);
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
	while (i < moves->total_moves)
	{
		perform_move(moves->seq[i], a, b);
		i++;
	}
}
