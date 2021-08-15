#include <stdlib.h>
#include <string.h>
#include <hash_map.h>

/**
 * @brief Add a key-value pair to a map_pair list.
 *
 * @param map	The bucket at the key's index.
 * @param elem 	A key-value pair matching to the key's index,
 */
void map_pair_add(map_pair **bucket, map_pair *elem)
{
	elem->next = *bucket;
	*bucket = elem;
}

/**
 * @brief Allocate a new key-value pair.
 *
 * @param key	Index key.
 * @param value	Mapped value.
 * @return map_pair*
 */
map_pair *map_pair_new(const char *key, const char *value)
{
	map_pair *const pair = malloc(sizeof(*pair));

	if (pair != NULL)
		*pair = (map_pair){key, value, NULL};

	return pair;
}

/**
 * @brief Clear a map's key-value pair list.
 *
 * @param pair	The map's bucket to be cleared,
 */
void map_pair_clr(map_pair **pair)
{
	map_pair *curr;

	while (*pair != NULL)
	{
		curr = *pair;
		*pair = curr->next;
		free(curr);
	}
}

/**
 * @brief Allocate a hash_map for a given size.
 *
 * @param size	The maximal amount of elements.
 * @return hash_map*
 */
hash_map *hash_map_new(size_t size)
{
	hash_map *const map = malloc(sizeof(*map) + sizeof(*map->buckets) * size);

	if (map != NULL)
	{
		map->size = size;
		map->buckets = (map_pair **)(map + 1);

		bzero(map->buckets, sizeof(*map->buckets) * size);
	}

	return map;
}

/**
 * @brief Hash an input into a number in the range [0 - map_size].
 *
 * @param input		The c-string to be hashed.
 * @param map_size	The containing map's size.
 * @return size_t	The hashed value.
 */
size_t hash_function(const char *input, size_t map_size)
{
	size_t acc = 0;

	while (*input != '\0')
		acc += *input++;

	return acc % map_size;
}

/**
 * @brief Get a value from a key in a hash map.
 *
 * Returns NULL if inexistent.
 * @param map	The hash-map in which to find the value.
 * @param key	The key associated to the value.
 * @return map_pair*
 */
const char *hash_map_get(const hash_map *const map, const char *key)
{
	const size_t index = hash_function(key, map->size);
	map_pair *pair = map->buckets[index];

	if (pair != NULL && pair->next != NULL)
		while (pair != NULL && strcmp(pair->key, key) != 0)
			pair = pair->next;
	return pair != NULL ? pair->value : NULL;
}

/**
 * @brief Set a value for a key in a hash map.
 *
 * @param map	The hash-map in which to set the value.
 * @param key	The key used to retrieve the value.
 * @param value	The value to be set.
 * @return const map_pair*
 */
const map_pair *hash_map_set(hash_map *map, const char *key, const char *value)
{
	const size_t index = hash_function(key, map->size);
	map_pair **bucket = map->buckets + index;
	map_pair *pair = *bucket;

	while (pair != NULL && strcmp(pair->key, key) != 0)
		pair = pair->next;
	if (pair == NULL)
	{
		pair = map_pair_new(key, value);

		if (pair != NULL)
		{
			pair->next = *bucket;
			*bucket = pair;
		}
	}
	else
		pair->value = value;
	return pair;
}

/**
 * @brief Free the map's memory and set it's pointer to NULL.
 *
 * @param map	A reference to the map to be cleared.
 */
void hash_map_clr(hash_map **map)
{
	if (*map)
	{
		for (size_t i = 0; i < (*map)->size; i++)
			map_pair_clr((*map)->buckets + i);
		free(*map);
		*map = NULL;
	}
}
