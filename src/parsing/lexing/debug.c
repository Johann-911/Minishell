#include "debug.h"

static const char *tok_name(t_toktype t)
{
    switch (t) {
        case TK_WORD:    return "WORD";
        case TK_PIPE:    return "PIPE";
        case TK_INFILE:  return "INFILE";
        case TK_OUTFILE: return "OUTFILE";
        case TK_APPEND:  return "APPEND";
        case TK_HEREDOC: return "HEREDOC";
        default:         return "UNKNOWN";
    }
}

void print_tokens(const t_token_list *lst)
{
    const t_token *cur = lst ? lst->head : NULL;
    int i = 0;

    printf("%sTokens (%zd):%s\n", COLOR_YELLOW, lst ? lst->size : 0, COLOR_RESET);
    while (cur) {
        printf("  [%02d] %-7s value: %s%s%s\n",
               i++, tok_name(cur->type),
               COLOR_GREEN, cur->value ? cur->value : "(null)", COLOR_RESET);
        cur = cur->next;
    }
}