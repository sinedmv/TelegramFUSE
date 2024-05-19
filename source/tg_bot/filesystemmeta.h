#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

struct MessageWithFileData {
    MessageWithFileData(std::int32_t messageId, std::string path, std::int32_t date);
    std::int32_t messageId;
    std::string path;
    std::int32_t date;
};

class FileSystemMeta {
public:
    FileSystemMeta(Bot& bot);
    void ReceiveMessage(Message::Ptr& message);
    void ConsistencyCheck();
private:
    Bot& bot;
    vector<MessageWithFileData> filesMetaData;
    std::int64_t chatId;

    std::string GetAbsolutePath(Message::Ptr& message);
    void GetAllMetaDataAboutFiles();
    void SaveFile(std::int32_t messageId, string& absolutePath, std::int32_t date, Bot& bot, std::int64_t chatId);
};
