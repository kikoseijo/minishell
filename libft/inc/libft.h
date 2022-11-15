/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:48:21 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/14 11:35:47 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*
** Part 1 - Libc functions (23)
*/

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strchr(char *s, int c);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

/*
** Additional functions (11)
*/

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_concat_char(char *str, char c);

/*
** TIME
*/

long				ft_get_time(void);

/*
** Bonus part (9)
*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/*
** Extra Functions
*/
int					ft_str_is_numeric(char *str);
void				ft_free_array(char **array);
int					ft_isset(char const c, char const *set);
int					ft_array_len(char **array);
char				**ft_array_join(char **a, char **b);
int					ft_strcmp(const char *s1, const char *s2);

/*
** GET NEXT LINE
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char				*get_next_line(int fd);

/*
** FT_PRINTF
*/

typedef struct s_print
{
	int				str_len;
	char			*str;
	int				width;
	int				points;
	int				precision;
	va_list			args;
}					t_print;

int					ft_printf(const char *format, ...);
void				ft_print_p(t_print *model, unsigned long long nb);
void				ft_print_int(t_print *model, int nb);
void				ft_print_uint(t_print *model, unsigned int nb);
void				ft_print_x(t_print *m, unsigned int nb);

#endif
