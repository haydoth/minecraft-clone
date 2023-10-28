#pragma once

#include <iostream>

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
#define LOG(x) std::cout << x << "\n"