// Copyright (c) 2014, Emmanuel Goossaert. All rights reserved.
// Use of this source code is governed by the BSD 3-Clause License,
// that can be found in the LICENSE file.

#ifndef KINGDB_ORDER_H_
#define KINGDB_ORDER_H_

#include "debug.h"

#include <set>

#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "logger.h"
#include "status.h"
#include "coding.h"
#include "crc32c.h"
#include "byte_array.h"
#include "options.h"

namespace kdb {

    enum class OrderType {
        Put, Delete
    };

    struct Order {
        std::thread::id tid;
        WriteOptions write_options;
        OrderType type;
        ByteArray key;
        ByteArray chunk;
        uint64_t offset_chunk;
        uint64_t size_value;
        uint64_t size_value_compressed;
        uint32_t crc32;
        bool is_large;

        bool IsFirstPart() {
            return (offset_chunk == 0);
        }

        bool IsMiddleOrLastPart() {
            return !IsFirstPart();
        }

        bool IsLastPart() {
            return ((size_value_compressed == 0 && chunk.size() + offset_chunk == size_value)
                    || (size_value_compressed != 0 && chunk.size() + offset_chunk == size_value_compressed));
        }

        bool IsSelfContained() {
            return IsFirstPart() && IsLastPart();
        }

        bool IsLarge() {
            return is_large;
        }
    };

} // namespace kdb

#endif // KINGDB_ORDER_H_
