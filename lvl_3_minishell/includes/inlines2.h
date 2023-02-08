/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inlines2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:41:15 by roramos           #+#    #+#             */
/*   Updated: 2023/02/08 19:41:32 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INLINES2_H
# define INLINES2_H

static inline int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static inline int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

static inline bool	is_ascii(int c)
{
	if (c >= 0 && c <= 127)
		return (true);
	return (false);
}

static inline bool	is_digit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (true);
	return (false);
}

#endif