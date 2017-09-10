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

#ifndef ASMITH_LUA_SCRIPT_HPP
#define ASMITH_LUA_SCRIPT_HPP

#include "state.hpp"

namespace asmith { namespace Lua {
	class Script {
	private:
		State& mState;
		bool mLoaded;

		Script(const Script&) = delete;
		Script(Script&&) = delete;
		Script& operator=(const Script&) = delete;
		Script& operator=(Script&&) = delete;
	public:
		Script(State&);
		~Script();

		void load(const char*);
		void operator()();
	};
}}

#endif