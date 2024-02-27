#include "Message.h"

Message::Message() {
    delta=Delta();
    newEventListener="void";
    kill=false;
    listenerId=0;
}