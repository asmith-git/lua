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

#ifndef ASMITH_LUA_STATE_HPP
#define ASMITH_LUA_STATE_HPP

#include <cstdint>
#include "lua/lua.hpp"

namespace asmith { namespace Lua {

	typedef void Nil;
	typedef bool Boolean;
	typedef int64_t Integer;
	typedef double Number;
	typedef const char* String;
	typedef int(*Callback)(lua_State*);

	// lua_pushX
	template<class T>
	static void push(lua_State* aState, T aValue);

	template<>
	static void push<Boolean>(lua_State* aState, Boolean aValue) {
		lua_pushboolean(aState, aValue);
	}

	template<>
	static void push<uint8_t>(lua_State* aState, uint8_t aValue) {
		lua_pushnumber(aState, aValue);
	}

	template<>
	static void push<uint16_t>(lua_State* aState, uint16_t aValue) {
		lua_pushnumber(aState, aValue);
	}

	template<>
	static void push<uint32_t>(lua_State* aState, uint32_t aValue) {
		lua_pushnumber(aState, aValue);
	}

	template<>
	static void push<uint64_t>(lua_State* aState, uint64_t aValue) {
		lua_pushnumber(aState, (Number) aValue);
	}

	template<>
	static void push<int8_t>(lua_State* aState, int8_t aValue) {
		lua_pushnumber(aState, aValue);
	}

	template<>
	static void push<int16_t>(lua_State* aState, int16_t aValue) {
		lua_pushnumber(aState, aValue);
	}

	template<>
	static void push<int32_t>(lua_State* aState, int32_t aValue) {
		lua_pushnumber(aState, aValue);
	}

	template<>
	static void push<int64_t>(lua_State* aState, int64_t aValue) {
		lua_pushnumber(aState, (Number) aValue);
	}

	template<>
	static void push<float>(lua_State* aState, float aValue) {
		lua_pushnumber(aState, aValue);
	}

	template<>
	static void push<double>(lua_State* aState, double aValue) {
		lua_pushnumber(aState, aValue);
	}

	template<>
	static void push<String>(lua_State* aState, String aValue) {
		lua_pushstring(aState, aValue);
	}

	// lua_toX

	template<class T>
	static T to(lua_State* aState, int aIndex);

	template<>
	static Boolean to<Boolean>(lua_State* aState, int aIndex) {
		return lua_toboolean(aState, aIndex);
	}

	template<>
	static uint8_t to<uint8_t>(lua_State* aState, int aIndex) {
		return (uint8_t) lua_tonumber(aState, aIndex);
	}

	template<>
	static uint16_t to<uint16_t>(lua_State* aState, int aIndex) {
		return (uint16_t) lua_tonumber(aState, aIndex);
	}

	template<>
	static uint32_t to<uint32_t>(lua_State* aState, int aIndex) {
		return (uint32_t) lua_tonumber(aState, aIndex);
	}

	template<>
	static uint64_t to<uint64_t>(lua_State* aState, int aIndex) {
		return (uint64_t) lua_tonumber(aState, aIndex);
	}

	template<>
	static int8_t to<int8_t>(lua_State* aState, int aIndex) {
		return (int8_t)lua_tonumber(aState, aIndex);
	}

	template<>
	static int16_t to<int16_t>(lua_State* aState, int aIndex) {
		return (int16_t)lua_tonumber(aState, aIndex);
	}

	template<>
	static int32_t to<int32_t>(lua_State* aState, int aIndex) {
		return (int32_t)lua_tonumber(aState, aIndex);
	}

	template<>
	static int64_t to<int64_t>(lua_State* aState, int aIndex) {
		return (int64_t)lua_tonumber(aState, aIndex);
	}

	template<>
	static float to<float>(lua_State* aState, int aIndex) {
		return (float) lua_tonumber(aState, aIndex);
	}

	template<>
	static double to<double>(lua_State* aState, int aIndex) {
		return lua_tonumber(aState, aIndex);
	}

	template<>
	static String to<String>(lua_State* aState, int aIndex) {
		return lua_tostring(aState, aIndex);
	}

	// Function Wrapper

	template<class F, F FUN>
	struct FunctionWrapper;

	template<class R, R(*FUN)()>
	struct FunctionWrapper<R(*)(), FUN> {
		static int wrapper(lua_State* aState) {
			R tmp = FUN();
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<class R, class P0, R(*FUN)(P0)>
	struct FunctionWrapper<R(*)(P0), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			R tmp = FUN(p0);
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<class R, class P0, class P1, R(*FUN)(P0, P1)>
	struct FunctionWrapper<R(*)(P0, P1), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			R tmp = FUN(p0, p1);
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<class R, class P0, class P1, class P2, R(*FUN)(P0, P1, P2)>
	struct FunctionWrapper<R(*)(P0, P1, P2), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			P2 p2 = to<P2>(aState, 3);
			R tmp = FUN(p0, p1, p2);
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<class R, class P0, class P1, class P2, class P3, R(*FUN)(P0, P1, P2, P3)>
	struct FunctionWrapper<R(*)(P0, P1, P2, P3), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			P2 p2 = to<P2>(aState, 3);
			P3 p3 = to<P3>(aState, 4);
			R tmp = FUN(p0, p1, p2, p3);
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<class R, class P0, class P1, class P2, class P3, class P4, R(*FUN)(P0, P1, P2, P3, P4)>
	struct FunctionWrapper<R(*)(P0, P1, P2, P3, P4), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			P2 p2 = to<P2>(aState, 3);
			P3 p3 = to<P3>(aState, 4);
			P4 p4 = to<P4>(aState, 4);
			R tmp = FUN(p0, p1, p2, p3, p4);
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<class R, class P0, class P1, class P2, class P3, class P4, class P5, R(*FUN)(P0, P1, P2, P3, P4, P5)>
	struct FunctionWrapper<R(*)(P0, P1, P2, P3, P4, P5), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			P2 p2 = to<P2>(aState, 3);
			P3 p3 = to<P3>(aState, 4);
			P4 p4 = to<P4>(aState, 4);
			P5 p5 = to<P5>(aState, 5);
			R tmp = FUN(p0, p1, p2, p3, p4, p5);
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<void(*FUN)()>
	struct FunctionWrapper<void(*)(), FUN> {
		static int wrapper(lua_State* aState) {
			FUN();
			return 0;
		}
	};

	template<class P0, void(*FUN)(P0)>
	struct FunctionWrapper<void(*)(P0), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			FUN(p0);
			return 0;
		}
	};

	template<class P0, class P1, void(*FUN)(P0, P1)>
	struct FunctionWrapper<void(*)(P0, P1), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			FUN(p0, p1);
			return 0;
		}
	};

	template<class P0, class P1, class P2, void(*FUN)(P0, P1, P2)>
	struct FunctionWrapper<void(*)(P0, P1, P2), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			P2 p2 = to<P2>(aState, 3);
			FUN(p0, p1, p2);
			return 0;
		}
	};

	template<class P0, class P1, class P2, class P3, void(*FUN)(P0, P1, P2, P3)>
	struct FunctionWrapper<void(*)(P0, P1, P2, P3), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			P2 p2 = to<P2>(aState, 3);
			P3 p3 = to<P3>(aState, 4);
			FUN(p0, p1, p2, p3);
			return 0;
		}
	};

	template<class P0, class P1, class P2, class P3, class P4, void(*FUN)(P0, P1, P2, P3, P4)>
	struct FunctionWrapper<void(*)(P0, P1, P2, P3, P4), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			P2 p2 = to<P2>(aState, 3);
			P3 p3 = to<P3>(aState, 4);
			P4 p4 = to<P4>(aState, 4);
			FUN(p0, p1, p2, p3, p4);
			return 0;
		}
	};

	template<class P0, class P1, class P2, class P3, class P4, class P5, void(*FUN)(P0, P1, P2, P3, P4, P5)>
	struct FunctionWrapper<void(*)(P0, P1, P2, P3, P4, P5), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			P2 p2 = to<P2>(aState, 3);
			P3 p3 = to<P3>(aState, 4);
			P4 p4 = to<P4>(aState, 4);
			P5 p5 = to<P5>(aState, 5);
			FUN(p0, p1, p2, p3, p4, p5);
			return 0;
		}
	};

	// State class

	class State {
	private:
		lua_State* const mState;

		State(const State&) = delete;
		State(State&&) = delete;
		State& operator=(const State&) = delete;
		State& operator=(State&&) = delete;
	public:
		State();
		~State();

		void setGlobal(String);
		lua_State* getHandle() throw();

		template<class T>
		void push(T aValue) {
			asmith::Lua::push<T>(mState, aValue);
		}

		template<class R, void(*FUN)()>
		void push() {
			typedef FunctionWrapper<R(*)(), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, R(*FUN)(P0)>
		void push() {
			typedef FunctionWrapper<R(*)(P0), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, R(*FUN)(P0, P1)>
		void push() {
			typedef FunctionWrapper<R(*)(P0, P1), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, class P2, R(*FUN)(P0, P1, P2)>
		void push() {
			typedef FunctionWrapper<R(*)(P0, P1, P2), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, class P2, class P3, R(*FUN)(P0, P1, P2, P3)>
		void push() {
			typedef FunctionWrapper<R(*)(P0, P1, P2, P3), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, class P2, class P3, class P4, R(*FUN)(P0, P1, P2, P3, P4)>
		void push() {
			typedef FunctionWrapper<R(*)(P0, P1, P2, P3, P4), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, class P2, class P3, class P4, class P5, R(*FUN)(P0, P1, P2, P3, P4, P5)>
		void push() {
			typedef FunctionWrapper<R(*)(P0, P1, P2, P3, P4, P5), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}
	};
}}

#endif