#include "zhasher.h"

const char *list[] = {
	"George Washington",
	"John Adams",
	"Thomas Jefferson",
	"James Madison",
	"James Monroe",
	"John Quincy Adams",
	"Andrew Jackson",
	"Martin Van Buren",
	"William Henry Harrison",
	"John Tyler",
	"James K. Polk",
	"Zachary Taylor",
	"Millard Fillmore",
	"Franklin Pierce",
	"James Buchanan",
	"Abraham Lincoln",
	"Andrew Johnson",
	"Ulysses S. Grant",
	"Rutherford B. Hayes",
	"James Garfield",
	"Chester A. Arthur",
	"Grover Cleveland",
	"Benjamin Harrison",
	"Grover Cleveland",
	"William McKinley",
	"Theodore Roosevelt",
	"William Howard Taft",
	"Woodrow Wilson",
	"Warren G. Harding",
	"Calvin Coolidge",
	"Herbert Hoover",
	"Franklin D. Roosevelt",
	"Harry S. Truman",
	"Dwight D. Eisenhower",
	"John F. Kennedy",
	"Lyndon B. Johnson",
	"Richard M. Nixon",
	"Gerald R. Ford",
	"James Carter",
	"Ronald Reagan",
	"George H. W. Bush",
	"William J. Clinton",
	"George W. Bush",
	"Barack Obama",
	"Donald J. Trump",
	NULL
};

struct yakvs { const char *key; char *val; } yakvs_list[] = {
	{ "nobody", "knows" },
	{ "the", "trouble I've seen." },
	{ "Anthony", "Hopkins" },
	{ "Mike", "Tyson" },
	{ NULL }
};


int main (int argc, char *argv[]) {
	//The zTable structure can be allocated either dynamically or statically
	zTable *t = malloc( sizeof( zTable ) );

	//However, the structure's initialization will usually be dynamic.
	lt_init( t, NULL, 1024 );

	//To statically initialize the structure, we'll use an array of zKeyvals
	//zKeyval kv[1024] = { 0 };

	//To add values we can loop through a list.
	fprintf( stderr, "SHORT WORDS\n============\n" );
	struct yakvs *y = yakvs_list;
	while ( y->key ) {
		lt_addtextkey( t, y->key );
		lt_addtextvalue( t, y->val );
		lt_finalize( t );
		y++;
	}

	//Finally, to fully initialize the table, use lt_lock( zTable *t )
	lt_lock( t );

	//Get the values
	char *key1 = "the";
	int hash = lt_geti( t, key1 );	
	fprintf( stderr, "hash of '%s': %d\n", key1, hash );
	char *the = lt_text( t, key1 ); 
	fprintf( stderr, "'%s' => %s\n", key1, the );

	//When done, free the table with lt_free and free our allocation
	lt_free( t );
	free( t );

	//Let's try another example, with random values on the other side...
	const char **name = list;	
	int i = 0;
	zTable *tt = malloc( sizeof( zTable ) );
	lt_init( tt, NULL, 1024 );

	fprintf( stderr, "PRESIDENTS\n============\n" );
	while ( *name ) {
		lt_addtextkey( tt, *name );
		lt_addintvalue( tt, i );
		lt_finalize( tt );
		i += 3;
		name++;
	}

	//Get the values
	lt_lock( tt );
	char key2[] = "Thomas Jefferson";
	int xhash = lt_geti( t, key2 );
	fprintf( stderr, "hash of '%s': %d\n", key2, xhash );
	int tj = lt_int( t, key2 );
	fprintf( stderr, "'%s' => %d\n", key2, tj );

	//Again we free the table with lt_free and free our allocation
	lt_free( tt );
	free( tt );
	return 0;
}
