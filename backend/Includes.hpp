#ifndef __INCLUDES_H
#define __INCLUDES_H

#include <cstdint>
#include <stdlib.h>
#include <stdexcept>
#include <stdio.h>
#include <sstream>
#include <string>
#include <iomanip>

typedef unsigned int uint;

#define SIGN_EXTEND_32BIT(B, V) ((V >> (B - 1)) & 1) ? \
    (0xFFFFFFFF << B) | V : V

#endif
