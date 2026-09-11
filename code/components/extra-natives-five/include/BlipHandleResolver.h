#pragma once

#include <cstdint>
#include <cstring>

namespace blip_names
{
// GTA Legacy handles contain a 16-bit pool index and a 16-bit generation.
// The pool stores pointers; the generation is at offset 8 in a radar blip.
// Layout reference: ScriptHookVDotNet NativeMemory.GetBlipAddress (zlib).
inline void* Resolve(void* const* pool, int count, uint32_t handle)
{
	if (!pool || count <= 0 || count > 65536 || handle == 0)
	{
		return nullptr;
	}

	const uint32_t index = handle & 0xFFFF;
	if (index >= static_cast<uint32_t>(count) || !pool[index])
	{
		return nullptr;
	}

	uint16_t generation;
	std::memcpy(&generation, static_cast<const uint8_t*>(pool[index]) + 8, sizeof(generation));
	return generation == (handle >> 16) ? pool[index] : nullptr;
}
}
