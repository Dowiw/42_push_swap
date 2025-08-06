/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:57:59 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/06 11:00:42 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf only

#include <unistd.h> // write, malloc
#include <stdlib.h> // malloc, free, exit

#include "headers/ft_push_swap.h"

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

int main(int ac, char **av) {
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (ac < 2)
		return (0);
	else if (!are_valid_args(av))
		error_free_exit(NULL, NULL);
}
