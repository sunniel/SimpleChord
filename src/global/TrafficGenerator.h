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

#ifndef __SIMPLECHORD_TRAFFICGENERATOR_H_
#define __SIMPLECHORD_TRAFFICGENERATOR_H_

#include <omnetpp.h>
#include "GlobalNodeListAccess.h"
#include "../common/Constants.h"
#include "../messages/UDPControlInfo_m.h"
#include "../messages/ChordMessage_m.h"

using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class TrafficGenerator: public cSimpleModule {
    simtime_t traffic_cycle;
    cMessage* traffic;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void final();
public:
    TrafficGenerator();
    ~TrafficGenerator();
};

#endif
