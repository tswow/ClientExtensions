#pragma once

#include "ClientMacros.h"
#include "lua.hpp"

#include <string>

namespace ClientLua {
	int AddFunction(char const* fnName, lua_CFunction fn, std::string const& file, size_t line);

	lua_State* State();
	// Registers lua that will fire on reload
	void RegisterLua(std::string const& lua);
	CLIENT_FUNC(DoString, 0x00819210, void, (char const* code, lua_State* L))
	CLIENT_FUNC(GetTop, 0x0084DBD0, int, (lua_State* L))

	CLIENT_FUNC(IsString, 0x0084DF60, uint32_t, (lua_State* L, int32_t))
	CLIENT_FUNC(IsNumber, 0x0084DF20, int32_t, (lua_State* L, int32_t))

	std::string GetString(lua_State* L, int32_t offset, std::string const& defValue = "");
	double GetNumber(lua_State* L, int32_t offset, double defValue = 0);
}

#define CLIENT_LUA(name) \
	int name##Fn(lua_State * L);\
	int name##Dummy = ClientLua::AddFunction(#name,name##Fn,__FILE__,__LINE__);\
	int name##Fn(lua_State * L)