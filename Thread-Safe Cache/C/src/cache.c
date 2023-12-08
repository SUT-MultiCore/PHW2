#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uthash.h>

#include "cache.h"

// Initialize the cache
void cache_init(cache_t *cache) {
    // Your code here.

    cache->data = NULL; // Initialize the hashmap
}

// Destroy the cache
void cache_destroy(cache_t *cache) {
    // Your code here.

    // Iterate through the hashmap and free entries
    cache_entry_t *entry, *tmp;
    HASH_ITER(hh, cache->data, entry, tmp) {
        HASH_DEL(cache->data, entry);
        free(entry);
    }
}

// Retrieve the value or insert a new one created by `f`
const char *cache_get_or_insert_with(cache_t *cache, const char *key, generator_t generator, const void *arg) {
    // Your code here.

    // Check if the key is already in the cache
    cache_entry_t *entry;
    HASH_FIND_STR(cache->data, key, entry);

    if (entry != NULL) {

        // There is already an `entry_t` with this key.

        return NULL;
    }

    // There is no `entry_t` with this key.

    return NULL;
}
