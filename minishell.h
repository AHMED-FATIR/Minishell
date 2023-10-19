/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:50:06 by afatir            #+#    #+#             */
/*   Updated: 2023/10/19 11:09:28 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft_gcl_ptf/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/time.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/types.h>
# define WORD 1
# define SEP 2
# define DEL 3
// # define LL long long

int	g_exit_status;

typedef struct s_env{
	char			*cmd;
	char			*str;
	int				v;
	struct s_env	*next;
}	t_env;
typedef struct s_list{
	char			*str;
	int				type;
	struct s_list	*next;
}	t_list;
typedef struct s_var{
	char		*c;
	char		*f;
	char		*str;
	int			j;
	int			k;
	int			b;
}	t_var;
typedef struct execution
{
	char	*oldpwd;
	char	*current_pwd;
	char	**splited_old_pwd;
	char	*new_pwd;
	char	*home_path;
	int		**array;
	char	*command;
	int		infile;
	int		outfile;
	t_env	**envs;
	pid_t	*array_of_pids;
	char	*joined;
	int		flag;
	pid_t	fd1;
	pid_t	fd2;
	int		fd;
	char	**envp;
	int		flag_1;
	int		flag_;
	t_list	*head;
	int		f;
	pid_t	fn;
	t_env	*head_cd;
	char	*buffer;
	int		status;
	int		j_cd;
	int		i_cd;
	int		pips[2];
	int		j_;
}	t_execution;
//signals.c
void		handler(int i);
void		ft_reset_hdl(void);
void		ft_reset_dfl(void);
void		ft_reset_ign(void);
// main.c
void		parsing(t_list *arg, t_env **envs, char **env);
void		eof_handling(char *cmd);
//env.c
char		**ft_fill_env(void);
t_env		*get_env(char **env, t_env *envs);
void		free_listt(t_env **list);
t_env		*ft_cr_listt(char *cmd, char *str, int i);
void		ft_add_endd(t_env **a, t_env *n);
// parcing.c
void		token_to(char *cmd, t_list **arg);
int			token(char **env, char *cmd, t_list **arg, t_env	**envs);
void		execution(char **env, t_list *arg, t_env **envs);
//linked_list.c
t_list		*ft_cr_list(char *cmd);
void		ft_add_end(t_list **a, t_list *n);
int			ft_strlen_stack(t_list **a);
void		free_list(t_list *list, char *cmd);
//separators.c
char		*ft_strndup(char *str, int start, int end);
int			get_index(int i, char *cmd);
int			handle_quote(t_list **arg, char *cmd, int i);
int			handle_sep(t_list **arg, char *cmd, int i);
int			is_char(t_list **arg, char *cmd, int i);
// quotes.c
int			quote_num(char *cmd, int flag);
char		*resize(char *cmd, int i, int b);
void		quote_rm(t_list **arg);
int			first_qoute(char *str);
int			check_nodes(t_list *arg);
//utils.c
void		print_nodes(t_list *arg);
char		**get_new_env(char **env);
int			not_sep(char c);
int			is_sep(char c, int x);
char		*dupping(char *str, char *p);
// expanding.c
int			expandable_in_herdoc(char *str);
char		*ft_free_expand(t_var *v);
int			ft_check_heredoc(t_list *arg);
char		*expander(char *cmd, t_env **env);
void		expanding(t_list **arg, t_env **envs);
// expanding2.c
int			get_expande(char *cmd, int i, t_env **env, t_var *v);
int			sep_case_double(char *cmd, int i, t_var *v, t_env **env);
int			sep_case(char *cmd, int i, t_var *v, t_env **env);
int			else_case_to(char *cmd, int i, t_var *v, t_env **env);
int			else_case(char *cmd, int i, t_var *v, t_env **env);
// check_syntax.c
char		*get_special(char c);
int			is_special(char c);
int			check_sep_valid(char *str, char *next);
int			check_syntax(t_list **arg);
int			check_if_expandable(char *str);
// export.c
void		expo_exist_norm(char *str, t_env **env, int i);
int			export_unset(t_list **args, t_env **envs, int outfile);
int			export_valid(char *arg, t_env **envs);
int			export_unset_to(t_list *arg, t_env **envs, int i);
int			expo_exist(char *arg, int i, t_env **envs);
// export2.c
void		print_env(t_env *arg, int outfile);
void		print_env_xp(t_env *arg, int outfile);
int			is_valide(char *arg);
int			ft_export(char *arg, t_env **envs);
int			check_sep(t_list *arg);
// unset.c
void		exit_func(int exit, t_env **envs);
char		*get_env_str(char *cmd, t_env **env);
int			is_valid_uns(char *arg);
int			check_path(t_env **envs, int outfile);
int			unset(char *args, t_env **envs);
// reset_env.c
void		reset_env(t_env **envs);
void		rm_node(t_env **envs);
//execution
int			heredoc_(int ac, char **av, char *envp[], char *delimiter);
char		*checking_path(char *comm, t_env **envs, int *flag, int i);
void		while_pipe(int **pips);
char		*ft_newstrchr(char *s, char *target);
int			sep_len(t_list **arg);
void		exec_function(char *envp[], char **command, char *x, t_env **envs);
pid_t		bonus_child_fork_1(t_list **arg, t_execution \
			**exec_vars, t_env **envs);
int			**handling_multiple_pipes(t_list **arg);
void		checking_if_pipe_exists(t_execution *exec_vars, \
			t_list **argv, int x, t_env **envs);
void		echo_function(char **splited_command, t_list *arg, \
			int flag, t_env **envs);
t_list		*t_list_char_converter(char **splited_command);
int			checking_builting_functions(char **splited_command, t_env **envs, \
				t_list **arg, t_execution **exec_vars);
void		pwd(int outfile, char **generated_old_pwd);
void		cd_function(char **splited_command, t_env **envs, \
				t_execution **exec_vars);
void		free_t_lst(t_list **list);
void		ft_free(char **str);
void		ending(t_list **argv, t_execution **exec_vars, t_env **envs);
void		ending_2(t_list **argv, t_execution **exec_vars, t_env **envs);
void		if_redirection_in(t_list **arg, t_execution \
			**exec_vars, t_env **envs);
void		if_rediretion_out(t_list **arg, t_execution **exec_vars);
void		if_last(t_list **arg, t_list **argv, \
			t_execution **exec_vars, t_env **envs);
void		declaration(t_list **argv, t_execution **exec_vars);
void		if_redirection_in_or_out(t_list **arg, \
			t_execution **exec_vars, t_env **envs);
void		if_exec_vars(t_execution **exec_vars);
void		init(t_execution **exec_vars, t_list **argv);
void		outfile_infile_reset(t_execution **exec_vars);
void		child_fork_if(t_execution **exec_vars, \
			t_env **env, t_list **arg, int i);
char		**child_fork_init(t_execution **exec_vars, t_env **envs);
void		exec_function_part_1(char **envp, char **command, \
			char *x, t_env **envs);
pid_t		while_finish(t_execution **exec_vars, int *j, \
			char **splited_command, pid_t fn);
void		if_first_time(t_execution **exec_vars, int j);
void		if_not_first_time(t_execution **exec_vars, int j);
int			splited_builting_functions(char **splited_command, t_env **envs, \
			t_list **arg, t_execution **exec_vars);
int			splited_builting_functions2(char **splited_command, \
			t_env **envs, t_list **arg, t_execution **exec_vars);
void		if_temp_arg2(t_list **temp_arg, int outfile, \
			t_env **envs, int new_line_flag);
void		while_temp_arg(t_list **temp_arg, int outfile, \
			t_env **envs, int *new_line_flag);
void		ft_atoi_error(char *str);
int			if_status_2(void);
void		heredoc_loop(t_execution **exec_vars, \
			t_list *delimiter, t_env **envs);
char		*while_loop_checking_path(char *located_path, t_env *head);
void		if_exit_exit(t_env **envs, char **splited_command);
void		exit_print(int status);
int			if_splitedcommand2(char **splited_command, t_env **envs);
int			checking_values(char *str);
void		exec_function_print_error(char *x, t_env **envs);
void		shlvl_increment(t_env **envs);
int			heredoc_func(char *envp[], t_list *delimiter, \
		t_execution **exec_vars, t_env **envs);
int			redirection_in_fork(char **envp, t_list *arg);
int			append(char **envp, t_list *arg);
int			redirection_out_fork(char **envp, t_list *arg);
pid_t		*creating_array_of_fds(t_list **argv);
pid_t		while_loop_fork(t_list **argv, t_execution **exec_vars, \
		int *x, t_env **envs);
////////////////////////////////////////////////////
long long	exit_function_util1(long long status);
long long	ft_atoi_long_long(char *str);
long long	exit_function(t_env **envs, char **splited_command);
#endif