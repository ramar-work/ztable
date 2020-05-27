# zhasher

zhasher is a library for handling hash tables in C.  It is intended as a drop-in two-file library that takes little work to setup and teardown, and even less work to integrate into a project of your own.


## Installation

To keep things simple, there will probably never be an official package for this.  zhasher will build on any Unix based platform with whatever compiler you choose.

zhasher can be built with: 
	`gcc -Wall -Werror -std=c99 zhasher.c main.c`


## Usage

An example of working with strings mapped to integers is below.

<pre>
void save_integers_to_table() {
	//Define some data
	const char *data[] = { "one", "two", "three", "four", "five" };
	const char **d = data;
 
	//The zTable structure can be allocated either dynamically or statically
	zTable *t = malloc( sizeof( zTable ) );

	//However, the structure's initialization will usually be dynamic.
	lt_init( t, NULL, 1024 );

	//To add keys we can loop through a list, generating integers along the way.
	while ( *d ) {
		// w will start at zero, and we'll add 13 at each new iteration
		static int w;
	
		//Add a text key (must be a zero-terminated string)
		lt_addtextkey( t, *d );

		//Add a numeric value.  
		//NOTE: Strings, BLOBs and void * are also supported via other functions.
		lt_addintvalue( t, w );
		
		//Terminate the "row" with lt_finalize
		lt_finalize( t );

		//Increment our numeric count and move to the next string in **d	
		w += 13;
		y++;
	}

	//Finally, to get hashing to work, use lt_lock( ... )
	lt_lock( t );
}
</pre>


To retrieve values from our table, we can use either `lt_geti` or `lt_$TYPE` where $TYPE can be `text`, `int`, `float`, `blob` or `userdata`.  `lt_geti` acts as a check function, which simply checks the table for a particular key and returns a positive integer if present.   

The `lt_$TYPE` family are convenience functions and will attempt to return the most appropriate value possible for non-existent values. In other words, if a key supplied to `lt_text(...)` does not exist, `lt_text(...)` will return NULL.  Most of the time a zero or NULL value is the right thing, but a caveat to this is discovered when taking a closer look at `lt_int` and `lt_float`.  Both functions return 0 in the case of keys that aren't found.   For this reason, it's best to check the existence of the key first with `lt_geti`.

Using our example from above, let's look for the values 'one' and 'hot'.

<pre>
int val1 = lt_int( t, "one" );
int val2 = lt_int( t, "hot" );
fprintf( stderr, "val1: %d\n", val1 );
fprintf( stderr, "val2: %d\n", val2 );
</pre>

Outputs
<pre>
val1: 26 
val2: 0 
</pre>

Note that unless when using NULL as the middle argument to lt_init, there will always be data to free.  So using lt_free will destroy the table data.
<pre>
lt_free( t );
</pre>

Likewise, if the zTable structure was dynamically allocated, don't forget to free it.
<pre>
free( t );
</pre>

Tables can be statically initialized as well by manually specifying the modulo value and an array of the datatype zKeyval.  In other words, instead of:
<pre>
lt_init( t, NULL, 1024 );
</pre>

do:
<pre>
zKeyval kv[1024] = { 0 };
lt_init( t, kv, sizeof( kv ) );
</pre>

As stated earlier, strings and integers are not the only values that zhasher will support. zhasher can map strings to integers, other strings, blobs and void pointers, allowing whatever you want to fit into a slot.   Better support (read <i>typesafe</i>) for more abstract datatypes will probably end up here in the future. 



## Reference

