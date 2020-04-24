#include "sum/sum.h"
#include <iostream>
#include <sqlite3.h>

int main() {
	sqlite3 *db;
	
	int rc;
	
	rc = sqlite3_open("test.db", &db);
	
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return (0);
	} else {
		fprintf(stderr, "Opened database successfully\n");
	}
	sqlite3_close(db);
	std::cout << "Hello!" << std::endl;
	std::cout << "5 + 7 = " << sum(5, 7) << std::endl;
	
	return 0;
}
