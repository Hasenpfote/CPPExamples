#include "service_locator.h"

#ifndef ENABLE_TYPE_TEST
std::unordered_map<std::string, std::shared_ptr<IService>> ServiceLocator::map;
#else
std::unordered_map<std::string, std::shared_ptr<void>> ServiceLocator::map;
#endif