#pragma once
#include <map>
#include <functional>
#include <string>

void setupCommands(std::map<std::string, std::function<void()>>& commands);
