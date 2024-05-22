#define FUSE_USE_VERSION 31

#include <fuse3/fuse.h>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <cstring>
#include <errno.h>

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
    MessageWithFileData* GetFileMeta(std::string path);
    std::string GetFileDataByAbsolutePath(std::string path); // Will return a file data in string-type or nullptr if file doesn't exist
    void DeleteFileByAbsolutePath(std::string path); // Will delete all occurrences about this file in Telegram and in meta-files
    MessageWithFileData SendFile(std::string path, std::string content); // Firstly, will delete file from the chat. And after this will send the file
}

LocalFileSystemWithTgAPI tg;

static int my_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
    memset(stbuf, 0, sizeof(struct stat));
    std::string path_str(path);
    std::vector<std::string> tags = tg.GetAllAvailableDirectories(); 
    MessageWithFileData* fileMeta = tg.GetFileMeta(path_str);

    if (path_str == "/") {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (tags.find(path_str) != tags.end()) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (fileMeta != nullptr) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = tg.GetFileDataByAbsolutePath(path_str).size();
        stbuf->st_mtime = (time_t)fileMeta->date;
        stbuf->st_ctime = (time_t)fileMeta->date;
    } else {
        return -ENOENT;
    }

    return 0;
}

static int my_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags) {
    (void) offset;
    (void) fi;
    (void) flags;

    std::vector<std::string> tags = tg.GetAllAvailableDirectories();
    std::vector<MessageWithFileData> filesMeta = tg.GetAllFilesMeta();

    std::set<std::string> files;
    for (int i = 0; i < filesMeta.size(); i++) {
        files.insert(filesMeta[i].path);
    }

    std::string path_str(path);

    filler(buf, ".", NULL, 0, static_cast<fuse_fill_dir_flags>(0));
    filler(buf, "..", NULL, 0, static_cast<fuse_fill_dir_flags>(0));

    if (path_str == "/") {
        for (const auto& tag : tags) {
            filler(buf, tag.c_str() + 1, NULL, 0, static_cast<fuse_fill_dir_flags>(0));
        }

        for (const auto& file : files) {
            if (file.find(path_str) == 0 && file.substr(path_str.length() + 1).find('/') == std::string::npos) {
                filler(buf, file.substr(path_str.length() + 1).c_str(), NULL, 0, static_cast<fuse_fill_dir_flags>(0));
            }
        }
    } else {
        for (const auto& file : files) {
            if (file.find(path_str) == 0 && file.substr(path_str.length() + 1).find('/') == std::string::npos) {
                filler(buf, file.substr(path_str.length() + 1).c_str(), NULL, 0, static_cast<fuse_fill_dir_flags>(0));
            }
        }
    }

    return 0;
}

static int my_open(const char *path, struct fuse_file_info *fi) {
    std::string path_str(path);
    std::vector<MessageWithFileData> filesMeta = tg.GetAllFilesMeta();

    std::set<std::string> files;
    for (int i = 0; i < filesMeta.size(); i++) {
        files.insert(filesMeta[i].path);
    }

    if (files.find(path_str) == files.end())
        return -ENOENT;

    return 0;
}

static int my_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    std::vector<MessageWithFileData> filesMeta = tg.GetAllFilesMeta();

    std::set<std::string> files;
    for (int i = 0; i < filesMeta.size(); i++) {
        files.insert(filesMeta[i].path);
    }

    std::string path_str(path);
    if (files.find(path_str) == files.end())
        return -ENOENT;

    std::string content = tg.GetFileDataByAbsolutePath(path_str);
    if (offset >= content.size())
        return 0;

    if (offset + size > content.size())
        size = content.size() - offset;

    memcpy(buf, content.c_str() + offset, size);
    return size;
}

static int my_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    std::string path_str(path);
    std::vector<MessageWithFileData> filesMeta = tg.GetAllFilesMeta();

    std::set<std::string> files;
    for (int i = 0; i < filesMeta.size(); i++) {
        files.insert(filesMeta[i].path);
    }

    if (files.find(path_str) != files.end())
        return 0;

    tg.SendFile(path_str, "");
    return 0;
}

static int my_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    std::string path_str(path);
    std::vector<MessageWithFileData> filesMeta = tg.GetAllFilesMeta();

    std::set<std::string> files;
    for (int i = 0; i < filesMeta.size(); i++) {
        files.insert(filesMeta[i].path);
    }

    if (files.find(path_str) == files.end())
        return -ENOENT;

    std::string content = tg.GetFileDataByAbsolutePath(path_str);
    if (offset + size > content.size())
        content.resize(offset + size);

    memcpy(&content[offset], buf, size);

    tg.SendFile(path_str, content);
    return size;
}

static int my_unlink(const char* path) {
    std::vector<MessageWithFileData> filesMeta = tg.GetAllFilesMeta();

    std::set<std::string> files;
    for (int i = 0; i < filesMeta.size(); i++) {
        files.insert(filesMeta[i].path);
    }
    if (files.find(path_str) == files.end()) {
        return -ENOENT;
    }

    tg.DeleteFileByAbsolutePath(path_str);
    return 0;
}

static int my_rmdir(const char* path) {
    std::vector<std::string> tags = tg.GetAllAvailableDirectories();
    std::vector<MessageWithFileData> filesMeta = tg.GetAllFilesMeta();

    std::set<std::string> files;
    for (int i = 0; i < filesMeta.size(); i++) {
        files.insert(filesMeta[i].path);
    }

    if (files.find(path_str) == files.end())
        return -ENOTDIR;
    
    for (const auto& file : files) {
        folder = file.substr(0, path_str.length() + 1);
        if (folder == path_str) {
            tg.DeleteFileByAbsolutePath(path_str);
        }
    }
    return 0;
}

static struct fuse_operations operations = {
    .getattr    = my_getattr,
    .unlink     = my_unlink,
    .rmdir      = my_rmdir,
    .open       = my_open,
    .read       = my_read,
    .write      = my_write,
    .readdir    = my_readdir,
    .create     = my_create,
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &operations, NULL);
}
