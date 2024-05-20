#ifndef MINISHELL_H
#define MINISHELL_H

#define TC_B_RED  "\x1B[0;31m"
#define TC_NRM  "\x1B[0m"
#define TC_RED  "\x1B[1;31m"
#define TC_GRN  "\x1B[1;32m"
#define TC_YEL  "\x1B[1;33m"
#define TC_BLU  "\x1B[1;34m"
#define TC_MAG  "\x1B[1;35m"
#define TC_CYN  "\x1B[1;36m"
#define TC_WHT  "\x1B[1;37m"

#  define M_ENVP_LEN 100
#  define CMD_ARG_LEN 201

#include "../Libft/libft.h"
#include <dirent.h>
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_command
{
	int					invalid;
	int					type;
	char				invalid_token;
	char				token;//correspond au token, et [&& = e] [|| = p] [>> = r] les autres donneront u
	char				*cmd;
	char				**heredoc;
	char				*arg[201];
	int					quote[201];
	char				*p_file;
	char				*p_opt;
	char				*p_new_command;
	struct s_command	*left;
	struct s_command	*right;
}					t_command;

typedef struct s_parse
{
	size_t	i;
	size_t	j;
	int	quote;
}					t_parse;

extern int g_exec_pid;

/*Parsing_utils*/
t_command	*CMD_Construct(char *new_command);
void		PARSE_Construct(t_parse *parse);
void		skip_ispace(char *new_command, t_parse *parse);
void    	ft_print_command_tree(t_command *command, char *branch, int i);

char		*pathfinder(t_command *command, char **m_envp, int *flag);

/*Parsing*/
t_command	*PUT_P_Arg(t_command *command);
int 		CMD_Verifier(t_command *command, int *wstatus);
char		*ARG_Malloc(t_command *command, char *new_command, char **m_envp);
t_command	*CMD_Filler(char *new_command, t_command *command, char **m_envp);
t_command   *CMD_Parse(char *new_command, char **m_envp, int *verif);

/*ENVP*/
void		ENVP_Print(char	**m_envp);
void		ENVP_Cpy(char **m_envp, char **envp);
char		*FIND_Var_Envp(char **m_envp, char *var, int verif);
void		UNSET_Envp(char **m_envp, char *cmd);
int			EXPORT_Envp(char **m_envp, char *cmd);

/*Heredoc*/
int			CREATE_Heredoc_Line(char *reader, char *here_doc_line, char **m_envp);
char		*MALLOC_Heredoc_Line(char *reader, char **m_envp);
void		HEREDOC(t_command *command, char **m_envp, int *wstatus);

/*History*/
int			IS_Last_Cmd(const char *new_command);
void		PRINT_History();

/*exec*/
void		ft_exec(t_command *command, char **envp, int *wstatus);

/*Builtins*/
void	ft_echo(t_command *command);
void	ft_cd2(t_command *command, char **m_envp, int *wstatus);
void	ft_cd(t_command *command, char **m_envp, int *wstatus);
int		built_in(t_command *command, char **m_envp, int *wstatus);

/*ENVP exec*/
void	ft_env(char **m_envp);
void	ft_unset(t_command *command, char **m_envp);
void	ft_export(t_command *command, char **m_envp, int *wstatus);
void	shlvlup2(char **m_envp, char *temp_num, int i);
void	shlvlup(char **m_envp);

/*Pathfinder*/
int	match_path_count(char *command, char **path);
char	**putlastslash(char **path);
char	*pathfinder(t_command *command, char **m_envp, int *flag);

/*Exit*/
void	ft_exit3(t_command *command, char **m_envp, int flag);
void	ft_exit2(t_command *command, char **m_envp, int *wstatus, int i);
void	ft_exit(t_command *command, char **m_envp, int *wstatus);

/*Redir*/
void	redir_output_append(t_command *command, char **m_envp, int *wstatus);
void	redir_output(t_command *command, char **m_envp, int *wstatus);
void	redir_input(t_command *command, char **m_envp, int *wstatus);

/*Signal*/
void		SIGNAL_Handler(int signal);
int			INIT_Receive_Signal(struct sigaction *sa);

/*Free*/
void		FREE_Command(t_command *command);
void		ft_free(t_command *command, char *new_command, char **m_envp, int m_exit);

/*Minishell*/
int			ft_builtins(t_command *command, int *wstatus, char **m_envp);
void		printerr(int fd, char *name, const char *error, int flag);
int			UPDATE_Wstatus(char **m_envp, int *wstatus, int flag);
void		minishell(char **m_envp);

#endif
