#ifndef UTIL_H
#define UTIL_H

// #include <ostream>
#include <string>
#include <fstream>
#include <ctime>

enum direction {N, S, E, W, NW, NE, SW, SE};
enum brains {BrainUser, BrainRandom, BrainHeuristicOnly};
void log_error(std::string, std::string);

#endif
