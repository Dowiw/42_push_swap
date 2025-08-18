/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:02:25 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/17 18:02:27 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

/**
 * - Helper
 * - Puts correct index into stack nodes
 */
static void	put_index(int *arr, int size, t_stack **stack_a)
{
	int		i;
	t_stack *cursor;

	i = 0;
	cursor = *stack_a;
	while (cursor != NULL)
	{
		i = 0;
		while (i < size)
		{
			if (cursor->number == arr[i])
			{
				cursor->correct_idx = i;
				break ;
			}
			i++;
		}
		cursor = cursor->next;
	}
}

/**
 * - Gets correct index of stack nodes (for radix)
 * - Does quicksort to the stack in an int array
 * - Allocates int array (protected)
 */
void	get_index(t_stack **stack_a)
{
	int	size;
	int	i;
	int	*arr;
	t_stack	*cursor;

	size = get_stack_size(stack_a);
	i = 0;
	cursor = *stack_a;
	arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		error_free_exit(stack_a, NULL);
	while (cursor != NULL && i < size)
	{
		arr[i] = cursor->number;
		cursor = cursor->next;
		i++;
	}
	quicksort(arr, 0, size - 1);
	put_index(arr, size, stack_a);
	free(arr);
}
