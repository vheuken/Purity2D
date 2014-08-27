#ifndef PURITY_CONFIGURATION_H
#define PURITY_CONFIGURATION_H

#include <memory>
#include <string>
#include <INIReader.h>

namespace Purity
{
    const std::string DEFAULT_CONFIG_FILE = "config.ini";

    class Configuration
    {
    public:
        static Configuration* getInstance();

        std::string getString(std::string section, std::string name, std::string defaultValue);
        bool getBool(std::string section, std::string name, bool defaultValue);
        double getReal(std::string section, std::string name, double defaultValue);
        int getInteger(std::string section, std::string name, int defaultValue);

    private:
        Configuration();

        std::unique_ptr<INIReader> mConfigFile;
    };
}

#endif // PURITY_CONFIGURATION_H
