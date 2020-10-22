#pragma once

#define BIND(fn) std::bind(&fn, this, std::placeholders::_1)