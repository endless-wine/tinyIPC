#include "file_ex.h"
#include "directory_ex.h"
#include "utils_log.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <securec.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

const int MAX_FILE_LENGTH = 32 * 1024 * 1024;

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

namespace Endless {

bool LoadStringFromFile(const string &filePath, string &content)
{
    ifstream file(filePath.c_str());
    if (!file.is_open()) {
        UTILS_LOGD("open file failed! filePath:%{public}s", filePath.c_str());
        return false;
    }

    file.seekg(0, ios::end);
    const long fileLength = file.tellg();
    if (fileLength > MAX_FILE_LENGTH) {
        UTILS_LOGD("invalid file length(%{public}ld)!", fileLength);
        return false;
    }

    content.clear();
    file.seekg(0, ios::beg);
    copy(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), back_inserter(content));
    return true;
}

string GetFileNameByFd(const int fd)
{
    if (fd <= 0) {
        return string();
    }

    string fdPath = "/proc/self/fd/" + std::to_string(fd);
    char fileName[PATH_MAX + 1] = {0};

    int ret = readlink(fdPath.c_str(), fileName, PATH_MAX);
    if (ret < 0 || ret > PATH_MAX) {
        UTILS_LOGD("Get fileName failed, ret is: %{public}d!", ret);
        return string();
    }
    fileName[ret] = '\0';
    return string(fileName);
}

bool LoadStringFromFdToFile(int fd, string &content)
{
    string fileName = GetFileNameByFd(fd);
    if (fileName.empty()) {
        UTILS_LOGD("LoadStringFromFd get file name by fd failed!");
        return false;
    }

    if (!LoadStringFromFile(fileName, content)) {
        UTILS_LOGE("LoadStringFromFd get string from file failed!");
        return false;
    }
    return true;
}

bool LoadStringFromFd(int fd, string &content)
{
    if (fd <= 0) {
        UTILS_LOGD("invalid fd:%{public}d", fd);
        return false;
    }

    const long fileLength = lseek(fd, 0, SEEK_END);
    if (fileLength > MAX_FILE_LENGTH) {
        UTILS_LOGE("invalid file length(%{public}ld)!", fileLength);
        return false;
    }

    // lseek is not support the linux file node
    if (fileLength < 0) {
        return LoadStringFromFdToFile(fd, content);
    }

    if (fileLength == 0) {
        return true;
    }

    content.resize(fileLength);
    int loc = lseek(fd, 0, SEEK_SET);
    if (loc == -1) {
        UTILS_LOGE("lseek file to begin failed!");
        return false;
    }

    const long len = read(fd, (void *)content.data(), fileLength);
    if (len != fileLength) {
        UTILS_LOGE("the length read from file is not equal to fileLength!len:%{public}ld,fileLen:%{public}ld", len,
                   fileLength);
        return false;
    }

    return true;
}

bool SaveStringToFile(const std::string &filePath, const std::string &content, bool truncated /*= true*/)
{
    if (content.empty()) {
        UTILS_LOGI("content is empty, no need to save!");
        return true;
    }

    ofstream file;
    if (truncated) {
        file.open(filePath.c_str(), ios::out | ios::trunc);
    } else {
        file.open(filePath.c_str(), ios::out | ios::app);
    }

    if (!file.is_open()) {
        UTILS_LOGD("open file failed! filePath:%{private}s", filePath.c_str());
        return false;
    }

    file.write(content.c_str(), content.length());
    if (file.fail()) {
        UTILS_LOGE("write content to file failed!file:%{private}s, content:%{private}s", filePath.c_str(),
                   content.c_str());
        return false;
    }
    return true;
}

bool SaveStringToFd(int fd, const std::string &content)
{
    if (fd <= 0) {
        UTILS_LOGD("invalid fd:%{public}d", fd);
        return false;
    }

    if (content.empty()) {
        UTILS_LOGI("content is empty, no need to save!");
        return true;
    }

    const long len = write(fd, content.c_str(), content.length());
    if (len < 0) {
        UTILS_LOGE("write file failed!errno:%{public}d, err:%{public}s", errno, strerror(errno));
        return false;
    }

    if (static_cast<unsigned long>(len) != content.length()) {
        UTILS_LOGE("the length write to file is not equal to fileLength!len:%{public}ld, fileLen:%{public}zu", len,
                   content.length());
        return false;
    }

    return true;
}

bool LoadBufferFromNodeFile(const string &filePath, vector<char> &content)
{
    string realPath;
    if (!PathToRealPath(filePath, realPath)) {
        UTILS_LOGD("filePath to realPath failed! filePath:%{private}s", filePath.c_str());
        return false;
    }

    FILE *fp = fopen(realPath.c_str(), "r");
    if (fp == nullptr) {
        UTILS_LOGD("open file failed! filePath:%{private}s", realPath.c_str());
        return false;
    }

    char ch = fgetc(fp);
    int byteCount = 1;
    while (!feof(fp)) {
        if (byteCount > MAX_FILE_LENGTH) {
            UTILS_LOGE("LoadBufferFromNodeFile invalid file length(%{public}d)!", byteCount);
            fclose(fp);
            fp = nullptr;
            content.clear();
            return false;
        }

        content.push_back(ch);
        ch = fgetc(fp);
        byteCount++;
    }

    fclose(fp);
    fp = nullptr;
    return true;
}

/* load file to buffer. If the buffer is not empty,then overwrite */
bool LoadBufferFromFile(const string &filePath, vector<char> &content)
{
    ifstream file;
    file.open(filePath.c_str(), ios::in | ios::binary);
    if (!file.is_open()) {
        UTILS_LOGD("open file failed! filePath:%{private}s", filePath.c_str());
        return false;
    }

    file.seekg(0, std::ios::end);
    const long fileLength = file.tellg();
    if (fileLength > MAX_FILE_LENGTH) {
        UTILS_LOGD("invalid file length(%{public}ld)!", fileLength);
        return false;
    }

    // lseek is not support the linux file node
    if (fileLength < 0) {
        return LoadBufferFromNodeFile(filePath, content);
    }

    if (fileLength == 0) {
        content.clear();
        return true;
    }

    file.seekg(0, std::ios::beg);
    if (file.fail()) {
        UTILS_LOGE("seekg file to begin failed!filePath:%{private}s", filePath.c_str());
        return false;
    }

    content.resize(fileLength);
    file.read(&content[0], fileLength);
    return true;
}

bool SaveBufferToFile(const string &filePath, const vector<char> &content, bool truncated /*= true*/)
{
    if (content.empty()) {
        UTILS_LOGI("content is empty, no need to save!");
        return true;
    }

    ofstream file;
    if (truncated) {
        file.open(filePath.c_str(), ios::out | ios::binary | ios::trunc);
    } else {
        file.open(filePath.c_str(), ios::out | ios::binary | ios::app);
    }
    if (!file.is_open()) {
        UTILS_LOGD("open file failed! filePath:%{private}s, mode:%{private}d", filePath.c_str(), mode);
        return false;
    }

    file.write(&content[0], content.size());
    return true;
}

bool FileExists(const string &fileName)
{
    return (access(fileName.c_str(), F_OK) == 0);
}

bool StringExistsInFile(const string &fileName, const string &subStr, bool caseSensitive /*= true*/)
{
    if (subStr.empty()) {
        UTILS_LOGD("String is empty");
        return false;
    }

    string str;
    if (!LoadStringFromFile(fileName, str)) {
        UTILS_LOGD("File load fail, filePath:%{private}s", fileName.c_str());
        return false;
    }

    if (caseSensitive) {
        return (str.find(subStr) != string::npos);
    }

    string strlower(str);
    string sublower(subStr);
    transform(str.begin(), str.end(), strlower.begin(), ::tolower);
    transform(subStr.begin(), subStr.end(), sublower.begin(), ::tolower);
    return (strlower.find(sublower) != string::npos);
}

int CountStrInStr(const string &str, const string &subStr)
{
    if (subStr.empty()) {
        UTILS_LOGD("subStr is empty");
        return 0;
    }

    size_t position = 0;
    int count = 0;
    size_t length = subStr.length();
    while ((position = str.find(subStr, position)) != string::npos) {
        position += length;
        count++;
    }

    return count;
}

int CountStrInFile(const string &fileName, const string &subStr, bool caseSensitive /*= true*/)
{
    if (subStr.empty()) {
        UTILS_LOGD("String is empty");
        return -1;
    }

    string str;
    if (!LoadStringFromFile(fileName, str)) {
        UTILS_LOGD("File load fail, filePath:%{private}s", fileName.c_str());
        return -1;
    }

    // If case-insensitive, strings are converted to lowercase.
    if (caseSensitive) {
        return CountStrInStr(str, subStr);
    }

    string strlower(str);
    string sublower(subStr);
    transform(str.begin(), str.end(), strlower.begin(), ::tolower);
    transform(subStr.begin(), subStr.end(), sublower.begin(), ::tolower);
    return CountStrInStr(strlower, sublower);
}
} // namespace Endless
