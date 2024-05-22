#include "filesystemmeta.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdint>
#include <regex>

using namespace std;
using namespace TgBot;

const std::string messagesBackupFile = "/source/metaFile.txt";
const std::string directoriesFile = "/source/directories.txt";

std::string GetMimeTypeFromExtension(const std::string& filePath) {
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


MessageWithFileData::MessageWithFileData(std::int32_t messageId, const std::string& fileId, const std::string& path, std::int32_t date) : messageId(messageId), fileId(fileId), path(path), date(date) {}

FileSystemMeta::FileSystemMeta(Bot& bot) : bot(bot) {
    GetAllMetaDataAboutFiles();
    chatId = -1002089796790;
}

std::string GetDirectory(const std::string& text) {
    std::regex pattern("#.*");
    if (text.length() != 0 && std::regex_match(text, pattern)) {
        return "/" + text.substr(1);
    }
    return "";
}

std::vector<std::string> GetAvailableDirectories() {
    std::vector<std::string> directories;
    std::ifstream file(directoriesFile);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << directoriesFile << std::endl;
        return directories;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            directories.push_back(line);
        }
    }
    
    file.close();
    return directories;
}

bool CheckDirectoryExist(const std::string& directory) {
    if (directory.empty()) {
        return true;
    }
    auto directories = GetAvailableDirectories();
    for (int i = 0; i < directories.size(); ++i) {
        if (directories[i] == directory) {
            return true;
        }
    }
    return false;
}

std::string FileSystemMeta::GetAbsolutePath(Message::Ptr& message) {
    std::string absolutePath = "/";
    std::regex pattern("#.*");
    std::string directory = GetDirectory(message->caption);
    if (directory.length() != 0) {
        absolutePath += directory;
        absolutePath += "/";
    }
    absolutePath += message->document->fileName;

    return absolutePath;
}

void FileSystemMeta::GetAllMetaDataAboutFiles() {
    std::vector<MessageWithFileData> resultVector;
    std::ifstream file(messagesBackupFile);

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::int32_t messageId;
        std::string fileId;
        std::string path;
        std::int32_t date;
        if (iss >> messageId >> fileId >> path >> date) {
            resultVector.emplace_back(messageId, fileId, path, date);
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    filesMetaData = resultVector;
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
            iss >> messageId_;
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

void FileSystemMeta::SaveFile(std::int32_t messageId, string& fileId, string& absolutePath, std::int32_t date, Bot& bot, std::int64_t chatId) {
    DeleteMatches(absolutePath, bot, chatId);

    std::ofstream file(messagesBackupFile, std::ios::app);
    file << messageId << " " << fileId << " " << absolutePath << " " << date << std::endl;
    file.close();
}

void FileSystemMeta::SendTestFile() {
    bot.getApi().sendDocument(chatId, InputFile::fromFile("/source/fs/messagesBackup.txt", GetMimeTypeFromExtension("/source/fs/messagesBackup.txt")));
}

void FileSystemMeta::ReceiveMessage(Message::Ptr& message) {
    if (message->document != nullptr) {
        File::Ptr file = bot.getApi().getFile(message->document->fileId);

        string absoluteFilePath = GetAbsolutePath(message);   

        if (CheckDirectoryExist(GetDirectory(message->caption))) {
            SaveFile(message->messageId, file->fileId, absoluteFilePath, message->date, bot, message->chat->id);
        } else {
            bot.getApi().sendMessage(message->chat->id, "Проверьте правильность введенной директории. Ошибка при создании файла:" + absoluteFilePath);
        }
    } else {
        bot.getApi().sendMessage(message->chat->id, "Я - безупречная файловая система. Не надо меня тыкать сообщениями без файлов");
    }
}

