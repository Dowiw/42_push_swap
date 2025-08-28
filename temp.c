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

typedef struct s_chunk
{
	unsigned int	chunk_id; // id of each chunk
	unsigned int	min_value;
	unsigned int	max_value;
	unsigned int	size;
	unsigned int	current_count; // how many elements currently in chunk
}		t_chunk;

typedef struct s_moves
{
	unsigned int	ra;
	unsigned int	rb;
	unsigned int	rr;
	unsigned int	rra;
	unsigned int	rrb;
	unsigned int	rrr;
	unsigned int	total_moves;
}					t_moves;

typedef struct s_data
{
	t_chunk			*chunks; // array of chunks
	unsigned int	num_chunks;
	unsigned int	*chunk_sizes;
	unsigned int	total_size;
}					t_data;

/**
 * - Chunk count for fine tuning
 * - Size represents the size itself
 * - Should be remembered that it is NOT **0-indexed**
 */
unsigned int	calc_chunk_count(unsigned int size)
{
	if (size <= 10)
		return (3);
	else if (size <= 50)
		return (5);
	else if (size <= 100)
		return (7);
	else if (size <= 200)
		return (10);
	else if (size <= 500)
		return (12);
	else
		return (15);
}

/**
 * - Initialize chunk struct values
 * - Chunks for chunks array, respective sizes,
 *  the number of chunks, and stack a for min max
 */
void	init_chunks(t_chunk *chunks, int *sizes, int count, t_stack **a)
{
	int	i;
	int	current_min;

	i = 0;
	current_min = 0;
	while (i < count)
	{
		chunks[i].chunk_id = i;
		chunks[i].min_value = current_min;
		chunks[i].max_value = current_min + sizes[i] - 1;
		chunks[i].size = sizes[i];
		chunks[i].current_count = 0;
		current_min += sizes[i];
	}
}

/**
 * - Assign each chunk size based on the total size and chunk count
 * - It does this in a decreasing manner where the first is big
 * - This means that the small numbers have a big size
 */
void	init_chunk_sizes(int *chunk_sizes, int size, int chunk_count)
{
	int	weight;
	int	assigned;
	int	total_weight;
	int	i;

	total_weight = 0;
	i = 0;
	while (i++ < chunk_count)
		total_weight += (chunk_count - i);
	i = 0;
	assigned = 0;
	while (i++ < chunk_count)
	{
		weight = chunk_count - i;
		if (i == chunk_count - 1)
			chunk_sizes[i] = size - assigned;
		else
		{
			chunk_sizes[i] = (size * weight) / total_weight;
			assigned += chunk_sizes[i];
		}
	}
}

/**
 * - Assign each i which is correct_idx their stack id
 * - Compares to each chunks min and max
 */
unsigned int	assign_id(unsigned int correct_i, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_chunks)
	{
		if (correct_i >= data->chunks[i].min_value &&
			correct_i <= data->chunks[i].max_value)
		{
			data->chunks[i].current_count++;
			return (i);
		}
		i++;
	}
	write(1, "Error in assign id\n", 20);
	return (i);
}

/**
 * - Assign each stack_a their proper stack_id
 */
void	assign_stack_a(t_data *data, t_stack **a)
{
	unsigned int	correct_i;
	t_stack			*current;

	current = *a;
	while (current)
	{
		correct_i = current->correct_idx;
		current->stack_id = assign_id(correct_i, data);
		current = current->next;
	}
}

/**
 * - Initialize data and assign each node in a its stack id
 * - Initializes each chunk with their respective sizes and min/max
 * - Malloc protects from data
 */
void	init_data_and_assign(t_stack **a, int size, t_data *data)
{
	unsigned int	chunk_count;

	chunk_count = calc_chunk_count(size);
	data->chunks = malloc(sizeof(t_chunk) * chunk_count);
	if (!data->chunks)
	{
		free_data(data);
		error_free_exit(a, NULL);
	}
	data->chunk_sizes = malloc(sizeof(unsigned int) * chunk_count);
	if (!data->chunk_sizes)
	{
		free_data(data);
		error_free_exit(a, NULL);
	}
	init_sizes(&data->chunk_sizes, size, chunk_count);
	data->num_chunks = chunk_count;
	data->total_size = size;
	init_chunks(data->chunks, data->chunk_sizes, chunk_count, a);
	assign_stack_a(data, a);
}

t_moves	init_moves(void)
{
	t_moves	moves;

	moves.ra = 0;
	moves.rb = 0;
	moves.rr = 0;
	moves.rra = 0;
	moves.rrb = 0;
	moves.rra = 0;
	moves.total_moves = INT_MAX;
}

t_moves	retrive_moves()
{

}

t_moves	best_move(t_data *data, t_stack **a, t_stack **b, unsigned int chunk_i)
{
	t_moves	current_moves;
	t_moves	best_moves;
	t_stack	*current;

	current = *a;
	current_moves = init_moves();
	best_moves = init_moves();
	while (current)
	{
		if (current->stack_id == chunk_i)
			current_moves = retrive_moves();
		if (current_moves.total_moves < best_moves.total_moves)
			best_moves = current_moves;
		current = current->next;
	}
	return (best_moves);
}

/**
 * - Heart
 */
void	large_sort(t_stack **a, t_stack **b, int size)
{
	t_moves			moves;
	t_data			*data;
	unsigned int	chunk_i;

	data = malloc(sizeof(t_data));
	if (!data)
		error_free_exit(a, b);
	init_data_and_assign(a, size, &data);
	chunk_i = 0;
	while (get_stack_size(a) > 0)
	{
		moves = best_move(&data, a, b, chunk_i);
		execute_moves(&moves);
		do_pb(a, b);
	}
	push_back_to_a();
	free_data();
}

/**
 * - Checks if stack is sorted
 */
int	is_sorted(t_stack **a)
{
	t_stack	*cursor;

	cursor = *a;
	while (cursor != NULL && cursor->next != NULL)
	{
		if (cursor->correct_idx > cursor->next->correct_idx)
			return (0);
		cursor = cursor->next;
	}
	return (1);
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
	size = get_stack_size(a);
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
		large_sort(a, b, get_smallest(a));
}
