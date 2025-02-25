/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:44:11 by ckarsent          #+#    #+#             */
/*   Updated: 2024/11/22 08:52:14 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*c;

	if (start >= ft_strlen(s))
	{
		c = malloc(sizeof(char));
		if (!c)
			return (NULL);
		c[0] = '\0';
		return (c);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	c = malloc(sizeof(char) * (len + 1));
	if (!c || !s)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len)
	{
		c[i] = s[i + start];
		i++;
	}
	c[i] = '\0';
	return (c);
}
