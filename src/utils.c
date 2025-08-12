/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:15:31 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/12 10:15:32 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

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
int ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}
