/*    Copyright 2014 MongoDB Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <string>
#include <bitset>

#include "mongo/client/export_macros.h"
#include "mongo/db/jsobj.h"

namespace mongo {

    class MONGO_CLIENT_API WriteConcern {
    public:
        WriteConcern();

        static const char kMajority[];

        // Getter methods
        int nodes() const;
        const std::string& nodes_str() const;
        bool journal() const;
        bool fsync() const;
        int timeout() const;

        // Setter methods
        WriteConcern& nodes(int w);
        WriteConcern& nodes(const StringData& w);
        WriteConcern& journal(bool j);
        WriteConcern& fsync(bool fsync);
        WriteConcern& timeout(int timeout);

        // Functional methods
        bool requiresConfirmation() const;
        bool hasNodeStr() const;

        // Conversion methods
        BSONObj toBson() const;
        std::string toString() const;

        // Static instances
        static const WriteConcern acknowledged;
        static const WriteConcern unacknowledged;
        static const WriteConcern majority;

    private:
        // Enabled option book keeping
        static const size_t kNumOptions = 5;
        enum Options { kW, kWStr, kJ, kFsync, kTimeout };
        std::bitset<kNumOptions> _enabled;

        // Actual option values
        int _w;
        std::string _w_str;
        bool _j;
        bool _fsync;
        int32_t _timeout;
    };

} // namespace mongo
