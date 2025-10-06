




static t_toktype	quote_type(const char *str, int i)
{
	if (str[i] == '\'')
		return (S_QUOTES);
	return (D_QUOTES);
}