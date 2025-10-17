/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_parser.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:59:49 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/17 16:02:12 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

char *gc_substr(const char *s, unsigned int start, size_t len)
{
    char *sub;
    size_t slen;

    if (!s)
        return (NULL);
    slen = ft_strlen(s);
    if (start >= slen)
        return (gc_strdup(""));
    if (len > slen - start)
        len = slen - start;
    sub = gc_malloc(len + 1);
    if (!sub)
        return (NULL);
    ft_memcpy(sub, s + start, len);
    sub[len] = '\0';
    return (sub);
}
