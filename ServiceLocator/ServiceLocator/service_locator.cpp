#include "service_locator.h"

std::unordered_map<std::string, std::shared_ptr<IService>> ServiceLocator::map;