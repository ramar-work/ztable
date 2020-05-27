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

Note that unless when using NULL as the middle argument to `lt_init`, there will always be data to free.  So using `lt_free` will destroy the table data.
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

As stated earlier, strings and integers are not the only values that zhasher supports. zhasher can map strings to integers, other strings, blobs and void pointers, allowing whatever you want to fit into a slot.   Better support (read <i>typesafe</i>) for more abstract datatypes will probably end up here in the future. 



## Reference


### Simple

To get busy using zhasher as a hash table, only the following functions are really needed.

#### Initialization & Teardown

`zTable * lt_init ( zTable * , zKeyval * , int )`
- Initialize the zTable either dynamically or statically.

`void lt_lock ( zTable * )`
- Initialize hashes for each key.  Use this after all of the values you want in the table have been added.

`void lt_free( zTable * )`
- Destroy a zTable 

 
#### Adding Values

`zhType lt_addintkey(t, v)`
- Add an integer key.  Return value can be discarded.

`zhType lt_addintvalue(t, v)`
- Add an integer value.  Return value can be discarded.

`zhType lt_addtextkey(t, v)`
- Add an zero-terminated string key.  Strings added in this manner are duplicated by zhasher.

`zhType lt_addtextvalue(t, v)`
- Add an zero-terminated string value.  Strings added in this manner are duplicated by zhasher. 

`zhType lt_addblobvalue(t, vblob, vlen)`
- Add a BLOB value where vblob is an unsigned char * and vlen is its length.  Return value can be discarded.

`zhType lt_addfloatvalue(t, v)`
- Add an float value.  Return value can be discarded.

`zhType lt_addudvalue(t, v)`
- Add an opaque value.  Return value can be discarded.

`void lt_finalize ( zTable * ) `
- Finalize a key-value set in a zTable.  Use this after adding at least one key and one value.

`void lt_descend( t )`
- Create a "table" within a zTable 

`void lt_ascend( t )`
- Ascend from a "table" within a zTable (lt_finalize is not needed after calling this)



#### Retrieving Values

`int lt_geti ( zTable * , char * )`
- Check that a string key is present in a zTable.

`int lt_get_long_i ( zTable * , unsigned char * , int)`
- Check that an unsigned char * block matches a key in a zTable.

`int lt_int( zTable *, const char * )`
- Retrieve an integer value from a zTable.  Returns 0 if value does not exist.

`float lt_float( zTable *, const char * )`
- Retrieve an float value from a zTable.  Returns 0 if value does not exist.

`char * lt_text( zTable *, const char * )`
- Retrieve a signed character value from a zTable.  Returns NULL if value does not exist.

`zhBlob * lt_blob( zTable *, const char * )`
- Retrieve a zhBlob value from a zTable.  Returns NULL if value does not exist.

`void *lt_userdata( zTable *, const char * )`
- Retrieve an opaque pointer value from a zTable.  Returns NULL if value does not exist.



### Helpers

This functions exist to make dealing with text-based and binary data a little bit easier.

`unsigned char * lt_trim ( uint8_t * , char * , int, int * )`
- Trims whitespace found in a returned unsigned char * value.


### Advanced

These functions will help write iterators.

`int lt_exec_complex( zTable * , int, int, void * , int ( * fp)(zKeyval * , int, void * ) )` -
Base iterator function for acting on the elements in a zTable.

`int lt_counti(t, i)` -
Get a count of the elements at index <i>i</i>.

`int lt_counta(t, i)` - 
Get an actual count of the elements at index <i>i</i>.

<!-- `zKeyval * lt_next( zTable * )` - -->
<!-- Return the zKeyval  -->

<!-- `zKeyval * lt_current( zTable * )` - -->
<!-- Return the zKeyval  -->

<!-- `void lt_reset( zTable * )` -  -->
<!-- Reset the pointer -->

<!-- `int lt_exists ( zTable * , int)` - -->
<!-- const char * lt_strerror( zTable * ); -->
<!-- void lt_clearerror( zTable * ); -->
<!-- int lt_count_at_index ( zTable * , int, int); -->
<!-- int lt_countall ( zTable * ); -->
<!-- int lt_count_elements ( zTable * , int); -->
<!-- zKeyval *lt_retkv (zTable *, int); -->
<!-- zhType lt_rettype (zTable *, int, int); -->
<!-- const char *lt_rettypename (zTable *, int, int); -->
<!-- unsigned char *lt_get_full_key (zTable *, int, unsigned char *, int); -->
<!-- int lt_set (zTable *, int); -->
<!-- int lt_absset (zTable *, int); -->
<!-- int lt_get_raw (zTable *, int); -->
<!-- zhValue *lt_retany (zTable *, int ); -->
<!-- zhRecord *lt_ret (zTable *, zhType, int ); -->
<!-- void lt_setsrc (zTable *, void *); -->
<!-- zKeyval *lt_items_i (zTable *, uint8_t *, int); -->
<!-- zKeyval *lt_items_by_index (zTable *, int); -->
<!-- const char *lt_typename (int); -->


## Notes

zhasher was extracted from a much larger library of mine called <a href="https://github.com/zaiah-dj/single">single.c</a>.  Much of that library has no use now, but this is one of the pieces that has found its way into my recent projects. 
