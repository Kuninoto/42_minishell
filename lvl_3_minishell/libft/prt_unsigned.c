/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:10:56 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/23 23:14:11 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned	int	u_digits(unsigned int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		digits += 1;
	}
	return (digits);
}

static void	put_uint(int n)
{
	char	digits[] = "0123456789";

	if (n > 9)
		put_uint(n / 10);
	write(STDOUT_FILENO, &digits[n % 10], 1);
}

int	prt_unsigned(unsigned int nbr)
{
	put_uint(nbr);
	return (u_digits(nbr));
}
