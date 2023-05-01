#ifndef FILEIO_H
#define FILEIO_H

#include "cust.h"

#define MAXLINELEN 5
#define INFILENAME "c_file"
#define OUTFILENAME "r_log"
#define DIVIDER "-----------------------------------------------------------------------"

FILE* open(char* name, char* mode);
cust_t* readCustFile(FILE* file, _Bool* eof);

#endif