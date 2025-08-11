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

#include "../headers/ft_push_swap.h"

typedef struct s_stack
{
	int				number;
	int				index;
	struct s_stack	*next;
}					t_stack;

//Helper function that helps count number of strings in s
static size_t	count_str(char const *s, char c)
{
	size_t	out;

	out = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			out++;
		while (*s && *s != c)
			s++;
	}
	return (out);
}

//Copies a mem_area src to another mem_area dest based on size
static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_area;
	unsigned char	*dest_area;

	i = 0;
	if (src == NULL && dest == NULL)
		return (dest);
	src_area = (unsigned char *)src;
	dest_area = (unsigned char *)dest;
	while (i < n)
	{
		dest_area[i] = src_area[i];
		i++;
	}
	return (dest);
}

//Helper function that puts string into out[i] from its index start to its end
static char	*dup_str(const char *start, const char *end)
{
	char	*string;
	size_t	len;

	len = (size_t)end - (size_t)start;
	string = malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	ft_memcpy(string, start, len);
	string[len] = '\0';
	return (string);
}

//Helper function to fill array
static int	fill_array(char **out, const char *s, char c)
{
	size_t		i;
	const char	*start;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = s;
			while (*s && *s != c)
				s++;
			out[i] = dup_str(start, s);
			if (!out[i])
			{
				while (i--)
					free(out[i]);
				return (0);
			}
			i++;
		}
	}
	out[i] = NULL;
	return (1);
}

//Splits str s into a mallocated array of strings based on delimiter c
char	**ft_split(char const *s, char c)
{
	char	**out;

	if (!s)
		return (NULL);
	out = malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!out)
		return (NULL);
	if (!fill_array(out, s, c))
	{
		free(out);
		return (NULL);
	}
	return (out);
}

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

/**
 * - Checks if character is a digit
 * - `c >= '0' && c <= '9'`
 */
int	ft_isdigit(char c)
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
		if (!ft_isdigit(arg[i]))
			return (0);
		while (ft_isdigit(arg[i]))
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
	if (!av[i])
		return (0);
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

/**
 *
 */
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
int	ft_atoi_pushswap(char *arg, int *error)
{
	long	value;
	int		sign;

	value = 0;
	sign = 1;
	while (*arg == ' ')
		arg++;
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign *= -1;
		arg++;
	}
	if (!(*arg >= '0' && *arg <= '9'))
		*error = 1;
	while ((*arg >= '0' && *arg <= '9') && *arg != '\0')
	{
		value = value * 10 + (*arg - '0');
		if ((sign == 1 && value > 2147483647)
			|| (sign == -1 && value < -2147483648))
				*error = 1;
		arg++;
	}
	return ((int)(sign * value));
}

/**
 * - Function that fills up stack A
 * - Allocates node for a number (protected)
 * - Protects duplicates & int overflow/underflow
 */
void	fill_stack_a(t_stack **stack_a, int ac, char **av)
{
	int		i;
	int		value;
	int		error;
	t_stack	*node;

	i = 0;
	error = 0;
	node = NULL;
	value = 0;
	while (i < ac)
	{
		printf("fill stack >> i: %i, av[i]: %s\n", i, av[i]);
		value = ft_atoi_pushswap(av[i], &error);
		if (error)
			error_free_exit(stack_a, NULL);
		node = stack_new_node(value);
		if (!node)
			error_free_exit(stack_a, NULL);
		stack_push_bottom(stack_a, node);
		i++;
	}
}

int main() {
	char *test[] = {"./a.out", "1 2 3", NULL};
	printf("test: %i\n", are_valid_args(test));

	char **split = ft_split("1 -2 3 -4 5 6 1231312", ' ');
	for (int i = 0; split[i] != NULL; i++)
	{
		printf("num: %s\n", split[i]);
	}

	// check atoi
	char *atoi = "111 222 333 444";
	int error = 0;
	for (int index = 0; atoi[index] != '\0'; index++)
	{
		int val = ft_atoi_pushswap(atoi, &error);
		printf("val: %i, err: %i\n", val, error);
	}

	// check stack filler
	t_stack *stack;
	stack = NULL;
	int ac = 0;
	while (split[ac] != NULL)
		ac++;
	printf("number of nums (ac): %i\n", ac);

	printf("Calling fill_stack_a\n");
	fill_stack_a(&stack, ac, split);
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
	int i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
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
