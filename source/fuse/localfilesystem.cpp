#include "localfilesystem.h"

#include <cstdlib>
#include <filesystem>
#include <set>

const std::string metaFile = "/source/metaFile.txt";
const std::string metaFolder = "/source/metaFolder.txt";

LocalFileSystemWithTgAPI::LocalFileSystemWithTgAPI() {
    bot = new Bot("7001811625:AAEg0fFOYm-yJ0ld9CKYEFT-E9xUQyF9lfs");
    chatId = -1002089796790;
}

LocalFileSystemWithTgAPI::~LocalFileSystemWithTgAPI() {
    std::string command = "/source/tg_bot/build/main";
    system(command.c_str());
}

std::string ExtractDirectory(const std::string& path) {
    std::size_t startPos = path.find_first_not_of('/');
    std::size_t endPos = path.find('/', startPos);
    if (startPos != std::string::npos && endPos != std::string::npos) {
        return "#" + path.substr(startPos, endPos - startPos);
    }
    return "";
}

std::vector<std::string> ExtractFirstDirectories(const std::vector<MessageWithFileData>& filesMeta) {
    std::set<std::string> firstDirectoriesSet;

    for (const auto& meta : filesMeta) {
        std::size_t startPos = meta.path.find_first_not_of('/');
        std::size_t endPos = meta.path.find('/', startPos);
        if (startPos != std::string::npos && endPos != std::string::npos) {
            firstDirectoriesSet.insert(meta.path.substr(startPos, endPos - startPos));
        }
    }

    std::vector<std::string> firstDirectories(firstDirectoriesSet.begin(), firstDirectoriesSet.end());
    return firstDirectories;
}

std::vector<std::string> LocalFileSystemWithTgAPI::GetAllAvailableDirectories() {
    std::vector<std::string> tags;
    std::ifstream file(metaFolder);

    std::string line;
    while (std::getline(file, line)) {
        tags.push_back(line);
    }

    return tags;
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
            MessageWithFileData* tmp = new MessageWithFileData(messages[i].messageId, messages[i].fileId, messages[i].path, messages[i].date);
            return tmp;
        }
    }

    return nullptr;
}

std::string getFileName(const std::string& filePath) {
    size_t pos = filePath.find_last_of("/\\");
    if (pos != std::string::npos) {
        return filePath.substr(pos + 1);
    }
    return filePath;
}

std::string LocalFileSystemWithTgAPI::GetFileDataByAbsolutePath(std::string path) {
    auto fileMeta = GetFileMeta(path);
    if (fileMeta == nullptr) {
        return "";
    }


    File::Ptr file = bot->getApi().getFile(fileMeta->fileId);
    return bot->getApi().downloadFile(file->filePath);
}

void LocalFileSystemWithTgAPI::DeleteFileByAbsolutePath(std::string path) {
    std::ifstream inputFile(metaFile);
    std::string line;
    std::string content;
    bool pathExists = false;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::int32_t messageId_;
        std::string fileId;
        std::string path_;
        std::int32_t date;
        if (iss >> messageId_ >> fileId >> path_ >> date) {
            if (path_ == path) {
                pathExists = true;
                bot->getApi().deleteMessage(chatId, messageId_);
            } else {
                content += line + "\n";
            }
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    inputFile.close();

    if (pathExists) {
        std::ofstream file(metaFile, std::ios::trunc);
        file << content;
        file.close();
    }
}

void LocalFileSystemWithTgAPI::SaveFileInMeta(std::int32_t messageId, std::string& fileId, std::string& absolutePath, std::int32_t date) {
    DeleteFileByAbsolutePath(absolutePath);

    std::ofstream file(metaFile, std::ios::app);
    file << messageId << " " << fileId << " " << absolutePath << " " << date << std::endl;
    file.close();
}

void LocalFileSystemWithTgAPI::SendFile(std::string path, std::string content) {
    std::string fileName = getFileName(path);
    std::ofstream outFile(fileName, std::ios::trunc);
    outFile << content;
    outFile.close();

    DeleteFileByAbsolutePath(path);
    auto message = bot->getApi().sendDocument(chatId, InputFile::fromFile(fileName, GetMimeTypeFromExtension(fileName)), "", ExtractDirectory(path));
    File::Ptr file = bot->getApi().getFile(message->document->fileId);
    SaveFileInMeta(message->messageId, file->fileId, path, message->date);

    std::filesystem::remove(fileName);
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

