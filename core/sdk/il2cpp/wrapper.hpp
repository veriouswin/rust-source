#pragma once

#include "LazyImporter.hpp"

bool m_strcmp(char* a, char* b) {
	if ((uintptr_t)a == 0x00000000ffffffff || (uintptr_t)b == 0x00000000ffffffff)
		return false;
	if ((uintptr_t)a == 0x000000000000007d || (uintptr_t)b == 0x000000000000007d)
		return false;

	if (!a || !b) return !a && !b;

	int ret = 0;
	unsigned char* p1 = (unsigned char*)a;
	unsigned char* p2 = (unsigned char*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	return ret == 0;
}

auto gameAssembly = GetModuleHandleA(xorstr_("GameAssembly.dll"));
auto unityPlayer = GetModuleHandleA(xorstr_("UnityPlayer.dll"));

#define ProcAddr(func) GetProcAddress(gameAssembly, func)

template<typename T, typename... Args>
inline T CallFunction(const char* func, Args... args) {
	__try {
		return reinterpret_cast<T(__fastcall*)(Args...)>(ProcAddr(func))(args...);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
namespace il2cpp {
    namespace methods {
        using il2cpp_domain_get = uintptr_t(*)();

        static auto domain_get = LI_FIND_DEF(il2cpp_domain_get);

        using il2cpp_class_get_methods = uintptr_t(*)(uintptr_t, uintptr_t*);

        static auto class_get_methods = LI_FIND_DEF(il2cpp_class_get_methods);

        using il2cpp_method_get_param_count = int (*)(uintptr_t);

        static auto method_get_param_count = LI_FIND_DEF(il2cpp_method_get_param_count);

        using il2cpp_assembly_get_image = uintptr_t(*)(uintptr_t);

        static auto assembly_get_image = LI_FIND_DEF(il2cpp_assembly_get_image);

        using il2cpp_domain_get_assemblies = uintptr_t * (*)(void* domain, uintptr_t* size);

        static auto domain_get_assemblies = LI_FIND_DEF(il2cpp_domain_get_assemblies);

        using il2cpp_object_new = uintptr_t(*)(uintptr_t);

        static auto object_new = LI_FIND_DEF(il2cpp_object_new);

        using il2cpp_class_from_name = uintptr_t(*)(uintptr_t, const char*, const char*);

        static auto class_from_name = LI_FIND_DEF(il2cpp_class_from_name);

        using il2cpp_resolve_icall = uintptr_t(*)(const char*);

        static auto resolve_icall = LI_FIND_DEF(il2cpp_resolve_icall);

        using il2cpp_field_static_get_value = uintptr_t(*)(uintptr_t, uintptr_t*);

        static auto field_static_get_value = LI_FIND_DEF(il2cpp_field_static_get_value);

        using il2cpp_class_get_fields = uintptr_t(*)(uintptr_t, uintptr_t*);

        static auto class_get_fields = LI_FIND_DEF(il2cpp_class_get_fields);

        using il2cpp_field_get_offset = uintptr_t(*)(uintptr_t);

        static auto field_get_offset = LI_FIND_DEF(il2cpp_field_get_offset);

        using il2cpp_runtime_class_init = uintptr_t(*)(uintptr_t);

        static auto runtime_class_init = LI_FIND_DEF(il2cpp_runtime_class_init);

        static auto intialize_method = GetModuleHandleA(xorstr_("GameAssembly.dll"));

        using il2cpp_string_new_wrapper = uintptr_t(*)(const char*);
        static auto new_string = LI_FIND_DEF(il2cpp_string_new_wrapper);
    }

	void init() {
        methods::intialize_method = GetModuleHandleA(xorstr_("GameAssembly.dll"));

		using il2cpp_string_new_wrapper = uintptr_t(*)(const char*);
		methods::new_string = LI_FIND_DEF(il2cpp_string_new_wrapper);

		using il2cpp_domain_get = uintptr_t(*)();

		methods::domain_get = LI_FIND_DEF(il2cpp_domain_get);

		using il2cpp_class_get_methods = uintptr_t(*)(uintptr_t, uintptr_t*);

		methods::class_get_methods = LI_FIND_DEF(il2cpp_class_get_methods);

		using il2cpp_method_get_param_count = int (*)(uintptr_t);

		methods::method_get_param_count = LI_FIND_DEF(il2cpp_method_get_param_count);

		using il2cpp_assembly_get_image = uintptr_t(*)(uintptr_t);

		methods::assembly_get_image = LI_FIND_DEF(il2cpp_assembly_get_image);

		using il2cpp_domain_get_assemblies = uintptr_t * (*)(void* domain, uintptr_t* size);

		methods::domain_get_assemblies = LI_FIND_DEF(il2cpp_domain_get_assemblies);

		using il2cpp_class_from_name = uintptr_t(*)(uintptr_t, const char*, const char*);

		methods::class_from_name = LI_FIND_DEF(il2cpp_class_from_name);

		using il2cpp_resolve_icall = uintptr_t(*)(const char*);

		methods::resolve_icall = LI_FIND_DEF(il2cpp_resolve_icall);

		using il2cpp_field_static_get_value = uintptr_t(*)(uintptr_t, uintptr_t*);

		methods::field_static_get_value = LI_FIND_DEF(il2cpp_field_static_get_value);

		using il2cpp_class_get_fields = uintptr_t(*)(uintptr_t, uintptr_t*);

		methods::class_get_fields = LI_FIND_DEF(il2cpp_class_get_fields);

		using il2cpp_field_get_offset = uintptr_t(*)(uintptr_t);

		methods::field_get_offset = LI_FIND_DEF(il2cpp_field_get_offset);

		using il2cpp_object_new = uintptr_t(*)(uintptr_t);

		methods::object_new = LI_FIND_DEF(il2cpp_object_new);

		using il2cpp_runtime_class_init = uintptr_t(*)(uintptr_t);


		methods::runtime_class_init = LI_FIND_DEF(il2cpp_runtime_class_init);

	}

	uintptr_t init_class(const char* name, const char* name_space = xorstr_("")) {

		uintptr_t domain = methods::domain_get();

		uintptr_t nrofassemblies = 0;
		uintptr_t* assemblies;
		assemblies = methods::domain_get_assemblies((void*)domain, &nrofassemblies);

		for (int i = 0; i < nrofassemblies; i++) {
			uintptr_t img = methods::assembly_get_image(assemblies[i]);

			uintptr_t kl = methods::class_from_name(img, name_space, name);
			if (!kl) continue;

			return kl;
		}
		return 0;
	}
	const uintptr_t method(const char* kl, const char* name, int argument_number = -1, char* arg_name = xorstr_(""), const char* name_space = xorstr_(""), int selected_argument = -1) {
		std::uintptr_t iter{};
		uintptr_t f{};

		auto klass = init_class(kl, name_space);


		while (f = methods::class_get_methods(klass, &iter)) {

			char* st = *reinterpret_cast<char**>(f + 0x10);
			const auto fn_name = *reinterpret_cast<const char**>(f + 0x10);

			if (m_strcmp(st, (char*)name)) {
				auto method_count = methods::method_get_param_count(iter);
				if (argument_number >= 0 && method_count != argument_number)
					continue;

				if (selected_argument >= 0 && arg_name) {
					auto args = *reinterpret_cast<std::uintptr_t*>(f + 0x28);

					if (selected_argument > method_count)
						continue;

					char* argname;

					if (method_count > 0)
						argname = *reinterpret_cast<char**>(args + (selected_argument - 1) * 0x18);
					else
						argname = (char*)("-");

					if (!argname || !m_strcmp(argname, arg_name))
						continue;
				}

				return f;
			}
		}

		return {};
	}
	//selected_argument is the argument to be checked if the name is right



	uintptr_t field(uintptr_t klass, char* field_name, bool get_offset = true) {
		uintptr_t out = 0;
		uintptr_t il2cpp_field;

		while (il2cpp_field = methods::class_get_fields(klass, &out)) {

			char* name = (char*)*reinterpret_cast<uintptr_t*>(il2cpp_field);
			if (!name)
				break;

			if (!m_strcmp(name, field_name)) {
				continue;
			}
			if (!get_offset)
				return il2cpp_field;

			uintptr_t offset = methods::field_get_offset(il2cpp_field);
			return offset;
		}
		return 0;
	}

	uintptr_t value(const char* kl, char* name, bool get_offset = true) {

		auto klass = init_class(kl);

		if (get_offset) {
			auto field_offset = field(klass, name);
			return field_offset;
		}
		else
		{
			auto _field = field(klass, name, false);

			uintptr_t ret;
			methods::field_static_get_value(_field, &ret);
			return ret;
		}
		return 0;
	}
}

namespace System {
	class Object_ {
	public:

	};
	template<typename T = void*>
	class Array {
	public:
		uint32_t ArraySize() {
			__try {
				if (!this) return 0;
				return *reinterpret_cast<uint32_t*>(this + 0x18);
			}
			__except (true) {
				std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
			}
		}
		T GetArray(int idx) {
			__try {
				if (!this) return T{};
				return *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8)));
			}
			__except (true) {
				std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
			}
		}
		void AddArray(int idx, T value) {
			__try {
				if (!this) return;
				*reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
			}
			__except (true) {
				std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
			}
		}
	};
	class String : public Object_ {
	public:
		char pad_0000[0x10];
		int len;
		wchar_t buffer[0];

		static String* Il2CPPNewString(const char* str) {
			__try {
				return CallFunction<String*, const char*>(xorstr_("il2cpp_string_new"), str);
			}
			__except (true) {
				std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
			}
		}
	};
	template<typename T = void*>
	struct List {
	public:
		char pad_0000[0x10];
		void* buffer;
		uint32_t size;

		T* get(uint32_t idx) {
			__try {
				if (!this) return nullptr;

				if (idx > this->size) return nullptr;

				void* items = this->buffer;

				if (!items) return nullptr;

				return *reinterpret_cast<T**>((uint64_t)items + (0x20 + (idx * 0x8)));
			}
			__except (true) {
				std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
			}
		}
	};
}

class Il2CppType
{
public:
	char* GetIl2CPPTypeName() {
		__try {
			return CallFunction<char*, Il2CppType*>(xorstr_("il2cpp_type_get_name"), this);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
};

class Il2CppMethod {
public:
	uint32_t paramCount() {
		__try {
			return CallFunction<uint32_t, Il2CppMethod*>(xorstr_("il2cpp_method_get_param_count"), this);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}

	Il2CppType* GetIl2CPPMethodReturnType() {
		__try {
			return CallFunction<Il2CppType*, Il2CppMethod*>(xorstr_("il2cpp_method_get_return_type"), this);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}

	Il2CppType* GetIl2CPPMethodParam(uint32_t idx) {
		__try {
			return CallFunction<Il2CppType*, Il2CppMethod*, uint32_t>(xorstr_("il2cpp_method_get_param"), this, idx);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}

	char* GetIl2CPPMethodName() {
		__try {
			return CallFunction<char*, Il2CppMethod*>(xorstr_("il2cpp_method_get_name"), this);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
};

uint64_t ResolveIl2CPPICall(const char* str) {
	__try {
		return CallFunction<uint64_t, const char*>(xorstr_("il2cpp_resolve_icall"), str);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}


uint64_t NewIl2CPPObject(uint64_t klass) {
	__try {
		return CallFunction<uint64_t, uint64_t>(xorstr_("il2cpp_object_new"), klass);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
class Il2CppField {
public:
	char* GetIl2CPPFieldName() {
		__try {
			return CallFunction<char*, Il2CppField*>(xorstr_("il2cpp_field_get_name"), this);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}

	uint32_t GetIl2CPPFieldOffset() {
		__try {
			return CallFunction<uint32_t, Il2CppField*>(xorstr_("il2cpp_field_get_offset"), this);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
};

class Il2CppClass
{
public:
	class Il2CppImage* image; //0x0000
	char pad_0008[8]; //0x0008
	char* name; //0x0010
	char* nNamespace; //0x0018
	char pad_0020[152]; //0x0020
	void* staticFields; //0x00B8

	Il2CppMethod* GetIl2CPPMethods(void* iter) {
		__try {
			return CallFunction<Il2CppMethod*, Il2CppClass*, void*>(xorstr_("il2cpp_class_get_methods"), this, iter);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}

	Il2CppField* GetIl2CPPFields(void* iter) {
		__try {
			return CallFunction<Il2CppField*, Il2CppClass*, void*>(xorstr_("il2cpp_class_get_fields"), this, iter);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
}; //Size: 0x00C0

class Il2CppImage
{
public:
	char* assemblyName; //0x0000
	char* name; //0x0008

	uint64_t ClassCount() {
		__try {
			return CallFunction<uint64_t, Il2CppImage*>(xorstr_("il2cpp_image_get_class_count"), this);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}

	Il2CppClass* GetIl2CPPClass(uint64_t idx) {
		__try {
			return CallFunction<Il2CppClass*, Il2CppImage*, uint64_t>(xorstr_("il2cpp_image_get_class"), this, idx);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
}; //Size: 0x0010
template<typename T = System::Object_>
System::Array<T*>* NewIl2CPPArray(Il2CppClass* klazz, uint64_t length) {
	__try {
		auto ret = CallFunction<System::Array<T*>*, Il2CppClass*, uint64_t>(xorstr_("il2cpp_array_new"), klazz, length);
		return ret;
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}

class Il2CppAssembly {
public:
	uint64_t buffer;
};

class Il2CppDomain {
public:
	size_t AssemblyCount() {
		__try {
			size_t size = 0;
			auto assemblies = CallFunction<Il2CppAssembly**, Il2CppDomain*, void*>(xorstr_("il2cpp_domain_get_assemblies"), this, &size);

			return size;
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}

	Il2CppAssembly** GetAssemblies() {
		__try {
			size_t size = 0;

			return CallFunction<Il2CppAssembly**, Il2CppDomain*, void*>(xorstr_("il2cpp_domain_get_assemblies"), this, &size);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
};

Il2CppDomain* GetIl2CPPDomain() {
	__try {
		return CallFunction<Il2CppDomain*>(xorstr_("il2cpp_domain_get"));
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}

void* Il2CPPRuntimeInvoke(void* method_ptr, void* obj, void** param, void** exc) {
	__try {
		return CallFunction<void*, void*, void*, void**, void**>("il2cpp_runtime_invoke", method_ptr, obj, param, exc);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}

void* GetVirtualIl2CPPObjectMethod(void* obj, void* method) {
	__try {
		return CallFunction<void*, void*, void*>("il2cpp_object_get_virtual_method", obj, method);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}