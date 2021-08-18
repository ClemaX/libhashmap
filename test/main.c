#include <stdio.h>

#include <hash_map.h>

// Demonstration of a modulo hash map with strings

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	hash_map *map = hash_map_new(512);

	hash_map_set(map, "iep", "value");
	hash_map_set(map, "pie", "drip");
	printf("%s -> %s\n", "iep", (char *)hash_map_get(map, "iep")->value);
	printf("%s -> %s\n", "pie", (char *)hash_map_get(map, "pie")->value);
	hash_map_set(map, "pie", "pie");
	printf("%s -> %s\n", "pie", (char *)hash_map_get(map, "pie")->value);

	hash_map_clr(&map, NULL);

	return (0);
}
