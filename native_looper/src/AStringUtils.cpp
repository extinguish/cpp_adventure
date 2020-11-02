//
// Created by guoshichao on 19-12-30.
//
#include "AStringUtils.h"
#include <string.h>

int adasplus::AStringUtils::Compare(const char *a, const char *b, size_t len, bool ignoreCase) {
    // this method relies on a trailing '\0' if a or b are shorter than len
    return ignoreCase ? strncasecmp(a, b, len) : strncmp(a, b, len);
}

bool
adasplus::AStringUtils::MatchesGlob(const char *glob, size_t globLen, const char *str, size_t strLen, bool ignoreCase) {
    // this method does not assume a trailing '\0'
    size_t ix = 0, globIx = 0;

    // pattern must match until first '*'
    while (globIx < globLen && glob[globIx] != '*') {
        ++globIx;
    }
    if (strLen < globIx || Compare(str, glob, globIx /* len */, ignoreCase)) {
        return false;
    }
    ix = globIx;

    // process by * separated sections
    while (globIx < globLen) {
        ++globIx;
        size_t start = globIx;
        while (globIx < globLen && glob[globIx] != '*') {
            ++globIx;
        }
        size_t len = globIx - start;
        const char *pattern = glob + start;

        if (globIx == globLen) {
            // last pattern must match tail
            if (ix + len > strLen) {
                return false;
            }
            const char *tail = str + strLen - len;
            return !Compare(tail, pattern, len, ignoreCase);
        }
        // progress after first occurrence of pattern
        while (ix + len <= strLen && Compare(str + ix, pattern, len, ignoreCase)) {
            ++ix;
        }
        if (ix + len > strLen) {
            return false;
        }
        ix += len;
        // we will loop around as globIx < globLen
    }

    // we only get here if there were no * in the pattern
    return ix == strLen;
}
