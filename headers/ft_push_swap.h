/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:56:21 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/06 10:58:13 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

typedef struct s_stack
{
	int				number;
	int				correct_idx;
	struct s_stack	*next;
}					t_stack;

# include <unistd.h>

int	is_valid_arg(char *arg);
int	are_valid_args(char **av);

t_stack	*stack_new_node(int number);
void stack_push_bottom(t_stack **stack, t_stack *new_node);
int	get_stack_size(t_stack **stack);

int	ft_isdigit(char c);
int	ft_issign(char c);

void	quicksort(int *arr, int low, int high);

#endif
