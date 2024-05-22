#include "localfilesystem.h"

#include <cstdlib>
#include <filesystem>

const std::string metaFile = "/source/metaFile.txt";

LocalFileSystemWithTgAPI::LocalFileSystemWithTgAPI() {
    bot = new Bot("7001811625:AAEg0fFOYm-yJ0ld9CKYEFT-E9xUQyF9lfs");
    chatId = -1002089796790;
}

LocalFileSystemWithTgAPI::~LocalFileSystemWithTgAPI() {
    std::string command = "/source/tg_bot/build/main";
    system(command.c_str());
}

std::vector<std::string> LocalFileSystemWithTgAPI::GetAllAvailableDirectories() {
    std::vector<MessageWithFileData> filesMeta = GetAllFilesMeta();
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

std::vector<MessageWithFileData> LocalFileSystemWithTgAPI::GetAllFilesMeta() {
    std::vector<MessageWithFileData> resultVector;
    std::ifstream file(metaFile);

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

    return resultVector;
}

MessageWithFileData* LocalFileSystemWithTgAPI::GetFileMeta(std::string path) {
    auto messages = GetAllFilesMeta();
    for (size_t i = 0; i < messages.size(); i++) {
        if (messages[i].path == path) {
            return &messages[i];
        }
    }

    return nullptr;
}

std::string LocalFileSystemWithTgAPI::GetFileDataByAbsolutePath(std::string path) {
    auto fileMeta = GetFileMeta(path);
    if (fileMeta == nullptr) {
        return "";
    }
    File::Ptr file = bot.getApi().getFile(fileMeta->fileId);
    return bot.getApi().downloadFile(file->filePath);
}

void LocalFileSystemWithTgAPI::DeleteFileByAbsolutePath(std::string path) {
    std::ifstream inputFile(metaFile);
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

std::string getFileName(const std::string& filePath) {
    size_t pos = filePath.find_last_of("/\\");
    if (pos != std::string::npos) {
        return filePath.substr(pos + 1);
    }
    return filePath;
}

MessageWithFileData LocalFileSystemWithTgAPI::SendFile(std::string path, std::string content) {
    std::string fileName = getFileName(path);
    std::ofstream outFile(filePath);
    outFile << content;
    outFile.close();

    DeleteFileByAbsolutePath(path);
    auto message = bot.getApi().sendDocument(chatId, InputFile::fromFile("/source/fuse/build/" + fileName, GetMimeTypeFromExtension(fileName)));
    std::filesystem::remove(filename);
    return message;
}

std::string LocalFileSystemWithTgAPI::GetMimeTypeFromExtension(const std::string& filePath) {
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

MessageWithFileData::MessageWithFileData(std::int32_t messageId, const std::string& fileId, const std::string& path, std::int32_t date) {
    this->messageId = messageId;
    this->fileId = fileId;
    this->path = path;
    this->date = date;
}
