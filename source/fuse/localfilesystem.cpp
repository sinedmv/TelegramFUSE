#include "localfilesystem.h"

#include <cstdlib>
#include <filesystem>
#include <set>

const std::string metaFile = "/source/metaFile.txt";

LocalFileSystemWithTgAPI::LocalFileSystemWithTgAPI() {
    bot = new Bot("7001811625:AAEg0fFOYm-yJ0ld9CKYEFT-E9xUQyF9lfs");
    chatId = -1002089796790;
}

LocalFileSystemWithTgAPI::~LocalFileSystemWithTgAPI() {
    std::string command = "/source/tg_bot/build/main";
    system(command.c_str());
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
    std::vector<MessageWithFileData> filesMeta = GetAllFilesMeta();
    return ExtractFirstDirectories(filesMeta);
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
        if (line.find(path) != std::string::npos) {
            pathExists = true;
            std::istringstream iss(line);
            std::int32_t messageId_;
            iss >> messageId_;
            bot->getApi().deleteMessage(chatId, messageId_);
        } else {
            content += line + "\n";
        }
    }

    inputFile.close();

    if (pathExists) {
        std::ofstream file(metaFile, std::ios::trunc);
        file << content;
        file.close();
    }
}

void LocalFileSystemWithTgAPI::SendFile(std::string path, std::string content) {
    std::string fileName = getFileName(path);
    std::ofstream outFile(fileName);
    outFile << content;
    outFile.close();

    //DeleteFileByAbsolutePath(path);
    try {
        auto message = bot->getApi().sendDocument(chatId, InputFile::fromFile(path, GetMimeTypeFromExtension(fileName)));
    } catch(std::exception e) {

    }

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

