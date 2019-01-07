
#include "Utility.hpp"
#include <whereami.h>

namespace jet
{
    std::string getExecutablePath()
    {
        std::string pathString;
        auto pathLength = static_cast<size_t>(wai_getExecutablePath(nullptr, 0, nullptr));
        pathString.resize(pathLength);
        wai_getExecutablePath(const_cast<char*>(pathString.data()), static_cast<int>(pathLength), nullptr);
        return pathString;
    }
}
