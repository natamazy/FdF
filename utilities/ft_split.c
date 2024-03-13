/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:06:08 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/13 22:05:02 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]) == -1)
		{
			count++;
			while (s[i] && ft_isspace(s[i]) == -1)
				i++;
		}
		else if (ft_isspace(s[i]) == 1)
			i++;
	}
	return (count);
}

size_t	get_word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]) == -1)
		i++;
	return (i);
}

void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

char	**split_helper(char const *s, char c, char **array, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (s[j] && s[j] == c)
			j++;
		array[i] = ft_substr(s, j, get_word_len(&s[j], c));
		if (!array[i])
		{
			free_array(i, array);
			return (NULL);
		}
		while (s[j] && ft_isspace(s[i]) == -1)
			j++;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = (char **) malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = split_helper(s, c, array, words);
	return (array);
}
