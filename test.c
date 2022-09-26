#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

static bool validate(queue_t *q)
{
    for (element_t *e = q->head; e->next; e = e->next) {
        if (strcmp(e->value, e->next->value) > 0)
            return false;
    }
    
    q_reverse(q);
    
    for (element_t *e = q->head; e->next; e = e->next) {
        if (strcmp(e->value, e->next->value) < 0)
            return false;
    }

    return true;
}

/**
static void q_show(queue_t *q)
{
    for (element_t *e = q->head; e->next; e = e->next)
        printf("%s", e->value);
}
*/

int main(void)
{
    FILE *fp = fopen("cities.txt", "r");
    if (!fp) {
        perror("failed to open cities.txt");
        exit(EXIT_FAILURE);
    }

    queue_t *q = q_new();
    char buf[256];
    while (fgets(buf, 256, fp))
        q_insert_head(q, buf);
    fclose(fp);

    q_sort(q);
    assert(validate(q));
    
    q_free(q);

    return 0;
}
