#pragma once

#include <cassert>

using TypeId = size_t;
using ObjectId = size_t;

static const ObjectId	INVALID_OBJECT_ID = std::numeric_limits<ObjectId>::max();
static const TypeId		INVALID_TYPE_ID = std::numeric_limits<TypeId>::max();