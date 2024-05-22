#include "localfilesystem.h"

#include <cstdlib>

const std::string directoriesFile = "/source/directories.txt";
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
    void FileSystemMeta::GetAllMetaDataAboutFiles() {
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

}

MessageWithFileData LocalFileSystemWithTgAPI::SendFile(std::string path, std::string content) {

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

