#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define NAME "miao.db"

int main() {		
		sqlite3 *db;
		sqlite3_stmt *stmt;
		int rc;
		char *errmsg = 0;

		rc = sqlite3_open(NAME, &db);
		if(rc) {
			fprintf(stderr, "can't open db %s: %s\n", NAME, sqlite3_errmsg(db));
			sqlite3_close(db);
			exit(1);
		}
		rc = sqlite3_prepare(db, "select * from words", 0, &stmt, 0);
		if(rc!=SQLITE_OK) {
			fprintf(stderr, "sql error #%d: %s\n", rc, sqlite3_errmsg(db));
		}
		else while((rc = sqlite3_step(stmt)) != SQLITE_DONE) {
			switch(rc) {
				case SQLITE_BUSY:
					fprintf(stderr, "busy, wait 1 sec\n");
					break;
				case SQLITE_ROW:
					{
						int n = sqlite3_column_count(stmt);
						int i;
						for(i=0; i<n; i++) {
							printf("%s = ", sqlite3_column_name(stmt, i));
							switch(sqlite3_column_type(stmt, i)) {
								case SQLITE_TEXT:
									printf("%s", sqlite3_column_text(stmt, i));
									break;
								case SQLITE_INTEGER:
									printf("%d", sqlite3_column_int(stmt,i));
									break;
								case SQLITE_FLOAT:
									printf("%f", sqlite3_column_double(stmt,i));
									break;
								case SQLITE_BLOB:
									printf("(blob)");
									break;
								case SQLITE_NULL:
									printf("(null)");
									break;
								default:
									printf("(unknown: %d)", sqlite3_column_type(stmt, i));
							}
							printf("\n");
						}
					}
				
			}
		}
}
