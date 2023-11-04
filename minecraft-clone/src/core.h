#pragma once

#include <chrono>
#include <iostream>
#include <gtx/string_cast.hpp>

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
#define LOG(x) std::cout << x << "\n"

#define TIMEPOINT std::chrono::steady_clock::time_point	
#define NOW std::chrono::steady_clock::now
#define MS std::chrono::duration_cast<std::chrono::milliseconds>
#define US std::chrono::duration_cast<std::chrono::microseconds>