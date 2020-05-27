#include "zhasher.h"

const char *list[] = {
	"abc",
	NULL
};

struct yakvs { const char *key; char *val; } yakvs_list[] = {
	{ "nobody", "knows" },
	{ "the", "trouble I've seen." },
	{ "Anthony", "Hopkins" },
	{ "Mike", "Tyson" }
};

int main (int argc, char *argv[]) {
	//The zTable structure can be allocated either dynamically or statically
	zTable *t = malloc( sizeof( zTable ) );

	//However, the structure's initialization will usually be dynamic.
	lt_init( t, NULL, 1024 );

	//To statically initialize the structure, we'll use an array of zKeyvals
	//zKeyval kv[1024] = { 0 };

	//To add values we can loop through a list.
	struct yakvs *y = yakvs_list;
	while ( y->key ) {
		lt_addtextkey( t, y->key );
		lt_addtextvalue( t, y->val );
		y++;
	}	
	return 0;
}
