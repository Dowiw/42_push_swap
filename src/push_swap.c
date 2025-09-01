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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	is_sorted(t_stack **a);

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

void	free_data(t_data *data)
{
	if (!data)
		return;
	if (data->chunks)
		free(data->chunks);
	if (data->chunk_sizes)
		free(data->chunk_sizes);
	free(data);
}

// Add free_moves implementation
void free_moves(t_moves *moves)
{
	if (!moves)
		return;
	if (moves->seq)
	{
		for (unsigned int i = 0; moves->seq[i]; i++)
			free(moves->seq[i]);
		free(moves->seq);
	}
	free(moves);
}

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
void	init_chunks(t_chunk *chunks, unsigned int *sizes, int count)
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
		chunks[i].half = sizes[i] / 2;
		chunks[i].size = sizes[i];
		chunks[i].current_count = 0;
		// printf("chunk_id: %i, min_value: %i, max_value: %i, half: %i, size: %i\n", i, current_min, current_min + sizes[i] - 1, sizes[i] / 2, sizes[i]);
		current_min += sizes[i];
		i++;
	}
}

/**
 * - Assign each chunk size based on the total size and chunk count
 * - It does this in a decreasing manner where the first is big
 * - This means that the small numbers have a big size
 */
void	init_chunk_sizes(unsigned int *chunk_sizes, int size, int chunk_count)
{
	int	weight;
	int	assigned;
	int	total_weight;
	int	i;

	total_weight = 0;
	for (i = 0; i < chunk_count; i++)
		total_weight += (chunk_count - i - 1);
	assigned = 0;
	for (i = 0; i < chunk_count; i++)
	{
		weight = chunk_count - i - 1;
		if (i == chunk_count - 1)
			chunk_sizes[i] = size - assigned;
		else
		{
			chunk_sizes[i] = (size * weight) / total_weight;
			assigned += chunk_sizes[i];
		}
		// printf("Chunk size for %i: %u\n", i + 1, chunk_sizes[i]);
	}
}

/**
 * - Assign each i which is correct_idx their chunk id
 * - Compares to each chunks min and max
 */
unsigned int	assign_id(unsigned int correct_i, t_data *data)
{
	unsigned int	i;

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
 * - Assign each stack_a their proper chunk_id
 */
void	assign_stack_a(t_data *data, t_stack **a)
{
	unsigned int	correct_i;
	t_stack			*current;

	current = *a;
	while (current)
	{
		correct_i = current->correct_idx;
		current->chunk_id = assign_id(correct_i, data);
		// printf("Correct_i: %u, Current num: %i, Stack_id: %i\n", correct_i, current->number, current->chunk_id);
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
	// printf("Number of chunks: %u\n", chunk_count);
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
	init_chunk_sizes(data->chunk_sizes, size, chunk_count);
	data->num_chunks = chunk_count;
	data->total_size = size;
	init_chunks(data->chunks, data->chunk_sizes, chunk_count);
	assign_stack_a(data, a);
}

t_moves	*init_moves(int size)
{
	int		i = 0;
	t_moves	*moves;

	moves = malloc(sizeof(t_moves));
	if (!moves)
		return (NULL);
	moves->seq = malloc(sizeof(char *) * (size + 1));
	if (!moves->seq)
	{
		free(moves);
		return (NULL);
	}
	moves->seq[size] = NULL;
	while (i < size)
	{
		moves->seq[i] = malloc(sizeof(char) * 4);
		if (!moves->seq[i])
		{
			while (--i >= 0)
				free(moves->seq[i]);
			free(moves->seq);
			free(moves);
			return (NULL);
		}
		moves->seq[i][0] = '\0';
		i++;
	}
	moves->total_moves = INT_MAX;
	return (moves);
}

int find_target_pos_a(t_stack **a, int value)
{
	t_stack *current = *a;
	int pos = 0;

	// If value is less than all, or greater than all, insert before the smallest
	int min = current->number;
	int max = current->number;
	t_stack *tmp = current;
	while (tmp)
	{
		if (tmp->number < min)
			min = tmp->number;
		if (tmp->number > max)
			max = tmp->number;
		tmp = tmp->next;
	}
	if (value < min || value > max)
	{
		// Find position of the smallest value
		tmp = current;
		int min_pos = 0, i = 0;
		while (tmp)
		{
			if (tmp->number == min)
				min_pos = i;
			tmp = tmp->next;
			i++;
		}
		return min_pos;
	}

	// Otherwise, find the first node where current->number > value and previous < value
	while (current && current->next)
	{
		if (current->number < value && current->next->number > value)
			return pos + 1;
		pos++;
		current = current->next;
	}
	return 0; // fallback
}

int find_min_pos(t_stack **a)
{
	t_stack *current = *a;
	int min = current->number;
	int min_pos = 0, i = 0;

	while (current)
	{
		if (current->number < min)
		{
			min = current->number;
			min_pos = i;
		}
		current = current->next;
		i++;
	}
	return min_pos;
}

int get_smallest(t_stack **a)
{
	t_stack *current = *a;
	int min = current->number;

	while (current)
	{
		if (current->number < min)
			min = current->number;
		current = current->next;
	}
	return min;
}

int get_max_b(t_stack **b)
{
	t_stack *cur = *b;
	int max = cur ? cur->number : INT_MIN;
	while (cur)
	{
		if (cur->number > max)
			max = cur->number;
		cur = cur->next;
	}
	return max;
}

/**
 * - Get moves of the closest node in chunk_i from the bottom or top
 * - Pick which one is best in a way that puts it into stack b where one
 *  half of the chunk is on top and the other on the bottom
 */
t_moves *best_move(t_data *data, t_stack **a, t_stack **b, unsigned int chunk_i)
{
	t_stack *current = *a;
	t_stack *best_node = NULL;
	int size_a = get_stack_size(a);
	int min_moves = INT_MAX;
	int pos = 0, best_pos = 0;

	// Find the closest node in chunk_i (either from top or bottom)
	while (current)
	{
		if (current->chunk_id == chunk_i)
		{
			int moves_to_top = pos;
			int moves_to_bottom = size_a - pos;
			int moves = (moves_to_top <= moves_to_bottom) ? moves_to_top : moves_to_bottom;
			if (moves < min_moves)
			{
				min_moves = moves;
				best_node = current;
				best_pos = pos;
			}
		}
		pos++;
		current = current->next;
	}

	if (!best_node)
		return (NULL);
	// printf("Best node: %i, Pos: %i\n", best_node->number, best_pos);
	// Allocate and fill moves
	t_moves *moves = init_moves(data->total_size);
	if (!moves)
		return (NULL);

	// Rotate A to bring best_node to top
	if (best_pos <= size_a / 2)
	{
		for (int i = 0; i < best_pos; i++)
			strcpy(moves->seq[i], "ra");
		moves->total_moves = best_pos;
	}
	else
	{
		for (int i = 0; i < size_a - best_pos; i++)
			strcpy(moves->seq[i], "rra");
		moves->total_moves = size_a - best_pos;
	}

	// Add the push to B
	strcpy(moves->seq[moves->total_moves], "pb");
	moves->total_moves++;

	// if the number is the biggest seen ever, put to rb
	int max_b = get_max_b(b);
	if (best_node->number > max_b)
	{
	strcpy(moves->seq[moves->total_moves], "rb");
	moves->total_moves++;
	}
	return moves;
}

void	execute_moves(t_moves *moves, t_stack **a, t_stack **b)
{
	for (unsigned int i = 0; i < moves->total_moves; i++)
	{
		if (strcmp(moves->seq[i], "ra") == 0)
			do_ra(a, 1);
		else if (strcmp(moves->seq[i], "rra") == 0)
			do_rra(a, 1);
		else if (strcmp(moves->seq[i], "pb") == 0)
			do_pb(a, b);
		else if (strcmp(moves->seq[i], "pa") == 0)
			do_pa(b, a);
		else if (strcmp(moves->seq[i], "rb") == 0)
			do_rb(b, 1);
		else if (strcmp(moves->seq[i], "rrb") == 0)
			do_rrb(b, 1);
		else if (strcmp(moves->seq[i], "rr") == 0)
			do_rr(a, b);
		else if (strcmp(moves->seq[i], "rrr") == 0)
			do_rrr(a, b);
	}
}

t_stack *get_bottom_node(t_stack **b, int *pos)
{
	t_stack *current = *b;
	int i = 0;
	while (current && current->next)
	{
		current = current->next;
		i++;
	}
	if (pos)
		*pos = i;
	return current;
}

void push_back_to_a(t_stack **a, t_stack **b)
{
	int target_pos_top, target_pos_bottom, pos_bottom;
	t_moves *moves_top, *moves_bottom;
	t_stack *bottom_node;

	while (get_stack_size(b) > 0)
	{
		// Top of B
		target_pos_top = find_target_pos_a(a, (*b)->number);
		moves_top = init_moves(get_stack_size(a) + get_stack_size(b));
		if (!moves_top)
			error_free_exit(a, b);

		if (target_pos_top <= get_stack_size(a) / 2)
		{
			for (int i = 0; i < target_pos_top; i++)
				strcpy(moves_top->seq[i], "ra");
			moves_top->total_moves = target_pos_top;
		}
		else
		{
			for (int i = 0; i < get_stack_size(a) - target_pos_top; i++)
				strcpy(moves_top->seq[i], "rra");
			moves_top->total_moves = get_stack_size(a) - target_pos_top;
		}
		strcpy(moves_top->seq[moves_top->total_moves], "pa");
		moves_top->total_moves++;

		// Bottom of B
		bottom_node = get_bottom_node(b, &pos_bottom);
		target_pos_bottom = find_target_pos_a(a, bottom_node->number);
		moves_bottom = init_moves(get_stack_size(a) + get_stack_size(b));
		if (!moves_bottom)
			error_free_exit(a, b);

		// Rotate A for bottom value
		if (target_pos_bottom <= get_stack_size(a) / 2)
		{
			for (int i = 0; i < target_pos_bottom; i++)
				strcpy(moves_bottom->seq[i], "ra");
			moves_bottom->total_moves = target_pos_bottom;
		}
		else
		{
			for (int i = 0; i < get_stack_size(a) - target_pos_bottom; i++)
				strcpy(moves_bottom->seq[i], "rra");
			moves_bottom->total_moves = get_stack_size(a) - target_pos_bottom;
		}
		// Rotate B to bring bottom to top
		for (int i = 0; i < get_stack_size(b) - pos_bottom; i++)
			strcpy(moves_bottom->seq[moves_bottom->total_moves + i], "rrb");
		moves_bottom->total_moves += get_stack_size(b) - pos_bottom;
		strcpy(moves_bottom->seq[moves_bottom->total_moves], "pa");
		moves_bottom->total_moves++;

		// Choose minimal
		if (moves_top->total_moves <= moves_bottom->total_moves)
		{
			execute_moves(moves_top, a, b);
			free_moves(moves_top);
			free_moves(moves_bottom);
		}
		else
		{
			execute_moves(moves_bottom, a, b);
			free_moves(moves_top);
			free_moves(moves_bottom);
		}
	}

	// Final rotation: bring the smallest value to the top of A
	int min_pos = find_min_pos(a);
	if (min_pos <= get_stack_size(a) / 2)
	{
		for (int i = 0; i < min_pos; i++)
			do_ra(a, 1);
	}
	else
	{
		for (int i = 0; i < get_stack_size(a) - min_pos; i++)
			do_rra(a, 1);
	}
}

/**
 * - Heart
 */
void	large_sort(t_stack **a, t_stack **b, int size)
{
	t_moves			*moves;
	t_data			*data;
	unsigned int	chunk_i;

	data = malloc(sizeof(t_data));
	if (!data)
		error_free_exit(a, b);
	init_data_and_assign(a, size, data);
	// printf("--- Data: num_chunks: %u, total: %u\n", data->num_chunks, data->total_size);
	chunk_i = 0;
	while (get_stack_size(a) > 1)
	{
		moves = best_move(data, a, b, chunk_i);
		if (!moves)
		{
			chunk_i++;
			continue;
		}
		// printf("---- Selected move: ----\n");
		execute_moves(moves, a, b);
		free_moves(moves);
	}
	push_back_to_a(a, b);
	free_data(data);
	// if (is_sorted(a))
	// 	printf("Success!\n");
	// else
	// 	printf("Sucks\n");
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
		large_sort(a, b, get_stack_size(a));
}
