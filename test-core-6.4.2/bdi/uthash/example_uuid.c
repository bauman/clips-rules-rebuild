#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
#include "uthash.h"
#include "../uuid/uuid4.h"

typedef struct my_struct {
    char uuid[36];             /* key */
    char name[10];
    int id;
    UT_hash_handle hh;         /* makes this structure hashable */
} uuid_hash_t;


int main()
{
    uuid4_init();
    const char **n, *names[] = { "joe", "bob", "betty", NULL };
    struct my_struct *s = NULL, *tmp = NULL, *users = NULL;
    int i=0;

    for (n = names; *n != NULL; n++) {
        s = (uuid_hash_t*)malloc(sizeof(uuid_hash_t));
        if (s == NULL) {
            exit(-1);
        }
        uuid4_generate(s->uuid);
        strcpy(s->name, *n);
        if(!tmp){
            tmp = s;
        }
        s->id = i++;
        HASH_ADD_STR( users, uuid, s );
    }

    HASH_FIND_STR( users, tmp->uuid, s);
    if (s != NULL) {
        printf("%s's id is %d\n", s->name, s->id);
    }

    /* free the hash table contents */
    HASH_ITER(hh, users, s, tmp) {
        printf("%s's id is %d\n", s->name, s->id);
        HASH_DEL(users, s);
        free(s);
    }
    return 0;
}
