




#include "garbage_collector.h"


char	*ft_substr(const char *s, unsigned int start, size_t length)
{
	t_gc	*gc;
	char	*str;
	size_t	string_length;
	size_t	substring_length;	gc = get_gc();
	if (s == NULL)
		return (NULL);
	string_length = ft_strlen(s);
	if (start >= string_length)
		return (ft_strdup(""));
	substring_length = string_length - start;
	if (length > substring_length)
		length = substring_length;
	str = gc_malloc(length + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, length + 1);
	return (str);
}
