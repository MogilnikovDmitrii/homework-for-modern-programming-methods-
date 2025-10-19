#pragma once
#include <map>
#include <functional>
#include <string>

void Commands(std::map<std::string, std::function<void()>>& commands);