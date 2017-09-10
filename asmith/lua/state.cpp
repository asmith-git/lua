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

#include "asmith/lua/state.hpp"
#include <stdexcept>

namespace asmith { namespace Lua {
	// State

	State::State() :
		mState(luaL_newstate())
	{
		if(! mState) throw std::runtime_error("asmith::Lua::State : Failed to create Lua state");
	}

	State::~State() {
		if(! mState) lua_close(mState);
	}

	lua_State* State::getHandle() throw() {
		return mState;
	}


}}