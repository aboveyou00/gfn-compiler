//
// pch.h
// Header for standard system include files.
//

#pragma once

#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define GTEST_HAS_TR1_TUPLE 0
#define GTEST_HAS_STD_TUPLE 1
#include "gtest/gtest.h"

#include <stdexcept>
#include <cstdint>

#include <string>
using namespace std::string_literals;
