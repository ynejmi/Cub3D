/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmods1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:34:39 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:34:40 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	int		i;
	char	*ptr;

	i = -1;
	if (!s)
		return (0);
	if (!(ptr = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (s[start] && i < (int)len - 1)
		ptr[++i] = s[start++];
	ptr[++i] = '\0';
	return (ptr);
}

char	*ft_strdup(char *s1)
{
	int		lensrc;
	char	*ptr;
	int		i;

	i = -1;
	lensrc = (int)ft_strlen(s1);
	if (!(ptr = malloc(sizeof(char) * (lensrc + 1))))
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, int c, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	if (!s1)
		return (NULL);
	if (!(ret = malloc(sizeof(char) * (ft_strlen(s2) + ft_strlen(s1) + 2 + c))))
		return (0);
	if (s1 != NULL)
	{
		while ((ret[i] = s1[i]))
			i++;
		if (c)
			ret[i++] = '\n';
	}
	j = 0;
	if (s2 != NULL)
		while ((ret[i++] = s2[j]))
			j++;
	free(s1);
	free(s2);
	ret[i] = '\0';
	return (ret);
}

int		ft_split(char *src, char **d1, char **d2, int spx)
{
	int		l;

	l = ft_strlen(src);
	if (spx < 0)
		spx = ft_strlen(src);
	*d1 = ft_substr(src, 0, spx);
	if (l != spx)
		*d2 = ft_substr(src, spx + 1, l - spx);
	else
		*d2 = NULL;
	free(src);
	return (1);
}
