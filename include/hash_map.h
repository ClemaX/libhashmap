#pragma once

#include <stddef.h>

#include <map_pair.h>

typedef struct s_hash_map
{
	map_pair **buckets;
	size_t size;
	// array space
} hash_map;

/**
 * @brief Allocate a hash_map for a given size.
 *
 * @param size	The maximal amount of elements.
 * @return hash_map*
 */
hash_map *hash_map_new(size_t size);

/**
 * @brief Hash an input into a number in the range [0 - map_size].
 *
 * @param input		The c-string to be hashed.
 * @param map_size	The containing map's size.
 * @return size_t	The hashed value.
 */
size_t hash_function(const char *input, size_t map_size);

/**
 * @brief Get a value from a key in a hash map.
 *
 * Returns NULL if inexistent
 * @param map	The hash-map in which to find the value.
 * @param key	The key associated to the value.
 * @return map_pair*
 */
const char *hash_map_get(const hash_map *const map, const char *key);

/**
 * @brief Set a value for a key in a hash map.
 *
 * @param map	The hash-map in which to set the value.
 * @param key	The key used to retrieve the value.
 * @param value	The value to be set.
 * @return const map_pair*
 */
const map_pair *hash_map_set(hash_map *map, const char *key, const char *value);

/**
 * @brief Free the map's memory and set it's pointer to NULL.
 *
 * @param map	A reference to the map to be cleared.
 */
void hash_map_clr(hash_map **map);
