/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:54:26 by jchuah            #+#    #+#             */
/*   Updated: 2025/10/01 13:40:29 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *str, char *charset)
{
	int		word_count;
	char	quote;

	word_count = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
				str++;
			if (!*str)
			{
				word_count++;
				return (word_count);
			}
		}
		if (!ft_strchr(charset, *str) && ft_strchr(charset, *(str + 1)))
			word_count++;
		str++;
	}
	return (word_count);
}

static char	*get_word(const char *str, char *charset)
{
	int		len;
	char	quote;

	len = 0;
	while (!ft_strchr(charset, str[len]))
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			quote = str[len];
			len++;
			while (str[len] && str[len] != quote)
				len++;
			if (!str[len])
				break ;
		}
		len++;
	}
	return (ft_strndup(str, len));
}

static void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

//ft_split but ignores delimiters in "" or '' quotes
//returns NULL if a quote is included in the charset
char	**ft_qsplit(const char *str, char *charset)
{
	int		word_count;
	char	**words;
	int		i;

	if (!str || !charset
		|| ft_strchr(charset, '\'') || ft_strchr(charset, '\"'))
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
		if (!words[i])
			return (free_words(words), NULL);
		str += ft_strlen(words[i]);
		i++;
	}
	words[i] = NULL;
	return (words);
}
