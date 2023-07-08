#if !defined(nekrs_ioutils_hpp_)
#define nekrs_ioutils_hpp_

#include "nrs.hpp"
#include <filesystem>
namespace fs = std::filesystem;

void fileSync(const char *file);
void copyFile(const char *srcName, const char* destName);
bool isFileEmpty(const char *file);
bool isFileNewer(const char *file1, const char* file2);
bool fileExists(const char *file);
void fileBcast(const std::filesystem::path &srcPath, const std::filesystem::path &dstPath,
               MPI_Comm comm, int verbose);

#endif
