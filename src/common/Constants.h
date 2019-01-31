//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
// message names
namespace msg {
// Chord message types
extern const char* CHORD_LOOK_UP;
extern const char* CHORD_FINAL;
extern const char* CHORD_SUCCESSOR;
extern const char* CHORD_QUERY_SUCCESSOR;
extern const char* CHORD_SUCCESSOR_FOUND;
extern const char* CHORD_NOTIFY;
extern const char* CHORD_STORE;
extern const char* CHORD_GET;
extern const char* CHORD_REPLICATE;
extern const char* CHORD_FIX_REPLICA;
extern const char* CHORD_UPDATE_PREDECESSOR;

// global schedules
extern const char* INIT_CHORD;
extern const char* TRAFFIC_CHORD;
extern const char* CHURN_SCAN_CYCLE;
extern const char* CHURN_CYCLE;
extern const char* DATA_DIST_CYCLE;

// Chord schedules
extern const char* CHORD_MAINT;
}

namespace data{
// chord data type
extern const char* CHORD_DATA_EMPTY;
}
#endif /* CONSTANTS_H_ */
