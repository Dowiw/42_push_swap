#include "ft_push_swap.h"
#include <string.h>

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

void	optimize_moves(t_moves *moves)
{
	recursive_rr(moves, 0, moves->total_moves);
}

void	perform_move(char *move, t_stack **a, t_stack **b)
{
	if (strcmp(move, "ra") == 0)
		do_ra(a, 1);
	else if (strcmp(move, "rra") == 0)
		do_rra(a, 1);
	else if (strcmp(move, "rb") == 0)
		do_rb(b, 1);
	else if (strcmp(move, "rrb") == 0)
		do_rrb(b, 1);
	else if (strcmp(move, "rr") == 0)
		do_rr(a, b);
	else if (strcmp(move, "rrr") == 0)
		do_rrr(a, b);
	else if (strcmp(move, "pb") == 0)
		do_pb(a, b);
	else if (strcmp(move, "pa") == 0)
		do_pa(b, a);
	else if (strcmp(move, "sa") == 0)
		do_sa(a, 1);
	else if (strcmp(move, "sb") == 0)
		do_sb(b, 1);
}
/**
 * - Execute moves minimally
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
