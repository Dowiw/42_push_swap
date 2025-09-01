/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:16:55 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/12 10:16:57 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

/**
 * - Allocates a new node, and takes prev node
 * - node->number = number, index = 0, next = NULL
 * - Returns NULL in malloc error
 */
t_stack	*stack_new_node(int number, t_stack *prev)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->number = number;
	node->correct_idx = 0;
	node->chunk_id = 0;
	node->next = NULL;
	if (!prev)
		node->prev = NULL;
	else
		node->prev = prev;
	return (node);
}

/**
 * - Puts node to the bottom of a stack
 * - Exits when new node is empty
 */
void	stack_push_bottom(t_stack **stack, t_stack *node)
{
	t_stack	*cursor;

	if (!node)
		return ;
	if (!*stack)
	{
		*stack = node;
		node->prev = NULL;
		return ;
	}
	cursor = *stack;
	while (cursor->next != NULL)
		cursor = cursor->next;
	cursor->next = node;
	node->prev = cursor;
	node->next = NULL;
}

/**
 * - Push a node to the top
 * - Sets prev of current top to node
 * - Exits if node is empty
 */
void	stack_push_top(t_stack **stack, t_stack *node)
{
	if (!node)
		return ;
	node->next = *stack;
	node->prev = NULL;
	if (*stack)
		(*stack)->prev = node;
	*stack = node;
}

/**
 * - Returns stack size in int
 */
int	get_stack_size(t_stack **stack)
{
	int		count;
	t_stack	*cursor;

	count = 0;
	cursor = *stack;
	while (cursor != NULL)
	{
		cursor = cursor->next;
		count++;
	}
	return (count);
}
