#include "../../includes/minishell.h"

void	cmd_pwd(void)
{
	char	*path;
	
 	path = join_freev2("", getenv("PWD"));
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(path);
}

