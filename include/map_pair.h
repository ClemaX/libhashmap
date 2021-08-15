#pragma once

typedef struct s_map_pair
{
	const char *key;
	void *value;
	struct s_map_pair *next;
} map_pair;

/**
 * @brief Add a key-value pair to a hash_map list.
 *
 * @param map	The hash-map list at the key's index.
 * @param elem 	A hash-map element matching to the key's index,
 */
void map_pair_add(map_pair **bucket, map_pair *elem);

/**
 * @brief Allocate a new key-value pair.
 *
 * @param key	Index key.
 * @param value	Mapped value.
 * @return hash_map*
 */
map_pair *map_pair_new(const char *key, void *value);

/**
 * @brief Clear a map's key-value pair list.
 *
 * @param pair	The map's bucket to be cleared,
 */
void map_pair_clr(map_pair **pair);
