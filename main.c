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


//...
struct inc { int depth; const char *key; float val; } inc_list[] = {
	{ 0, "Basic Industries", 0 },
	{ 1, "Aduro Biotech, Inc.", 5.24 },
	{ 1, "AdvisorShares Vice ETF", 15.8 },
	{ 1, "Aehr Test Systems", 0.8443 },

	{ 0, "Capital Goods", 0 },
	{ 1, "9F Inc.", 54.98 },
	{ 1, "Acasti Pharma, Inc.", 8.76 },
	{ 1, "Advanced Emissions Solutions, Inc.", 66.1 },
	{ 1, "Aeglea BioTherapeutics, Inc.", 1.66 },
	{ 1, "Aerie Pharmaceuticals, Inc.", 70.16 },
	{ 1, "AEterna Zentaris Inc.", 1.27 },

	{ 0, "Consumer Non-Durables", 0 },
	{ 1, "Acorda Therapeutics, Inc.", 10.11 },
	{ 1, "Act II Global Acquisition Corp.", 0.995 },
	{ 1, "Act II Global Acquisition Corp.", 10.62 },

	{ 0, "Consumer Services", 0 },
	{ 1, "180 Degree Capital Corp.", 22.54 },
	{ 1, "Addus HomeCare Corporation", 1.78 },
	{ 1, "Affimed N.V.", 18.05 },
	{ 1, "AGM Group Holdings Inc.", 13.49 },

	{ 0, "Energy", 0 },
	{ 1, "ABIOMED, Inc.", 0.2061 },

	{ 0, "Finance", 0 },
	{ 1, "111, Inc.", 4.5307 },
	{ 1, "1347 Property Insurance Holdings, Inc.", 1.57 },
	{ 1, "1347 Property Insurance Holdings, Inc.", 23.8 },
	{ 1, "1-800-FLOWERS.COM, Inc.", 8.6 },
	{ 1, "1Life Healthcare, Inc.", 13.11 },
	{ 1, "1st Constitution Bancorp (NJ)", 36.56 },
	{ 1, "2U, Inc.", 9.86 },
	{ 1, "89bio, Inc.", 10.03 },
	{ 1, "8i Enterprises Acquisition Corp", 0.29 },
	{ 1, "8i Enterprises Acquisition Corp", 0.3492 },
	{ 1, "8i Enterprises Acquisition Corp", 10.6 },
	{ 1, "9 Meters Biopharma, Inc.", 5.9208 },
	{ 1, "ACADIA Pharmaceuticals Inc.", 9.97 },
	{ 1, "Acamar Partners Acquisition Corp.", 0.4801 },
	{ 1, "Acamar Partners Acquisition Corp.", 10.2 },
	{ 1, "ACM Research, Inc.", 26.26 },
	{ 1, "Afya Limited", 10.1 },
	{ 1, "AGBA Acquisition Limited", 0.08 },
	{ 1, "AGBA Acquisition Limited", 0.2 },
	{ 1, "AGBA Acquisition Limited", 10.22 },

	{ 0, "Health Care", 0 },
	{ 1, "10x Genomics, Inc.", 7.64 },
	{ 1, "1895 Bancorp of Wisconsin, Inc.", 31.23 },
	{ 1, "51job, Inc.", 26 },
	{ 1, "8x8 Inc", 0.5999 },
	{ 1, "AAON, Inc.", 3.3 },
	{ 1, "Abeona Therapeutics Inc.", 207.76 },
	{ 1, "Abraxas Petroleum Corporation", 7.71 },
	{ 1, "Acacia Research Corporation", 28.8 },
	{ 1, "Acadia Healthcare Company, Inc.", 50.63 },
	{ 1, "Acamar Partners Acquisition Corp.", 0.6449 },
	{ 1, "Accelerated Pharma, Inc.", 99.51 },
	{ 1, "Acceleron Pharma Inc.", 2.18 },
	{ 1, "Accuray Incorporated", 1.555 },
	{ 1, "AcelRx Pharmaceuticals, Inc.", 3.38 },
	{ 1, "Acer Therapeutics Inc.", 0.4105 },
	{ 1, "ACI Worldwide, Inc.", 1.34 },
	{ 1, "ACNB Corporation", 0.79 },
	{ 1, "Activision Blizzard, Inc", 2.81 },
	{ 1, "Adamas Pharmaceuticals, Inc.", 0.5025 },
	{ 1, "Adamis Pharmaceuticals Corporation", 16.63 },
	{ 1, "AdaptHealth Corp. ", 4.78 },
	{ 1, "Adaptimmune Therapeutics plc", 39.08 },
	{ 1, "Adaptive Biotechnologies Corporation", 7.28 },
	{ 1, "Addex Therapeutics Ltd", 97.37 },
	{ 1, "Adesto Technologies Corporation", 1.7 },
	{ 1, "Adial Pharmaceuticals, Inc", 0.2102 },
	{ 1, "Adial Pharmaceuticals, Inc", 3.03 },
	{ 1, "ADTRAN, Inc.", 3.28 },
	{ 1, "Advanced Micro Devices, Inc.", 0.71 },
	{ 1, "Advaxis, Inc.", 21.02 },
	{ 1, "Aegion Corp", 9.04 },
	{ 1, "Aemetis, Inc", 14.39 },
	{ 1, "AeroVironment, Inc.", 0.782 },
	{ 1, "Aerpio Pharmaceuticals, Inc.", 7.79 },
	{ 1, "Aesthetic Medical International Holdings Group Ltd.", 1.15 },
	{ 1, "Aethlon Medical, Inc.", 3.16 },
	{ 1, "AGBA Acquisition Limited", 2.75 },
	{ 1, "Agenus Inc.", 3.19 },
	{ 1, "Agilysys, Inc.", 53.04 },

	{ 0, "Miscellaneous", 0  },
	{ 1, "360 Finance, Inc.", 6.8 },
	{ 1, "Acacia Communications, Inc.", 2.57 },

	{ 0, "n/a", 0 },
	{ 1, "Accelerate Diagnostics, Inc.", 832 },
	{ 1, "Adverum Biotechnologies, Inc.", 19.0558 },
	{ 1, "AdvisorShares Dorsey Wright Alpha Equal Weight ETF", 26.5849 },
	{ 1, "AdvisorShares Dorsey Wright FSM All Cap World ETF", 25.7884 },
	{ 1, "AdvisorShares Dorsey Wright FSM US Core ETF", 20.4729 },
	{ 1, "AdvisorShares Dorsey Wright Micro-Cap ETF", 21.29 },
	{ 1, "AdvisorShares Dorsey Wright Short ETF", 23.0243 },

	{ 0, "Public Utilities", 0 },
	{ 1, "Adobe Inc.", 11.38 },

	{ 0, "Technology", 0 },
	{ 1, "1st Source Corporation", 15.14 },
	{ 1, "21Vianet Group, Inc.", 34.89 },
	{ 1, "36Kr Holdings Inc.", 62.88 },
	{ 1, "8i Enterprises Acquisition Corp", 15.49 },
	{ 1, "Achieve Life Sciences, Inc. ", 27.35 },
	{ 1, "AC Immune SA", 67.25 },
	{ 1, "Aclaris Therapeutics, Inc.", 59.16 },
	{ 1, "Act II Global Acquisition Corp.", 70.15 },
	{ 1, "ADDvantage Technologies Group, Inc.", 12 },
	{ 1, "ADMA Biologics Inc", 375.17 },
	{ 1, "Advanced Energy Industries, Inc.", 52.74 },
	{ 1, "Agile Therapeutics, Inc.", 20.1 },
	{ 1, "Agios Pharmaceuticals, Inc.", 20.89 },
	{ 0, NULL }
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


	//Last, let's add all of this and test tables...
	zTable *mt = malloc( sizeof( zTable ) );
	lt_init( mt, NULL, 2048 );
	struct inc *inc = inc_list;	
	int key = 0;
	while ( inc->key ) {
		if ( inc->depth ) {
fprintf( stderr, "adding inner record\n" );
			lt_addtextkey( mt, inc->key );
			lt_addfloatvalue( mt, inc->val );
			lt_finalize( mt );
		}
		else {
fprintf( stderr, "adding outer record\n" );
			if ( key == 1 ) {
				lt_ascend( mt );
				key = 0;
			}
			lt_addtextkey( mt, inc->key );
			lt_descend( mt );
			key = 1;
		}
		inc++;
	}

	lt_dump( mt );
	lt_free( mt );
	free( mt );
	return 0;
}
