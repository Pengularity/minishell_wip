/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:08:10 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/23 14:54:22 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = c;
	return (s);
}

void	*memset_malloc(int c, size_t len)
{
	void	*point;

	point = malloc(len);
	if (!point)
		return (NULL);
	point = ft_memset(point, c, len);
	return (point);
}
