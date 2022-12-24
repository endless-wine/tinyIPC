#ifndef UTILS_BASE_FILE_EX_H
#define UTILS_BASE_FILE_EX_H

#include <string>
#include <vector>

namespace Endless {

bool LoadStringFromFile(const std::string &filePath, std::string &content);
bool SaveStringToFile(const std::string &filePath, const std::string &content, bool truncated = true);
bool LoadStringFromFd(int fd, std::string &content);
bool SaveStringToFd(int fd, const std::string &content);
bool LoadBufferFromFile(const std::string &filePath, std::vector<char> &content);
bool SaveBufferToFile(const std::string &filePath, const std::vector<char> &content, bool truncated = true);
bool FileExists(const std::string &fileName);
bool StringExistsInFile(const std::string &fileName, const std::string &subStr, bool caseSensitive = true);
int CountStrInFile(const std::string &fileName, const std::string &subStr, bool caseSensitive = true);

} // namespace Endless

#endif
