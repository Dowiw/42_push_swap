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
	return (current);
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
		return (3);
	else if (size <= 100)
		return (3);
	else if (size <= 200)
		return (4);
	else if (size <= 500)
		return (14);
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
 * - Perform Turk when pushing back to a
 */
void push_back_to_a(t_stack **a, t_stack **b)
{
	while (get_stack_size(b) > 0)
	{
		// 1. Find largest chunk_id in B
		int max_chunk_id = -1;
		int pos = 0, pos_top = -1, pos_bottom = -1;
		t_stack *cur = *b;
		int size_b = get_stack_size(b);
		while (cur)
		{
			if ((int)cur->chunk_id > max_chunk_id)
				max_chunk_id = cur->chunk_id;
			cur = cur->next;
		}

		// 2. Find top and bottom node with max_chunk_id
		t_stack *top_node = NULL, *bottom_node = NULL;
		cur = *b;
		pos = 0;
		while (cur)
		{
			if ((int)cur->chunk_id == max_chunk_id)
			{
				if (!top_node)
				{
					top_node = cur;
					pos_top = pos;
				}
				bottom_node = cur;
				pos_bottom = pos;
			}
			cur = cur->next;
			pos++;
		}

		// 3. Calculate moves for top_node
		int target_pos_a_top = find_target_pos_a(a, top_node->number);
		int size_a = get_stack_size(a);
		int moves_a_top = (target_pos_a_top <= size_a / 2) ? target_pos_a_top : target_pos_a_top - size_a;
		int moves_b_top = (pos_top <= size_b / 2) ? pos_top : pos_top - size_b;
		int common_top = 0;
		if (moves_a_top > 0 && moves_b_top > 0)
			common_top = (moves_a_top < moves_b_top) ? moves_a_top : moves_b_top;
		else if (moves_a_top < 0 && moves_b_top < 0)
			common_top = (moves_a_top > moves_b_top) ? moves_a_top : moves_b_top;
		int total_moves_top = abs(moves_a_top) + abs(moves_b_top) - abs(common_top);

		// 4. Calculate moves for bottom_node
		int target_pos_a_bottom = find_target_pos_a(a, bottom_node->number);
		int moves_a_bottom = (target_pos_a_bottom <= size_a / 2) ? target_pos_a_bottom : target_pos_a_bottom - size_a;
		int moves_b_bottom = (pos_bottom <= size_b / 2) ? pos_bottom : pos_bottom - size_b;
		int common_bottom = 0;
		if (moves_a_bottom > 0 && moves_b_bottom > 0)
			common_bottom = (moves_a_bottom < moves_b_bottom) ? moves_a_bottom : moves_b_bottom;
		else if (moves_a_bottom < 0 && moves_b_bottom < 0)
			common_bottom = (moves_a_bottom > moves_b_bottom) ? moves_a_bottom : moves_b_bottom;
		int total_moves_bottom = abs(moves_a_bottom) + abs(moves_b_bottom) - abs(common_bottom);

		// 5. Choose best option
		int use_top = (total_moves_top <= total_moves_bottom);

		// 6. Execute moves
		int moves_a = use_top ? moves_a_top : moves_a_bottom;
		int moves_b = use_top ? moves_b_top : moves_b_bottom;
		int common = use_top ? common_top : common_bottom;

		// Perform common rotations
		while (common > 0)
		{
			do_rr(a, b);
			moves_a--;
			moves_b--;
			common--;
		}
		while (common < 0)
		{
			do_rrr(a, b);
			moves_a++;
			moves_b++;
			common++;
		}
		// Finish remaining rotations for A
		while (moves_a > 0) { do_ra(a, 1); moves_a--; }
		while (moves_a < 0) { do_rra(a, 1); moves_a++; }
		// Finish remaining rotations for B
		while (moves_b > 0) { do_rb(b, 1); moves_b--; }
		while (moves_b < 0) { do_rrb(b, 1); moves_b++; }

		// Push from B to A
		do_pa(b, a);
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

int	check_opposite(t_stack *a)
{
	int	s_size;
	int	count;
	int	diff;

	diff = 0;
	count = 0;
	s_size = get_stack_size(&a);
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
 * - Get moves of the closest node in chunk_i from the bottom or top
 * - Pick which one is best in a way that puts it into stack b where one
 *  half of the chunk is on top and the other on the bottom
 */
void best_move(t_stack **a, t_stack **b, int range)
{
	unsigned int		i;

	i = 0;
	while (get_stack_size(a) > 0)
	{
		if ((*a)->correct_idx >= i && (*a)->correct_idx <= i + range)
		{
			do_pb(a, b);
			if ((*a)->correct_idx > i + range / 2)
				do_rb(b, 1);// push to bottom half
			i++;
		}
		else if (check_opposite(*a))
			do_rra(a, 1);
		else
			do_ra(a, 1);
	}
}

/**
 * - Heart
 */
void	large_sort(t_stack **a, t_stack **b, int size)
{
	unsigned int	i = 0;
	int	range = 37;
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (!data)
		error_free_exit(a, b);
	init_data_and_assign(a, size, data);
	while (get_stack_size(a) > 1)
	{
		if ((*a)->correct_idx <= i)
		{
			do_pb(a, b);
			do_rb(b, 1);
			++i;
		}
		else if ((*a)->correct_idx <= i + range)
		{
			do_pb(a, b);
			++i;
		}
		else if (check_opposite(*a))
			do_rra(a, 1);
		else
			do_ra(a, 1); // about 2200
	}
	push_back_to_a(a, b);
	free_data(data);
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
