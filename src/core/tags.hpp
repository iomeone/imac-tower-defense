#pragma once

#include <entt/entt.hpp>

#define TAG(__name__) using __name__ = entt::label<#__name__ ## _hs>
#pragma warning(push)
#pragma warning(disable: 4307) // EnTT throws a warning with the hashing in VS2017

namespace renderTag
{
    TAG(Animated);
    TAG(Still);
};

