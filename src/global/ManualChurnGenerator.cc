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

#include "ManualChurnGenerator.h"

Define_Module(ManualChurnGenerator);

ManualChurnGenerator::ManualChurnGenerator() {
    scan = NULL;
}

ManualChurnGenerator::~ManualChurnGenerator() {
    if (scan != NULL) {
        cancelAndDelete(scan);
    }
}

void ManualChurnGenerator::initialize() {
    scan_cycle = par("scan_cycle");
    scan = new cMessage(msg::CHURN_SCAN_CYCLE);
    scheduleAt(simTime() + scan_cycle, scan);
    WATCH(host);
}

void ManualChurnGenerator::handleMessage(cMessage *msg) {
    if (msg->isName(msg::CHURN_SCAN_CYCLE)) {
        EV << "host: " << host << endl;
        if (!host.empty()) {
            EV << "host: " << endl;
            // host is the chord Id
            unsigned long chordId = util::strToInt(host);
            if (chordId > 0L) {
                IPvXAddress toRemove =
                        GlobalNodeListAccess().get()->getChordAddr(chordId);
                UnderlayConfiguratorAccess().get()->removeNode(toRemove);
            } else {
                UnderlayConfiguratorAccess().get()->addNode();
            }
            host.clear();
        }
        scheduleAt(simTime() + scan_cycle, scan);
    }
}
