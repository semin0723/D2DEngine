#pragma once

#include <cassert>
#include "STL.h"

using TypeId = size_t;
using ObjectId = size_t;

using ULL = unsigned long long;

static const ObjectId	INVALID_OBJECT_ID = (std::numeric_limits<ObjectId>::max)();
static const TypeId		INVALID_TYPE_ID = (std::numeric_limits<TypeId>::max)();