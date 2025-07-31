/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:15:17 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/31 09:21:57 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	int		nbr;

	nbr = n;
	len = 0;
	if (!n)
		len++;
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = 0;
	len--;
	while (len >= 0)
	{
		ptr[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (ptr);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1[i])
		ptr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[j++] = s2[i++];
	ptr[j] = 0;
	return (ptr);
}

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	if (!s1 && !s2 && !s3)
		return (ft_strdup(""));
	temp = ft_strjoin(s1, s2);
	if (!s3)
		return (temp);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}
