/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:17:14 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/23 17:36:34 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef unsigned char		t_uchar;
typedef long long			t_llong;
typedef unsigned long long	t_ullong;
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//character functions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_iswhitespace(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

//string functions
char	*ft_strtolower(char *str);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strcat(char *dst, const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
int		ft_atoi_safe(const char *nptr, int *dst);
int		ft_atoll_safe(const char *nptr, t_llong *dst);
int		ft_atoi_base(const char *nptr, const char *radix);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t n);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(const char *str1, const char *str2);
char	*ft_strnjoin(const char *str1, const char *str2, size_t n);
char	*ft_strtrim(const char *str, const char *set);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *str, char (*f)(unsigned int, char));
void	ft_striteri(char *str, void (*f)(unsigned int, char *));

//array of string functions
char	**ft_split(const char *str, char *charset);
char	**ft_qsplit(const char *str, char *charset);
void	ft_strarr_free(char **strarr);
size_t	ft_strarr_len(char *const *strarr);
char	**ft_strarr_dup(char *const *strarr);
char	**ft_strarr_join(char *const *strarr1, char *const *strarr2);

//memory functions
void	*ft_memset(void *s, int c, size_t n);
void	ft_memswap(void *a, void *b, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

//put functions
void	ft_putchar_fd(const char c, int fd);
int		ft_putstr_fd(const char *str, int fd);
int		ft_putendl_fd(const char *str, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstrarr_fd(char *const *strarr, int fd);

//list functions
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//algos
void	ft_qsort(void *base, size_t nmemb, size_t size,
			int (*compare)(const void *, const void *));

//math
double	ft_decimal_round(double nbr, int decimals);
double	ft_deg_to_rad(double angle);
int		ft_get_sign(double nbr);

//more complex functions
char	*get_next_line(int fd);

#endif
