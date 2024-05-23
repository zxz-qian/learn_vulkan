#include "vector"
#include <string>

class FileUtils
{
private:
    /* data */
public:
    static std::vector<char> ReadFile(const std::string &filepath);
};
