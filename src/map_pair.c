#include <stdlib.h>

#include <map_pair.h>

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
map_pair *map_pair_new(const char *key, void *value)
{
	map_pair *const pair = malloc(sizeof(*pair));

	if (pair != NULL)
		*pair = (map_pair){NULL, key, value};

	return pair;
}

/**
 * @brief Clear a map's key-value pair list.
 *
 * @param pair	The map's bucket to be cleared,
 * @param del	The value's destructor.
 */
void map_pair_clr(map_pair **pair, void(*del(void *)))
{
	map_pair *curr;

	while (*pair != NULL)
	{
		curr = *pair;
		*pair = curr->next;
		if (del != NULL)
			del(curr->value);
		free(curr);
	}
}
