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

#include "UniformChurnGenerator.h"

Define_Module(UniformChurnGenerator);

UniformChurnGenerator::UniformChurnGenerator() {
    churn = NULL;
}

UniformChurnGenerator::~UniformChurnGenerator() {
    if (churn != NULL) {
        cancelAndDelete(churn);
    }
}

void UniformChurnGenerator::initialize() {
    departRate = par("depart_rate");
    arrivalRate = par("arrival_rate");
    churnCycle = par("churn_cycle");
    max = par("overlay_size_max");
    min = par("overlay_size_min");
    churn = new cMessage(msg::CHURN_CYCLE);
    scheduleAt(simTime() + churnCycle, churn);
}

void UniformChurnGenerator::handleMessage(cMessage *msg) {
    if (msg->isName(msg::CHURN_CYCLE)) {
        double depart = uniform(0, 1);
        int size = GlobalNodeListAccess().get()->chordSize();
        if (depart < departRate && size > min) {
            ChordInfo* toRemove = NULL;
            do {
                toRemove = GlobalNodeListAccess().get()->randChord();
            } while (toRemove == NULL);
            IPvXAddress addrToRemove =
                    GlobalNodeListAccess().get()->getChordAddr(
                            toRemove->getChordId());
            UnderlayConfiguratorAccess().get()->removeNode(addrToRemove);

            cout << simTime() << " remove node: " << toRemove->getChordId() << endl;

            GlobalStatisticsAccess().get()->DEPARTURE++;
        }
        double arrival = uniform(0, 1);
        if (arrival < arrivalRate && size < max) {
            UnderlayConfiguratorAccess().get()->addNode();
            GlobalStatisticsAccess().get()->ARRIVAL++;
        }
        scheduleAt(simTime() + churnCycle, churn);
    }
}
