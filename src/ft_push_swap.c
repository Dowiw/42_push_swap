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

#include "headers/ft_push_swap.h"

typedef struct s_stack
{
	int				number;
	int				index;
	struct s_stack	*next;
}					t_stack;


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
	if (stack_a && stack_b);
}

/**
 * - Checks if character is a digit
 * - `c >= '0' && c <= '9'`
 */
int	isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * - Checks if character is a sign
 * - `c == '+' || c == '-'`
 */
int issign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

/**
 * - Checker that looks for valid integers in an arg
 * - Each int: skips space ' ', a sign '+' '-' and digits
 * - Returns 0 if anything else is found
 */
int	is_valid_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] != '\0')
	{
		while (arg[i] == ' ')
			i++;
		if (issign(arg[i]))
			i++;
		if (!isdigit(arg[i]))
			return (0);
		while (isdigit(arg[i]))
			i++;
		if (arg[i] && arg[i] != ' ')
			return (0);
	}
	return (1);
}

/**
 * - Checks for valid arguments in ./push_swap ...
 * - Will check for ./push_swap "" (return error)
 * - Will check each argument ac > 2
 */
int	are_valid_args(char **av)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	while (av[i][j] == ' ')
		j++;
	if (av[i][j] == '\0')
		return (0);
	while (av[i] != NULL)
	{
		if (!is_valid_arg(av[i]))
			return (0);
		i++;
	}
	return (1);
}

t_stack	*stack_new(int number)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->number = number;
	node->index = 0;
	node->next = NULL;
}

/**
 * - Similar to stack push
 * - Puts the new node on the top
 */
void stack_push(t_stack **stack, t_stack *new_node)
{
	if (!stack || !new_node)
		return ;
	new_node->next = *stack;
	*stack = new_node;
}

// Helper: free the stack
void stack_free(t_stack **stack)
{
	t_stack *tmp;
	while (stack && *stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

/**
 * - Main logic for filling up the stack
 * - Checks for overflow/underflow
 * - Checks for errors
 */
int	ft_atoi_pushswap(const char *arg, int *error)
{
	long	value;
	int		sign;

	value = 0;
	sign = 1;
	while (*arg == ' ')
		arg++;
	if (*arg == '-' || *arg == '+')
		if (*arg++ == '-')
			sign = -1;
	if (!(*arg >= '0' && *arg <= '9'))
		*error = 1;
	while (*arg >= '0' && *arg <= '9')
	{
		value = value * 10 + (*arg - '0');
		if ((sign == 1 && value > 2147483647)
			|| (sign == -1 && value < -2147483648))
			*error = 1;
	}
	if (*arg != '\0')
		*error = 1;
	return ((int)(sign * value));
}

/**
 * - Function that fills up stack A
 * - Allocates node for a number (protected)
 * - Protects duplicates & int overflow/underflow
 */
void	fill_stack_a(t_stack **stack_a, int ac, const char **av)
{
	int		i;
	int		value;
	int		error;
	t_stack	*node;

	i = 1;
	error = 0;
	while (i < ac)
	{
		value = ft_atoi_pushswap(av[i], &error);
		if (error)
			error_free_exit(stack_a, NULL);
		node = stack_new(value);
		if (!node)
			error_free_exit(stack_a, NULL);
		stack_push(stack_a, node);
		i++;
	}
}

int main(int ac, char **av) {
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (ac < 2)
		return (0);
	else if (!are_valid_args(av))
		error_free_exit(NULL, NULL);
	fill_stack_a(stack_a, ac, av);
	stack_b = NULL;
	push_swap(stack_a, stack_b);
}
