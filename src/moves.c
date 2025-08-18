/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:11:32 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/17 17:11:33 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	do_sa(t_stack **stack_a)
{
	t_stack *temp;
	t_stack	*cursor;

	temp = *stack_a;
	cursor = *stack_a;
	cursor = cursor->next;
	cursor = temp;
	write(1, "sa\n", 3);
}
