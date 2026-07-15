#include <stdlib.h>    /* malloc       */
#include <stddef.h>    /* offsetof     */
#include <stdio.h>     /* printf       */
#include <string.h>    /* memset       */
#include "uthash.h"

typedef struct inner {
    int a;
    int b;
    char event_code;
} __attribute__((packed)) hash_key_t;
// needs to be packed to avoid the padding

struct my_event {
    hash_key_t hash_key;           /* key is aggregate of this field */
    int user_id;
    UT_hash_handle hh;         /* makes this structure hashable */
};


int main()
{
    struct my_event *e, ev, *events = NULL;
    unsigned keylen;
    int i;


    keylen = sizeof(hash_key_t);

    for(i = 0; i < 10; i++) {
        e = (struct my_event*)malloc(sizeof(struct my_event));
        if (e == NULL) {
            exit(-1);
        }
        memset(e,0,sizeof(struct my_event));
        e->hash_key.a = i * (60*60*24*365);          /* i years (sec)*/
        e->hash_key.b = 0;
        e->hash_key.event_code = 'a'+(i%2);              /* meaningless */
        e->user_id = i;

        HASH_ADD( hh, events, hash_key, keylen, e);
    }

    /* look for one specific event */
    memset(&ev,0,sizeof(struct my_event));
    ev.hash_key.a = 5 * (60*60*24*365);
    ev.hash_key.b = 0;
    ev.hash_key.event_code = 'b';
    HASH_FIND( hh, events, &ev.hash_key, keylen , e);
    if (e != NULL) {
        printf("found: user %d, unix time %d\n", e->user_id, e->hash_key.a);
    }
    return 0;
}
