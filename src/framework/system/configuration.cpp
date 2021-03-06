#include "configuration.h"

Purity::Configuration::Configuration()
{
    mConfigFile = std::unique_ptr<INIReader>(new INIReader("config.ini"));
}

Purity::Configuration* Purity::Configuration::getInstance()
{
    static Configuration instance;
    return &instance;
}

std::string
Purity::Configuration::getString(std::string section, std::string name, std::string defaultValue)
{
    return mConfigFile->Get(section, name, defaultValue);
}

bool Purity::Configuration::getBool(std::string section, std::string name, bool defaultValue)
{
    return mConfigFile->GetBoolean(section, name, defaultValue);
}

double Purity::Configuration::getReal(std::string section, std::string name, double defaultValue)
{
    return mConfigFile->GetReal(section, name, defaultValue);
}

int Purity::Configuration::getInteger(std::string section, std::string name, int defaultValue)
{
    return mConfigFile->GetInteger(section, name, defaultValue);
}
