#include "Message.h"

Message::Message() {
    delta = GameData();
    newEventListenerInfo = std::make_shared<NewEventListenerInfo>();
    kill=false;
    listenerId=0;
    empty=true;
}

Message::Message(GameData newDelta, NewEventListenerInfo newNewEventListenerInfo, bool newKill, int newListenerId) {
    delta = newDelta;
    newEventListenerInfo = std::make_shared<NewEventListenerInfo>(newNewEventListenerInfo);
    kill=newKill;
    listenerId=newListenerId;
    empty=false;
}