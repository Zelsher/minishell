/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:55:42 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/07 18:55:42 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
/*t_list		ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *)); 
*/

int				ft_atoi(const char *str);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_isprint(int c);
int				ft_isdigit(int c);
int				ft_isascii(int c);
int				is_quote(char c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_iswspace(char c);
int				ft_isminorplus(char c);
int				is_in(char c, char *str);
int				ft_is_str_num(char *str);
int				ft_power(int number, int power);
int				ft_nbrlen(long long int num);
long long int	ft_nbr_reducer(long long int nbr, int digit);
long long int	ft_nbr_max_pos(long long int nbr);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);

char			*ft_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *src);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_find_str_in_str(char *str, char *searched);
char			*ft_strnstr(const char *haystack, const char *needle, size_t n);
char			*ft_substr(const char *str, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strtrim(const char *s1, const char *set);
char			**ft_split(const char *str, char c);
char			**ft_free_double_tab(char **str);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void			ft_putstr(char *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *str, int fd);
void			ft_putendl_fd(char *str, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_striteri(char *str, void (*f)(unsigned int, char *));

void			*ft_memset(void *ptr, int n, size_t count);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			ft_bzero(void *ptr, size_t n);
void			*ft_calloc(size_t n, size_t size);

void			*ft_memchr(const void *ptr, int ch, size_t count);

/*Printf*/

int				ft_print_c(int c);
int				ft_print_s(char *s);
int				ft_print_p(unsigned long int p);
int				ft_print_d(int d);
int				ft_print_i(int i);
int				ft_print_u(unsigned int u);
int				ft_print_x(unsigned int x);
int				ft_print_maj_x(unsigned int X);
int				ft_putnbr(int n, int i);
int				ft_putnbr_unsigned_int(unsigned int n, int i);

char			*ft_putptr(unsigned long int n);
char			*ft_int_to_hexa(unsigned int n);

int				ft_printf(const char *str, ...);

/*Printf_error*/

int				ft_print_c_error(int c);
int				ft_print_s_error(char *s);
int				ft_print_p_error(unsigned long int p);
int				ft_print_d_error(int d);
int				ft_print_i_error(int i);
int				ft_print_u_error(unsigned int u);
int				ft_print_x_error(unsigned int x);
int				ft_print_maj_x_error(unsigned int X);
int				ft_putnbr_error(int n, int i);
int				ft_putnbr_unsigned_int_error(unsigned int n, int i);

char			*ft_putptr_error(unsigned long int n);
char			*ft_int_to_hexa_error(unsigned int n);

int				ft_printf_error(const char *str, ...);

/*GNL*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char			*get_next_line(int fd);

/*random*/

//#include <fcntl.h>
//int				ft_random_seed(long long int seed);
//long long int   ft_random(int seed, long long int max, int sign);
/*len : la longeur du nombre, signe : boolean pour activer ou non les signes*/

#endif