#include <stdio.h>
#include "parser.h"

static const char *tok_name(t_toktype t)
{
    switch (t)
    {
        case TK_WORD:    return "WORD";
        case TK_PIPE:    return "PIPE";
        case TK_INFILE:  return "INFILE";
        case TK_OUTFILE: return "OUTFILE";
        case TK_APPEND:  return "APPEND";
        case TK_HEREDOC: return "HEREDOC";
        default:         return "UNKNOWN";
    }
}

void	print_tokens(const t_token_list *lst)
{
    const t_token	*cur;
    int				i;

    printf("Tokens (%zd):\n", lst ? lst->size : 0); // ssize_t => %zd
    if (!lst)
        return;
    cur = lst->head;
    i = 0;
    while (cur)
    {
        printf("  [%02d] %-7s value: %s\n",
            i++, tok_name(cur->type), cur->value ? cur->value : "(null)");
        cur = cur->next;
    }
}