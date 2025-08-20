/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:12:31 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/20 13:12:32 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_stack	*temp;
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (ac < 2)
		return (0);
	else if (!are_valid_args(av))
		error_free_exit(NULL, NULL);
	stack_a = NULL;
	stack_b = NULL;
	fill_stack_a(&stack_a, ac, av);
	do_push_swap(&stack_a, &stack_b);
	while (stack_a)
	{
		temp = stack_a->next;
		free(stack_a);
		stack_a = temp;
	}
	return (0);
}
