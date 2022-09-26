#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

static bool validate(queue_t *q)
{
    printf("elements: ");
    for (element_t *e = q->head; e->next; e = e->next) {
        if (strcmp(e->value, e->next->value) > 0)
            return false;
    }

    return true;
}

void q_show(queue_t *q)
{
    int i = 0;
    printf("index   :");
    for (element_t *e = q->head; e; e = e->next, i++) printf("%6d ", i);
    puts("");
    printf("elements:");
    for (element_t *e = q->head; e; e = e->next) printf("%6s ", e->value);
    puts("");
}

int main(void) {
    queue_t* q = q_new();
    char input[100];
    while (1) {
        printf("(1) insert head (2) insert tail (3) remove head (4) queue reverse (5) sort (6)free queue (7) exit \n");
        int opt;
        scanf("%d", &opt); puts("");
        if (opt == 1) {
            printf("enter a string");
            puts("");
            scanf("%s", input); puts("");
            q_insert_head(q, input);
        }
        else if (opt == 2) {
            printf("enter a string");
            puts("");
            scanf("%s", input); puts("");
            q_insert_tail(q, input);
        }
        else if (opt == 3) {
            char buf[100];
            q_remove_head(q, buf, 50);
        }
        else if (opt == 4) {
            q_reverse(q);
        }
        else if (opt == 5) {
            q_sort(q);
        }
        else if (opt == 6) {
            q_free(q);
        }
        else if (opt == 7) {
            q_free(q);
            if (q) free(q);
            return 0;
        }
        q_show(q);
    }
}
