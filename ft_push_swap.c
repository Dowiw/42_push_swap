/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:57:59 by kmonjard          #+#    #+#             */
/*   Updated: 2025/07/31 11:36:22 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf only

#include <unistd.h> // write, malloc
#include <stdlib.h> // malloc, free, exit

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

static int	write_error() {
	write(STDERR_FILENO, "Error\n", 6);
	return (1);
}

// int argc, char **argv
int main(void) {
	return (write_error());
}



