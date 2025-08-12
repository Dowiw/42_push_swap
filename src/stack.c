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
 * - Allocates a new node
 * - node->number = number, index = 0, next = NULL
 * - Returns NULL in malloc error
 */
t_stack	*stack_new_node(int number)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->number = number;
	node->index = 0;
	node->next = NULL;
	return (node);
}

/**
 * - Puts node to the bottom of a stack
 * -
 */
void stack_push_bottom(t_stack **stack, t_stack *new_node)
{
	t_stack *cursor;

	if (!new_node)
		return ;
	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	cursor = *stack;
	while (cursor->next != NULL)
		cursor = cursor->next;
	cursor->next = new_node;
	new_node->next = NULL;
}
