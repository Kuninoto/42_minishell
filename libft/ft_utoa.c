/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:07:18 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/19 23:24:17 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_digits(unsigned int n)
{
	unsigned int	digits;

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

char	*ft_utoa(unsigned int n)
{
	unsigned int	digits;
	char			*result;

	digits = ft_digits(n);
	result = malloc((digits + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[digits--] = '\0';
	if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		result[digits--] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
