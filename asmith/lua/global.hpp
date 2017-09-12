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

#ifndef ASMITH_LUA_GLOBAL_HPP
#define ASMITH_LUA_GLOBAL_HPP

#include "state.hpp"

namespace asmith { namespace Lua {

	class Variable : public Object {
	public:
		virtual ~Variable() {}
		virtual Type getType() const = 0;
	};

	template<class T>
	class Global : public Variable {
	private:
		const std::string mName;
		State& mState;

		Global(const Global&) = delete;
		Global(Global&&) = delete;
		Global& operator=(const Global&) = delete;
		Global& operator=(Global&&) = delete;
	public:
		Global(State& aState, String aName) :
			mName(aName),
			mState(aState)
		{}

		operator T() const {
			lua_State* state = mState.getHandle();
			lua_getglobal(state, mName.c_str());
			T tmp = implementation::to<T>(state, -1);
			lua_pop(state, 1);
			return tmp;
		}

		Global<T>& operator=(T aValue) {
			lua_State* state = mState.getHandle();
			implementation::push<T>(state, aValue);
			lua_setglobal(state, mName.c_str());
			return *this;
		}

		// Inherited from Variable

		State& getState() const override {
			return mState;
		}

		Type getType() const override {
			return typeOf<T>();
		}
	};

	typedef Global<Boolean> GlobalBoolean;
	typedef Global<Integer> GlobalInteger;
	typedef Global<Number> GlobalNumber;
	typedef Global<String> GlobalString;
}}

#endif