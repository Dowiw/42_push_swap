/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:57:59 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/06 15:35:33 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf only

#include <unistd.h> // write, malloc
#include <stdlib.h> // malloc, free, exit

#include <limits.h>

#include "ft_push_swap.h"

// libft authorized and ft_printf

/**
 * Parameters:
 * - a stack of numbers with an executable as in:
 *   $> ./push_swap 5 3 4 2 1
 *   $> ./push_swap "5 3 4 2 1"
 *   $> ARG="5 3 4 2 1"; ./push_swap $ARG
 *
 *   results in a stack that looks like:
 *   5 - first argument on the top
 *   3
 *   4
 *   2
 *   1
 *
 * Return:
 * - prints out the instructions to STD_OUT along with a '\n'
 * - prints out "Error\n" for errors
 *
 * Checking:
 * - number of steps: wc -l
 * - if movements are valid, pipe ARG to check: ./checker_linux $ARG
 *  OK if good, KO if bad
 *
 * Errors:
 * - if empty parameters: ./push_swap ""
 * - ascii string c in parameters is not 0 >= c && c <= 9
 * - integer overflow for each number
 * - integers represented as words: "one"
 * - duplicates
 *
 * Others:
 * - if only one number in stack?
 * - if only executing? : ./push_swap
 *   - stops and does nothing (return to prompt)
 */

/**
 * - Function that writes `"Error\n"` to STDERR.
 * - Frees the allocated stacks.
 * - End: terminates the program with `exit(EXIT_FAILURE)`
 */
void	error_free_exit(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*cursor;

	cursor = NULL;
	while (stack_a && *stack_a)
	{
		cursor = (*stack_a)->next;
		free(*stack_a);
		*stack_a = cursor;
	}
	while (stack_b && *stack_b)
	{
		cursor = (*stack_b)->next;
		free(*stack_b);
		*stack_b = cursor;
	}
	exit(EXIT_FAILURE);
}

void	push_alloc_node(t_stack **stack_a, int num)
{
	t_stack	*node;

	node = stack_new_node(num);
	if (!node)
		error_free_exit(stack_a, NULL);
	stack_push_bottom(stack_a, node);
}

int	parse_and_push(t_stack **stack_a, char *s, int *j)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	while (s[*j] == ' ')
		(*j)++;
	if (s[*j] == '-' || s[*j] == '+')
	{
		if (s[*j] == '-')
			sign *= -1;
		(*j)++;
	}
	if (ft_isdigit(s[*j]))
	{
		while (ft_isdigit(s[*j]))
			num = num * 10 + (s[(*j)++] - '0');
		num *= sign;
		if (num < INT_MIN || num > INT_MAX)
			error_free_exit(stack_a, NULL);
		push_alloc_node(stack_a, num);
		return (1);
	}
	return (0);
}

/**
 * - Function that fills up stack A
 * - Allocates node for a number (protected)
 * - Protects duplicates & int overflow/underflow
 */
void	fill_stack_a(t_stack **stack_a, int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (av[i][j])
		{
			if (!parse_and_push(stack_a, av[i], &j))
				j++;
		}
		i++;
	}
}

int main() {
	char *test[] = {"./a.out", "1 2 3 4 5 6 7 8 9 10", NULL};
	printf("test: %i\n", are_valid_args(test));

	// check stack filler
	t_stack *stack;
	stack = NULL;
	int ac = 0;
	while (test[ac] != NULL)
		ac++;
	printf("number of nums (ac): %i\n", ac);

	printf("Calling fill_stack_a\n");
	fill_stack_a(&stack, ac, test);
	printf("Returned from fill_stack_a\n");

	t_stack *cursor = stack;
	int count = 0; // debug for infinite loop
	while (cursor != NULL)
	{
		printf("stack num: %i\n", cursor->number);
		cursor = cursor->next;
		count++;
		if (count > 100) break ;
	}

	// free everything
	// int i = 0;
	// while (test[i] != NULL)
	// {
	// 	free(split[i]);
	// 	i++;
	// }
	// free(split);
	error_free_exit(&stack, NULL);
}

// int main(int ac, char **av)
// {
// 	t_stack	*stack_a;
// 	t_stack	*stack_b;
// 	char	**temp;

// 	if (ac < 2)
// 		return (0);
// 	else if (!are_valid_args(av))
// 		error_free_exit(NULL, NULL);
// 	if (ac == 2)
// 	{

// 	}
// 	str = ft_split(av[1], ' ');
// 	fill_stack_a(&stack_a, ac, str);
// 	stack_b = NULL;
// 	while (cursor->next != NULL)
// 	{
// 		printf("num: %i", cursor->number);
// 		cursor = cursor->next;
// 	}
// }
