/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:54:26 by jchuah            #+#    #+#             */
/*   Updated: 2025/10/14 15:16:00 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *str, char *charset)
{
	int	word_count;

	word_count = 0;
	while (*str)
	{
		if (!ft_strchr(charset, *str) && ft_strchr(charset, *(str + 1)))
			word_count++;
		str++;
	}
	return (word_count);
}

static char	*get_word(const char *str, char *charset)
{
	int		len;
	char	*word;

	len = 0;
	while (!ft_strchr(charset, str[len]))
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	word[len] = '\0';
	while (len--)
		word[len] = str[len];
	return (word);
}

static void	*free_words(char **words, int count)
{
	while (count--)
		free(words[count]);
	free(words);
	return (NULL);
}

char	**ft_split(const char *str, char *charset)
{
	int		word_count;
	char	**words;
	int		i;

	if (!str || !charset)
		return (NULL);
	word_count = count_word(str, charset);
	words = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (ft_strchr(charset, *str))
			str++;
		words[i] = get_word(str, charset);
		if (!words[i++])
			return (free_words(words, i));
		while (!ft_strchr(charset, *str))
			str++;
	}
	words[i] = NULL;
	return (words);
}
