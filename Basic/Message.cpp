#include "Message.h"

Message::Message() {
    delta = GameData();
    newEventListenerInfo = NewEventListenerInfo();
    kill=false;
    listenerId=0;
}