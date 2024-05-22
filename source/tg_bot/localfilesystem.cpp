#include "localfilesystem.h"

std::vector<std::string> LocalFileSystemWithTgAPI::GetAllAvailableDirectories() {
    return std::vector<std::string>{"/lol", "/kek", "/mem"};
}

std::vector<MessageWithFileData> LocalFileSystemWithTgAPI::GetAllFilesMeta() {
    return std::vector<MessageWithFileData>{MessageWithFileData(1, "", "/1.txt", 0), MessageWithFileData(2, "", "/lol/2.txt", 0), MessageWithFileData(3, "", "/kek/3.txt", 0)};
}

MessageWithFileData* LocalFileSystemWithTgAPI::GetFileMeta(std::string path) {
    std::vector<MessageWithFileData> messages = std::vector<MessageWithFileData>{MessageWithFileData(1, "", "/1.txt", 0), MessageWithFileData(2, "", "/lol/2.txt", 0), MessageWithFileData(3, "", "/kek/3.txt", 0)};
    for (size_t i = 0; i < messages.size(); i++) {
        if (messages[i].path == path) {
            return &messages[i];
        }
    }

    return nullptr;
}

std::string LocalFileSystemWithTgAPI::GetFileDataByAbsolutePath(std::string path) {
    return "lol";
}

void LocalFileSystemWithTgAPI::DeleteFileByAbsolutePath(std::string path) {

}

MessageWithFileData LocalFileSystemWithTgAPI::SendFile(std::string path, std::string content) {

}

MessageWithFileData::MessageWithFileData(std::int32_t messageId, const std::string& fileId, const std::string& path, std::int32_t date) {
    this->messageId = messageId;
    this->fileId = fileId;
    this->path = path;
    this->date = date;
}