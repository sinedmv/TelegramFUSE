#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

int main() {
    string token = "7001811625:AAEg0fFOYm-yJ0ld9CKYEFT-E9xUQyF9lfs";
    printf("Token: %s\n", token.c_str());

    Bot bot(token);

    bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (message->document != NULL) {
            File::Ptr file = bot.getApi().getFile(message->document->fileId);
            string fileContent = bot.getApi().downloadFile(file->filePath);
            string fileName = message->document->fileName;

            std::ofstream inFile(fileName);

            if (inFile.is_open()) {
                inFile << fileContent;
                inFile.close();
                bot.getApi().sendMessage(message->chat->id, "Файл " + fileName + " корректно сохранен");
            } else {
                bot.getApi().sendMessage(message->chat->id, "Ошибка при создании/открытии файла:" + fileName);
            }
        } else {
            bot.getApi().sendMessage(message->chat->id, "Прошу прощения, я умею работать только с сообщениями с файлом");
        } 
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
            longPoll.start();
        }
    } catch (exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}