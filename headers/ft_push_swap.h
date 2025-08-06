/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:56:21 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/06 14:29:50 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

typedef struct s_stack
{
	int				number;
	int				index;
	struct s_stack	*next;
}					t_stack;

# include <unistd.h>

#endif
