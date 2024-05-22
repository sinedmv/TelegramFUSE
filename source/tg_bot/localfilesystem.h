#include <vector>
#include <string>

struct MessageWithFileData {
    MessageWithFileData(std::int32_t messageId, const std::string& fileId, const std::string& path, std::int32_t date);
    std::int32_t messageId; 
    std::string fileId; // FileId in Telegram
    std::string path;
    std::int32_t date; // UNIX-time
    // We need to use this attribute to the "ctime" and "mtime" commands
};

class LocalFileSystemWithTgAPI {
public:
    std::vector<std::string> GetAllAvailableDirectories();
    std::vector<MessageWithFileData> GetAllFilesMeta();
    MessageWithFileData* GetFileMeta(std::string path); // Will return nullptr if file doesn't exist
    std::string GetFileDataByAbsolutePath(std::string path); // Will return a file data in string-type
    void DeleteFileByAbsolutePath(std::string path); // Will delete all occurrences about this file in Telegram and in meta-files
    MessageWithFileData SendFile(std::string path, std::string content); // Firstly, will delete file from the chat. And after this will send the file
}