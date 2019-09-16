#include "M_Config.hpp"

JsonConfig::CVConfig::CVConfig()
{
    if (access(cvConfigName.c_str(), F_OK) != -1)
    {
        if (access(cvConfigName.c_str(), R_OK) != -1)
        {
            std::cout << "\033[33m[SensorsConfig] config file found , reading ........\033[0m\n";
			Base::ConfigSetter::ReadConfig(cvConfigName, dataTmp);
        }
        else
        {
            std::cout << "\033[31m[SensorsConfig] config file false , please check user func\033[0m\n";
        }
    }
    else
    {
        std::cout << "\033[33m[SensorsConfig] config file no found , will create a example\033[0m\n";
		Base::ConfigSetter::CreateConfig(cvConfigName, cvExample.dump(4));
    }
}
