#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "filesystemmeta.h"


using namespace std; 

int main() {
    string token = "7001811625:AAEg0fFOYm-yJ0ld9CKYEFT-E9xUQyF9lfs";

    Bot bot(token);
    auto fsMeta = new FileSystemMeta(bot);

    bot.getEvents().onAnyMessage([&bot, fsMeta](Message::Ptr message) {  // Захватываем fsMeta
        printf("User wrote %s\n", message->text.c_str());
        fsMeta->ReceiveMessage(message);
    });

    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        exit(0);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            fsMeta->ConsistencyCheck();
            longPoll.start();
        }
    } catch (exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}