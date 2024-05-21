#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

struct MessageWithFileData {
    MessageWithFileData(std::int32_t messageId, const std::string& fileId, const std::string& path, std::int32_t date);
    std::int32_t messageId;
    std::string fileId;
    std::string path;
    std::int32_t date;
};

class FileSystemMeta {
public:
    FileSystemMeta(Bot& bot);
    void ReceiveMessage(Message::Ptr& message);
    std::string GetFile(const std::string& telegramPath);
    void SendTestFile();
private:
    Bot& bot;
    vector<MessageWithFileData> filesMetaData;
    std::int64_t chatId;

    std::string GetAbsolutePath(Message::Ptr& message);
    void GetAllMetaDataAboutFiles();
    void SaveFile(std::int32_t messageId, string& telegramPath, string& fileId, std::int32_t date, Bot& bot, std::int64_t chatId);
};
