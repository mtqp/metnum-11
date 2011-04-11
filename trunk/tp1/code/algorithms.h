#ifndef _ALGORITHMS_H__
#define _ALGORITHMS_H__

#include "includes.h"
#include "Real.h"

typedef Real (SERIES)(int t_digits, int cantIt, bool truncate);

SERIES Gregory;
SERIES Machin;
SERIES Ramanujan;

#endif
