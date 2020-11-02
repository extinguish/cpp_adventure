//
// Created by guoshichao on 19-12-30.
//

#ifndef CPPADVENTURE_ASTRINGUTILS_H
#define CPPADVENTURE_ASTRINGUTILS_H

#include <stddef.h>

namespace adasplus {
    struct AStringUtils {
        // similar to strncmp or strcasecmp, but case sensitivity is parametric
        static int Compare(const char *a, const char *b, size_t len, bool ignoreCase);

        // matches a string (str) to a glob pattern that supports:
        //    * - matches any number of characters
        static bool MatchesGlob(const char *glob, size_t globLen, const char *str, size_t strLen, bool ignoreCase);
    };
}

#endif //CPPADVENTURE_ASTRINGUTILS_H
