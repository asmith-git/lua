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
#include <stdexcept>
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
	struct CFunctionWrapper;

	template<class R, R(*FUN)()>
	struct CFunctionWrapper<R(*)(), FUN> {
		static int wrapper(lua_State* aState) {
			R tmp = FUN();
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<class R, class P0, R(*FUN)(P0)>
	struct CFunctionWrapper<R(*)(P0), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			R tmp = FUN(p0);
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<class R, class P0, class P1, R(*FUN)(P0, P1)>
	struct CFunctionWrapper<R(*)(P0, P1), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			R tmp = FUN(p0, p1);
			push<R>(aState, tmp);
			return 1;
		}
	};

	template<class R, class P0, class P1, class P2, R(*FUN)(P0, P1, P2)>
	struct CFunctionWrapper<R(*)(P0, P1, P2), FUN> {
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
	struct CFunctionWrapper<R(*)(P0, P1, P2, P3), FUN> {
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
	struct CFunctionWrapper<R(*)(P0, P1, P2, P3, P4), FUN> {
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
	struct CFunctionWrapper<R(*)(P0, P1, P2, P3, P4, P5), FUN> {
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
	struct CFunctionWrapper<void(*)(), FUN> {
		static int wrapper(lua_State* aState) {
			FUN();
			return 0;
		}
	};

	template<class P0, void(*FUN)(P0)>
	struct CFunctionWrapper<void(*)(P0), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			FUN(p0);
			return 0;
		}
	};

	template<class P0, class P1, void(*FUN)(P0, P1)>
	struct CFunctionWrapper<void(*)(P0, P1), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			FUN(p0, p1);
			return 0;
		}
	};

	template<class P0, class P1, class P2, void(*FUN)(P0, P1, P2)>
	struct CFunctionWrapper<void(*)(P0, P1, P2), FUN> {
		static int wrapper(lua_State* aState) {
			P0 p0 = to<P0>(aState, 1);
			P1 p1 = to<P1>(aState, 2);
			P2 p2 = to<P2>(aState, 3);
			FUN(p0, p1, p2);
			return 0;
		}
	};

	template<class P0, class P1, class P2, class P3, void(*FUN)(P0, P1, P2, P3)>
	struct CFunctionWrapper<void(*)(P0, P1, P2, P3), FUN> {
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
	struct CFunctionWrapper<void(*)(P0, P1, P2, P3, P4), FUN> {
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
	struct CFunctionWrapper<void(*)(P0, P1, P2, P3, P4, P5), FUN> {
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

	// Lua function call

	template<class R, class...PARAMS>
	struct LuaFunctionWrapper;

	template<>
	struct LuaFunctionWrapper<void> {
		static void call(lua_State* aState, String aName) {
			lua_getglobal(aState, aName);
			if(lua_pcall(aState, 0, 0, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
		}
	};

	template<class P0>
	struct LuaFunctionWrapper<void, P0> {
		static void call(lua_State* aState, String aName, P0 aP0) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			if(lua_pcall(aState, 1, 0, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
		}
	};

	template<class P0, class P1>
	struct LuaFunctionWrapper<void, P0, P1> {
		static void call(lua_State* aState, String aName, P0 aP0, P1 aP1) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			if(lua_pcall(aState, 2, 0, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
		}
	};

	template<class P0, class P1, class P2>
	struct LuaFunctionWrapper<void, P0, P1, P2> {
		static void call(lua_State* aState, String aName, P0 aP0, P1 aP1, P2 aP2) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			push<P2>(aState, aP2);
			if(lua_pcall(aState, 3, 0, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
		}
	};

	template<class P0, class P1, class P2, class P3>
	struct LuaFunctionWrapper<void, P0, P1, P2, P3> {
		static void call(lua_State* aState, String aName, P0 aP0, P1 aP1, P2 aP2, P3 aP3) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			push<P2>(aState, aP2);
			push<P3>(aState, aP3);
			if(lua_pcall(aState, 4, 0, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
		}
	};

	template<class P0, class P1, class P2, class P3, class P4>
	struct LuaFunctionWrapper<void, P0, P1, P2, P3, P4> {
		static void call(lua_State* aState, String aName, P0 aP0, P1 aP1, P2 aP2, P3 aP3, P4 aP4) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			push<P2>(aState, aP2);
			push<P3>(aState, aP3);
			push<P4>(aState, aP4);
			if(lua_pcall(aState, 5, 0, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
		}
	};

	template<class P0, class P1, class P2, class P3, class P4, class P5>
	struct LuaFunctionWrapper<void, P0, P1, P2, P3, P4, P5> {
		static void call(lua_State* aState, String aName, P0 aP0, P1 aP1, P2 aP2, P3 aP3, P4 aP4, P5 aP5) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			push<P2>(aState, aP2);
			push<P3>(aState, aP3);
			push<P4>(aState, aP4);
			push<P5>(aState, aP5);
			if(lua_pcall(aState, 6, 0, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
		}
	};

	template<class R>
	struct LuaFunctionWrapper<R> {
		static R call(lua_State* aState, String aName) {
			lua_getglobal(aState, aName);
			if(lua_pcall(aState, 0, 1, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
			R tmp = to<R>(aState, -1);
			lua_pop(aState, 1);
			return tmp;
		}
	};

	template<class R, class P0>
	struct LuaFunctionWrapper<R, P0> {
		static R call(lua_State* aState, String aName, P0 aP0) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			if(lua_pcall(aState, 1, 1, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
			R tmp = to<R>(aState, -1);
			lua_pop(aState, 1);
			return tmp;
		}
	};

	template<class R, class P0, class P1>
	struct LuaFunctionWrapper<R, P0, P1> {
		static R call(lua_State* aState, String aName, P0 aP0, P1 aP1) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			if(lua_pcall(aState, 2, 1, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
			R tmp = to<R>(aState, -1);
			lua_pop(aState, 1);
			return tmp;
		}
	};

	template<class R, class P0, class P1, class P2>
	struct LuaFunctionWrapper<R, P0, P1, P2> {
		static R call(lua_State* aState, String aName, P0 aP0, P1 aP1, P2 aP2) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			push<P2>(aState, aP2);
			if(lua_pcall(aState, 3, 1, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
			R tmp = to<R>(aState, -1);
			lua_pop(aState, 1);
			return tmp;
		}
	};

	template<class R, class P0, class P1, class P2, class P3>
	struct LuaFunctionWrapper<R, P0, P1, P2, P3> {
		static R call(lua_State* aState, String aName, P0 aP0, P1 aP1, P2 aP2, P3 aP3) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			push<P2>(aState, aP2);
			push<P3>(aState, aP3);
			if(lua_pcall(aState, 4, 1, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
			R tmp = to<R>(aState, -1);
			lua_pop(aState, 1);
			return tmp;
		}
	};

	template<class R, class P0, class P1, class P2, class P3, class P4>
	struct LuaFunctionWrapper<R, P0, P1, P2, P3, P4> {
		static R call(lua_State* aState, String aName, P0 aP0, P1 aP1, P2 aP2, P3 aP3, P4 aP4) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			push<P2>(aState, aP2);
			push<P3>(aState, aP3);
			push<P4>(aState, aP4);
			if(lua_pcall(aState, 5, 1, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
			R tmp = to<R>(aState, -1);
			lua_pop(aState, 1);
			return tmp;
		}
	};

	template<class R, class P0, class P1, class P2, class P3, class P4, class P5>
	struct LuaFunctionWrapper<R, P0, P1, P2, P3, P4, P5> {
		static R call(lua_State* aState, String aName, P0 aP0, P1 aP1, P2 aP2, P3 aP3, P4 aP4, P5 aP5) {
			lua_getglobal(aState, aName);
			push<P0>(aState, aP0);
			push<P1>(aState, aP1);
			push<P2>(aState, aP2);
			push<P3>(aState, aP3);
			push<P4>(aState, aP4);
			push<P5>(aState, aP5);
			if(lua_pcall(aState, 6, 1, 0) != 0) throw std::runtime_error(lua_tostring(aState, -1));
			R tmp = to<R>(aState, -1);
			lua_pop(aState, 1);
			return tmp;
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
			typedef CFunctionWrapper<R(*)(), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, R(*FUN)(P0)>
		void push() {
			typedef CFunctionWrapper<R(*)(P0), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, R(*FUN)(P0, P1)>
		void push() {
			typedef CFunctionWrapper<R(*)(P0, P1), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, class P2, R(*FUN)(P0, P1, P2)>
		void push() {
			typedef CFunctionWrapper<R(*)(P0, P1, P2), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, class P2, class P3, R(*FUN)(P0, P1, P2, P3)>
		void push() {
			typedef CFunctionWrapper<R(*)(P0, P1, P2, P3), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, class P2, class P3, class P4, R(*FUN)(P0, P1, P2, P3, P4)>
		void push() {
			typedef CFunctionWrapper<R(*)(P0, P1, P2, P3, P4), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class P0, class P1, class P2, class P3, class P4, class P5, R(*FUN)(P0, P1, P2, P3, P4, P5)>
		void push() {
			typedef CFunctionWrapper<R(*)(P0, P1, P2, P3, P4, P5), FUN> Wrapper;
			Callback callback = Wrapper::wrapper;
			lua_pushcfunction(mState, callback);
		}

		template<class R, class...PARAMS>
		R call(String aName, PARAMS... aParams) {
			return LuaFunctionWrapper<R, PARAMS...>::call(mState, aName, aParams...);
		}
	};
}}

#endif