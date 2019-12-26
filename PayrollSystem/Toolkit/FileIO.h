#ifndef _FILEIO_H
#define _FILEIO_H
#include "FlexibleArray.h"

int CheckJSONFileValid(const char * fileName);
int GetWholeFile(FArray *buffer,const char *fileName);
int CreateEmptyJSON(const char *fileName);

#endif // _FILEIO_H
