/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:17:32 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/15 18:31:28 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>//									Long Long
# include <stdbool.h>//									Bool
# include <stdio.h>// 									Printf
# include <unistd.h>//									GetCWD
# include <signal.h>//									Signals
# include <sys/stat.h>//								File Stat
# include <fcntl.h>//									Open / Read
# include <stdlib.h>// 									Malloc & Free
# include <errno.h>//									Setting perror messages

# include "./readline/readline.h"// 					Readline
# include "./readline/history.h"//						History

int	g_last_result;

typedef struct s_input// Final Output
{
	char			**commands;
	int				_stdin;
	int				_stdout;
	char			*_stdinname;
	char			*_stdoutname;
	struct s_input	*previous;
	struct s_input	*next;
}	t_input;

typedef struct s_heredoc_state
{
	int		stdin_clone;
	bool	fd_broken;
	bool	c;
	bool	r;
}	t_hd_state;

typedef struct s_fd_chain {
	int					pid;
	int					fd[2];
	struct s_fd_chain	*next;
	struct s_fd_chain	*previous;
}	t_fd_chain;

enum e_std_save
{
	SAVE_IN = 1 << 0,
	SAVE_OUT = 1 << 1,
	CLOSE_IN = 1 << 2,
	CLOSE_OUT = 1 << 3,
	RESTORE_IN = 1 << 4,
	RESTORE_OUT = 1 << 5
};

enum e_file_type
{
	EXE,
	DIR,
	NORMAL_FILE
};

# define HEREDOC_KILLED -666
# define COMMAND_NOT_FOUND_EXIT 127
# define IS_DIR_EXIT 126
# define PERMISSION_DENIED_EXIT 126
# define UNEXPECTED_TOKEN_ERROR 258

// Parsing
void		free_input(t_input *head);
t_input		*parse_input(char *input, t_input *linkedlist);
char		*remove_quotes(char	*str);
bool		argschecker(t_input *LL);
bool		check_fd(t_input *input);
bool		check_input(char *input);
void		clean_mess(t_input *LL);
char		*convert_all_args(char *command);
void		change_input(char *file, t_input *node);
void		compute_node(char *command, t_input *node, int *index);

// Heredoc
void		restoreline(void);
t_hd_state	*hstate(void);
char		*get_uniquefilename(void);
void		delete_heredocs_files(void);
int			*get_heredoc_filecount(void);
char		*get_heredoc_fileprefix(void);
void		heredoc_cleanup(t_input	*node);
char		*convert_all_args_hd(char *command);
void		heredoc(char *keyword, t_input *node);

// Env
void		show_env(void);
void		show_env_export(void);
char		***get_env(void);
void		free_env(void);
void		init_env(char **env);
void		find_and_remove(char *str);
void		add_to_env(char *str);
void		rem_from_env(char *argname);
char		*find_and_return(char *str);

// Tools
bool		is_valid_longlong(const char *str);
char		*ft_itoa(int n);
bool		ft_isdigit(int c);
bool		ft_isalpha(int c);
bool		ft_isspace(char c);
bool		ft_isredir(char *str);
uint8_t		ft_isquote(char	*str);
char		*ft_strdup(char *src);
char		*ft_isvariable(char *str);
size_t		ft_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
int			ft_getvariablelen(char *str);
int			ft_strcmp(const char *s1, const char *s2);
bool		ft_iscorrectenvname(char *str);
char		*ft_strcpy(char *dest, char *src);
char		*ft_charncat(char *dest, char c, size_t n);
char		*ft_strncat(char *dest, char *src, int nb);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		free_double_array(void	**ptr);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *nptr);
int			is_str_int(const char *str);
bool		is_valid_longlong(const char *str);
int			get_array_size(char	**array);
void		ft_putstr_fd(char *s, int fd);
long long	ft_longlongatoi(const char *nptr);
bool		check_fd(t_input *input);
bool		ft_isredir_or_pipe(char *str);
void		*ft_memcpy(void *dst, const void *src, size_t n);

// Strtoks - SUPER cursed stuff
char		*ft_strtok(char *str);
void		strtok_two(char **stock);
char		*ft_strtok_monkas(char *str);
int			count_strtok_monkas(char *str);
bool		stok3(char **stock, char *last_char);
void		strtok_one(uint8_t *swtch, char **output, char *stock);
void		ft_strtokhelper2(uint8_t *swtch, uint8_t *quote, char **stock);
void		ft_strtokhelper3(char **output, uint8_t *quote, uint8_t *swtch);

// 2D Array
int			ft_count2darray(char **s);
void		ft_sort2darray(char ***strings);
void		ft_copy2darray(char ***dist, char **src);
bool		ft_isin2darray(char **src, char *tofind);
void		ft_remove2darray(char ***dist, char **src, char *str);
void		ft_insert2darray(char ***dist, char **src, char *newstr);

// Signals
void		sigint_interactive(int sig);
void		sigint_running_shell(int sig);
void		sigint_running_heredoc(int sig);
void		heredoc_child_sighandler(int sig);
void		interactive_sighandlers(void);

// execution
void		ms_export(char **args);
int			intercept_signals(void);
void		ms_pipes(t_input *input, t_fd_chain *fd_chain);
t_fd_chain	*open_new_pipe(t_fd_chain *fd_chain);
t_fd_chain	*close_fd_chain(t_fd_chain *fd_chain);
void		save_std(int option);
void		close_unused_fd(t_fd_chain *fd_chain);
t_fd_chain	*open_new_pipe(t_fd_chain *fd_chain);
t_fd_chain	*free_fd_chain(t_fd_chain *fd_chain);
void		pipeline_error_cleaning(t_input *input, t_fd_chain *fd_chain, \
	char	*msg, bool	exiting_process);
void		close_other_redirection_pipe_fd(t_input *input);
void		close_redirection(t_input *input);
void		ms_unset(char **args);
void		ms_pwd(char **args);
void		ms_cd(char **args);
void		ms_exe(t_input *input);
void		ms_exit(t_input *input);
void		ms_echo(char **args);
void		command_handler(t_input *input);
void		single_command_handler(t_input *input);
void		ms_env(char **args);
void		perror_global(char *str);
void		clean_static_memory(void);
void		*ft_calloc(size_t nitems, size_t size);
void		convert_exit(void);
int			get_file_type(char *path);
void		error_message_exe(char *str);
void		dup_last_fd(t_fd_chain *fd_chain);
void		default_sig(void);

#endif
