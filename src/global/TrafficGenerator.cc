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

#include "TrafficGenerator.h"

Define_Module(TrafficGenerator);

TrafficGenerator::TrafficGenerator() {
    traffic = new cMessage(msg::TRAFFIC_CHORD);
}

TrafficGenerator::~TrafficGenerator() {
    // destroy self timer messages
    cancelAndDelete(traffic);
}

void TrafficGenerator::initialize() {
    traffic_cycle = par("traffic_cycle");
    scheduleAt(simTime() + traffic_cycle, traffic);
}

void TrafficGenerator::final() {
    ;
}

void TrafficGenerator::handleMessage(cMessage *msg) {
    if (msg->isName(msg::TRAFFIC_CHORD)) {
        ChordInfo* sender = NULL;
        ChordInfo* target = NULL;
        do {
            sender = GlobalNodeListAccess().get()->randChord();
            target = GlobalNodeListAccess().get()->randChord();
        } while (target == NULL || sender == NULL
                || target->getChordId() == sender->getChordId()
                || !GlobalNodeListAccess().get()->isReady(sender->getChordId())
                || !GlobalNodeListAccess().get()->isReady(target->getChordId()));
        ChordMessage* message = new ChordMessage(msg::CHORD_LOOK_UP);
        message->setType(ChordMsgType::LOOK_UP);
        message->setSender(sender->getChordId());
        message->setContent(to_string(target->getChordId()).c_str());
        message->setHop(0);

        IPvXAddress destAddr = GlobalNodeListAccess().get()->getChordAddr(
                sender->getChordId());
        UDPControlInfo* udpControlInfo = new UDPControlInfo();
        udpControlInfo->setDestAddr(destAddr);
        message->setControlInfo(udpControlInfo);
        SimpleNodeEntry* destEntry = sender->getEntry();
        cSimpleModule::sendDirect(message, 0, 0, destEntry->getTcpIPv4Gate());

        cout << simTime() << " Generate traffic for lookup "
                << target->getChordId() << " from " << sender->getChordId()
                << endl;

        scheduleAt(simTime() + traffic_cycle, traffic);
    }
}
