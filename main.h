/* 
 * File:   main.h
 * Author: romanius
 *
 * Created on 1 Апрель 2013 г., 14:46
 */

#ifndef MAIN_H
#define	MAIN_H

//#define LINUX

#ifdef LINUX
  extern char  __etext;
#endif

#ifdef DEBUG
  #define PRINT_FUNCTION printf
#else
  #define PRINT_FUNCTION logprintf
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "CMemory.h"

#endif	/* MAIN_H */

