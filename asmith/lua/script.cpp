//	Copyright 2017 Adam Smith
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
// 
//	http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.

#include "asmith/lua/script.hpp"
#include <stdexcept>

namespace asmith { namespace Lua {
	// Script

	Script::Script(State& aState) :
		mState(aState),
		mLoaded(false)
	{}

	Script::~Script() {

	}

	void Script::load(const char* aScript) {
		lua_State* const state = mState.getHandle();
		int error = luaL_loadbuffer(state, aScript, strlen(aScript), "line");
		if(error) {
			const std::string errorMsg = lua_tostring(state, -1);
			lua_pop(state, 1);
			throw std::runtime_error("asmith::Lua::Script::load : " + errorMsg);
		}
		mLoaded = true;
	}

	void Script::operator()() {
		if(! mLoaded) throw std::runtime_error("asmith::Lua::Script::load : Error loading script"); 
		lua_State* const state = mState.getHandle();
		int error = lua_pcall(state, 0, 0, 0);
		if(error) {
			const std::string errorMsg = lua_tostring(state, -1);
			lua_pop(state, 1);
			throw std::runtime_error("asmith::Lua::Script::operator() : " + errorMsg);
		}
	}

}}