#ifndef CRTFOR
#define CRTFOR
#include <map>
#include <set>
#include <utility>
std::pair<std::pair<std::set<int>, std::set<int>>, std::map<int, std::set<int>>>
create_forest(std::map<int, std::set<int>>, int);
#endif
