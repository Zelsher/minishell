/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:56:25 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/10 15:16:32 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef M_ENVP_LEN
#  define M_ENVP_LEN 100
# endif

# ifndef CMD_ARG_LEN
#  define CMD_ARG_LEN 201
# endif

# include "../Libft/libft.h"
# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_command
{
	int					invalid;
	int					type;
	char				invalid_token;
	char				token;
	char				*cmd;
	char				*heredoc;
	char				*arg[CMD_ARG_LEN];
	char				*p_file;
	char				*p_opt;
	struct s_command	*left;
	struct s_command	*right;
}					t_command;

typedef struct s_mshell
{
	struct s_command	*command;
	char				**m_envp;
	char				*new_command;
	size_t				line;
}					t_mshell;

typedef struct s_parse
{
	size_t	i;
	size_t	j;
	int		quote;
}					t_parse;

typedef struct s_piper
{
	int				pipe[2];
	int				new_pipe[2];
	int				*pid;
	int				i;
}					t_piper;

extern int	g_exec_pid;

/*Parsing_utils*/
t_command	*cmd_construct(t_mshell *m_shell, char first_cmd);
void		parse_construct(t_parse *parse);
void		skip_ispace(char *new_command, t_parse *parse);
void		ft_print_command_tree(t_command *command, char *branch, int i);
void		print_cmd(t_command *command, int a);

/*Parsing*/
int			nothing_left(char *new_command);
t_command	*put_p_arg(t_command *command);
int			cmd_verifier(t_command *command, int *wstatus);
char		*arg_malloc(t_command *command, char *new_command, char **m_envp);
t_command	*cmd_filler(t_mshell *m_shell, char *new_command,
				t_command *command, char token);
t_command	*cmd_parse(t_mshell *m_shell, char *new_command,
				char **m_envp, int *wstatus);
int			tokener(char *new_command, t_command *command, int *j,
				char *tokens);

/*ENVP*/
void		envp_print(char	**m_envp);
void		envp_cpy(char **m_envp, char **envp);
char		*find_var_envp(char **m_envp, char *var, int verif);
void		unset_envp(char **m_envp, char *cmd);
int			export_envp(char **m_envp, char *cmd);

/*Heredoc*/
void		return_parse_error(t_command *command);
char		*generate_file(size_t *count);
char		*find_delimiter(char *new_command, t_parse *parse);
int			create_heredoc_line(char *reader,
				char *here_doc_line, char **m_envp);
char		*malloc_heredoc_line(char *reader, char **m_envp);
int			heredoc(t_mshell *m_shell, t_command *command,
				t_parse *parse, char *new_command);

/*History*/
int			is_last_cmd(const char *new_command);
void		print_history(void);

/*exec*/
void		ft_exec(t_command *command, char **envp, int *wstatus);
void		wait_pid(int *pid, int *wstatus);
int			*create_new_pid_list(t_piper *piper);
void		end_pipe(t_command *command, char **m_envp,
				t_piper *piper, int *wstatus);
int			piper(t_command *command, char **m_envp,
				int *wstatus, t_command *p_command);

/*Builtins*/
void		ft_env(char **m_envp);
void		ft_echo(t_command *command);
void		ft_cd2(t_command *command, char **m_envp, int *wstatus);
void		ft_cd(t_command *command, char **m_envp, int *wstatus);
int			built_in(t_command *command, char **m_envp, int *wstatus);

/*ENVP exec*/
void		ft_env(char **m_envp);
void		ft_unset(t_command *command, char **m_envp, int *wstatus);
void		ft_export(t_command *command, char **m_envp, int *wstatus);
int			shlvlup(char **m_envp);

/*Pathfinder*/
int			match_path_count(char *command, char **path);
char		**putlastslash(char **path);
char		*pathfinder(t_command *command, char **m_envp, int *flag);

/*Exit*/
void		ft_exit3(t_command *command, char **m_envp, int flag);
void		ft_exit2(t_command *command, char **m_envp, int *wstatus, int i);
void		ft_exit(t_command *command, char **m_envp, int *wstatus);

/*Redir*/
void		redir_output_append(t_command *command,
				char **m_envp, int *wstatus);
void		redir_output(t_command *command, char **m_envp, int *wstatus);
void		redir_input(t_command *command, char **m_envp, int *wstatus);
void		redir_heredoc(t_command *command, char **m_envp, int *wstatus);

/*Signal*/
void		singal_handler(int signal);
int			init_receive_signal(struct sigaction *sa,
				struct sigaction *sa_quit);
int			init_child_signal(struct sigaction *sa);

/*Free*/
void		free_command(t_command *command);
void		ft_free(t_command *command, char *new_command,
				char **m_envp, int m_exit);
void		return_parse_error(t_command *command);
void		free_single_command(t_command *command);

/*Minishell*/
int			ft_builtins(t_command *command, int *wstatus, char **m_envp);
void		printerr(int fd, char *name, const char *error, int flag);
int			update_wstatus(char **m_envp, int *wstatus, int flag);
int			minishell(t_mshell *m_shell, int *wstatus);

#endif
