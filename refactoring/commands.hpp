#pragma once

#include <functional>
#include <map>
#include <string>

void initializeCommands(std::map<std::string, std::function<void()>>& commands);