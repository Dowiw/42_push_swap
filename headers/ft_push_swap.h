/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:56:21 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/06 10:58:13 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

typedef struct s_stack
{
	int				number;
	unsigned int	correct_idx;
	unsigned int	chunk_id;
	struct s_stack	*prev;
	struct s_stack	*next;
}					t_stack;

typedef struct s_chunk
{
	unsigned int	chunk_id; // id of each chunk
	unsigned int	min_value;
	unsigned int	max_value;
	unsigned int	half;
	unsigned int	size;
	unsigned int	current_count; // how many elements currently in chunk
}		t_chunk;

typedef struct s_moves
{
	char			**seq;
	unsigned int	total_moves;
}					t_moves;

typedef struct s_data
{
	t_chunk			*chunks; // array of chunks
	unsigned int	num_chunks;
	unsigned int	*chunk_sizes;
	unsigned int	total_size;
}					t_data;

/* index.c */

void	get_index(t_stack **stack_a);

/* a_moves.c */

void	do_sa(t_stack **stack_a, int bool);
void	do_pa(t_stack **stack_b, t_stack **stack_a);
void	do_ra(t_stack **stack_a, int bool);
void	do_rra(t_stack **stack_a, int bool);

/* b_moves.c */

void	do_sb(t_stack **stack_b, int bool);
void	do_pb(t_stack **stack_a, t_stack **stack_b);
void	do_rb(t_stack **stack_b, int bool);
void	do_rrb(t_stack **stack_b, int bool);

/* both_moves.c */

void	do_ss(t_stack **stack_a, t_stack **stack_b);
void	do_rr(t_stack **stack_a, t_stack **stack_b);
void	do_rrr(t_stack **stack_a, t_stack **stack_b);

// optimize.c

void	execute_moves(t_moves *moves, t_stack **a, t_stack **b);

/* parsing.c */

int		is_valid_arg(char *arg);
int		are_valid_args(char **av);
int		parse_and_push(t_stack **stack_a, char *s, int *j);
void	fill_stack_a(t_stack **stack_a, int ac, char **av);
void	check_and_alloc(t_stack **stack_a, int num);

/* push_swap.c */

void	large_sort(t_stack **stack_a, t_stack **stack_b, int size);
void	do_push_swap(t_stack **stack_a, t_stack **stack_b);

/* small_sort.c */

void	sort_three(t_stack **a);
void	sort_four(t_stack **a, t_stack **b);
void	sort_five(t_stack **a, t_stack **b);

/* quicksort.c */

void	quicksort(int *arr, int low, int high);

/* stack.c */

void	stack_push_bottom(t_stack **stack, t_stack *node);
void	stack_push_top(t_stack **stack, t_stack *node);
t_stack	*stack_new_node(int number, t_stack *prev);
t_stack	*get_smallest(t_stack **stack);
int	get_stack_size(t_stack **stack);

/* utils.c */

int		ft_isdigit(char c);
int		ft_issign(char c);
void	error_free_exit(t_stack **stack_a, t_stack **stack_b);

#endif
