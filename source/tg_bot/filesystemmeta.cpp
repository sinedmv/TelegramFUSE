#include "filesystemmeta.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdint>
#include <regex>

using namespace std;
using namespace TgBot;

const std::string messagesBackupFile = "/source/fs/messagesBackup.txt";
const std::string fuseDirectory = "/source/fs/";

MessageWithFileData::MessageWithFileData(std::int32_t messageId, std::string path, std::int32_t date) : messageId(messageId), path(path), date(date) {}

FileSystemMeta::FileSystemMeta(Bot& bot) : bot(bot) {
    GetAllMetaDataAboutFiles();
    chatId = -1002089796790;
}

std::string FileSystemMeta::GetAbsolutePath(Message::Ptr& message) {
    std::string absoluteFilePath = fuseDirectory;
    std::regex pattern("#.*");
    if (message->caption.length() != 0 && std::regex_match(message->caption, pattern)) {
        absoluteFilePath += message->caption.substr(1);
        absoluteFilePath += "/";
    }
    absoluteFilePath += message->document->fileName;

    return absoluteFilePath;
}

void FileSystemMeta::GetAllMetaDataAboutFiles() {
    std::vector<MessageWithFileData> resultVector;
    std::ifstream file(messagesBackupFile);

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::int32_t messageId;
        std::string path;
        std::int32_t date;
        if (iss >> messageId >> path >> date) {
            resultVector.emplace_back(messageId, path, date);
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    filesMetaData = resultVector;
}

bool CheckFileName(string& name) {
    if (name == "messagesBackup.txt" ||
        name.empty()) {
            return false;
    }
    return true;
}

void DeleteMatches(string& absolutePath, Bot& bot, std::int64_t chatId) {
    std::ifstream inputFile(messagesBackupFile);
    std::string line;
    std::string content;
    bool pathExists = false;
    while (std::getline(inputFile, line)) {
        if (line.find(absolutePath) != std::string::npos) {
            pathExists = true;
            std::istringstream iss(line);
            std::int32_t messageId_;
            std::string path_;
            std::int32_t date_;
            iss >> messageId_ >> path_ >> date_;
            bot.getApi().deleteMessage(chatId, messageId_);
        } else {
            content += line + "\n";
        }
    }

    inputFile.close();

    if (pathExists) {
        std::ofstream file(messagesBackupFile, std::ios::trunc);
        file << content;
        file.close();
    }
}

void FileSystemMeta::SaveFile(std::int32_t messageId, string& absolutePath, std::int32_t date, Bot& bot, std::int64_t chatId) {
    DeleteMatches(absolutePath, bot, chatId);

    std::ofstream file(messagesBackupFile, std::ios::app);
    file << messageId << " " << absolutePath << " " << date << std::endl;
    file.close();
}

void FileSystemMeta::ReceiveMessage(Message::Ptr& message) {
    if (message->document != nullptr) {
        File::Ptr file = bot.getApi().getFile(message->document->fileId);

        if (!CheckFileName(message->document->fileName)) {
            bot.getApi().sendMessage(message->chat->id, "Файл с таким именем не может быть создан");
            return;
        }        

        string absoluteFilePath = GetAbsolutePath(message);

        std::ofstream inFile(absoluteFilePath, std::ios::trunc);

        if (inFile.is_open()) {
            inFile << bot.getApi().downloadFile(file->filePath);
            inFile.close();
            SaveFile(message->messageId, absoluteFilePath, message->date, bot, message->chat->id);
        } else {
            bot.getApi().sendMessage(message->chat->id, "Проверьте правильность введенной директории. Ошибка при создании файла:" + absoluteFilePath);
        }
    } else {
        bot.getApi().sendMessage(message->chat->id, "Я - безупречная файловая система. Не надо меня тыкать сообщениями без файлов");
    } 
}

std::string getMimeTypeFromExtension(const std::string& filePath) {
    size_t lastDot = filePath.find_last_of(".");
    if (lastDot == std::string::npos) {
        return "application/octet-stream"; 
    }
    std::string extension = filePath.substr(lastDot + 1);
    static const std::unordered_map<std::string, std::string> extensionToMimeType {
        {"txt", "text/plain"},
        {"jpg", "image/jpeg"},
        {"png", "image/png"},
    };

    auto it = extensionToMimeType.find(extension);
    if (it != extensionToMimeType.end()) {
        return it->second;
    } else {
        return "application/octet-stream";
    }
}

std::vector<std::string> GetModifiedFiles() {
    // We need to get absolute paths from query-meta-file.
    // Suppose that we already know how to do this
    std::vector<std::string> files;
    files.push_back("/source/fs/Тест.txt");
    return files;
}

void FileSystemMeta::ConsistencyCheck() {
    std::vector<std::string> files = GetModifiedFiles();

    for (int i = 0; i < files.size(); ++i) {
        auto inputFile = TgBot::InputFile::fromFile(files[i], getMimeTypeFromExtension(files[i]));
        auto message = bot.getApi().sendDocument(chatId, inputFile);
        SaveFile(message->messageId, files[i], message->date, bot, message->chat->id);
    }
}