void	ft_putnbr(int n)
{
	long	x;
	int		c;
	int		i;

	i = 0;
	c = 0;
	x = n;
	if (x < 0)
	{
		x = -x;
		write (1, "-", 1);
	}
	if (x >= 0 && x <= 9)
	{
		c = x + 48;
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(x / 10);
		ft_putnbr(x % 10);
	}
}

void	bonu(int *g_global_var, int *shift_index, int *bonus)
{
	if (*shift_index == 32)
	{
		kill(*g_global_var, SIGUSR2);
		*g_global_var = 0;
		*shift_index = 0;
		*bonus = 0;
	}
}	

void	signals_handler(int sig)
{
	static int	bonus;
	static int	shift_index;
	static int	g_global_var;

	if (sig == SIGUSR1)
		g_global_var = g_global_var | (1 << shift_index);
	shift_index += 1;
	if (shift_index == 8)
	{
		if (g_global_var == 0 && bonus == 0)
		{
			bonus = 1;
			shift_index = 0;
		}
		else if (bonus == 0)
		{
			write(1, &g_global_var, 1);
			g_global_var = 0;
			shift_index = 0;
		}
	}
	bonu(&g_global_var, &shift_index, &bonus);
}

int	main(void)
{
	int	server_pid;

	server_pid = getpid();
	ft_putnbr(server_pid);
	write(1, "\n", 1);
	while (1)
	{
		signal(SIGUSR1, &signals_handler);
		signal(SIGUSR2, &signals_handler);
	}
}

