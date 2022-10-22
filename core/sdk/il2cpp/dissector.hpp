#pragma once

template<typename T1, typename T2>
bool MapContainsKey(T1 map, T2 key) {
	return map.count(key) > 0;
}

class default_t
{
public:
	template<typename T>
	operator T() const { return T(); }
};
default_t const defaultt = default_t();
#define NP(type) type nonptr = defaultt; if(!this) return nonptr;

static std::map<uint32_t, uint64_t> offsets = std::map<uint32_t, uint64_t>();

Il2CppClass* GetClasses(uint32_t path) {
	if (MapContainsKey(offsets, path))
		return reinterpret_cast<Il2CppClass*>(offsets[path]);

	Il2CppDomain* domain = GetIl2CPPDomain();
	Il2CppAssembly** assemblies = domain->GetAssemblies();

	for (int i = 0; i < domain->AssemblyCount(); i++) {
		Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
		for (int c = 0; c < image->ClassCount(); c++) {
			std::string temp(image->assemblyName);
			temp.erase(temp.find(xorstr_(".dll")), 4);

			Il2CppClass* klass = image->GetIl2CPPClass(c);
			char* name = klass->name;
			char* ns = klass->nNamespace;
			if (std::string(ns).empty())
				temp = temp + xorstr_("::") + name;
			else
				temp = temp + xorstr_("::") + ns + xorstr_("::") + name;

			if (path == RUNTIME_CRC32(temp.c_str())) {
				uint64_t ptr = std::uint64_t(klass);

				offsets.insert(std::make_pair(path, ptr));
				return klass;
			}
		}
	}
}


Il2CppClass* GetClass(uint32_t path) {
	__try {
		return GetClasses(path);
	}
	__except (true)
	{
		printf("Exception caused at %s", __FUNCTION__);
	}
}


uint64_t CallFieldOffsetNebelPaster(uint32_t path) {
	if (MapContainsKey(offsets, path))
		return std::uint32_t(offsets[path]);

	Il2CppDomain* domain = GetIl2CPPDomain();
	Il2CppAssembly** assemblies = domain->GetAssemblies();

	for (int i = 0; i < domain->AssemblyCount(); i++) {
		Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
		for (int c = 0; c < image->ClassCount(); c++) {
			std::string temp(image->assemblyName);
			temp.erase(temp.find(xorstr_(".dll")), 4);

			Il2CppClass* klass = image->GetIl2CPPClass(c);
			char* name = klass->name;
			char* ns = klass->nNamespace;
			if (std::string(ns).empty())
				temp = temp + xorstr_("::") + name;
			else
				temp = temp + xorstr_("::") + ns + xorstr_("::") + name;

			Il2CppField* field;
			void* iter = NULL;
			while (field = klass->GetIl2CPPFields(&iter)) {
				if (!field) continue;

				std::string t(temp + xorstr_("::") + field->GetIl2CPPFieldName());
				if (RUNTIME_CRC32(t.c_str()) == path) {
					uint32_t off = field->GetIl2CPPFieldOffset();
					offsets.insert(std::make_pair(path, off));

					return off;
				}
			}
		}
	}
}

uint64_t GetFieldOffset(uint32_t path) {
	__try {
		return CallFieldOffsetNebelPaster(path);
	}
	__except (true)
	{
		printf("Exception occured at %s", __FUNCTION__);
	}
}

uint64_t GetNiggerMethodNebelPasterMan(uint32_t path) 
{
	if (MapContainsKey(offsets, path))
		return offsets[path];

	Il2CppDomain* domain = GetIl2CPPDomain();
	Il2CppAssembly** assemblies = domain->GetAssemblies();

	for (int i = 0; i < domain->AssemblyCount(); i++) {
		Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
		for (int c = 0; c < image->ClassCount(); c++) {
			std::string temp(image->assemblyName);
			temp.erase(temp.find(xorstr_(".dll")), 4);

			Il2CppClass* klass = image->GetIl2CPPClass(c);
			if (!klass) continue;

			char* name = klass->name;
			char* ns = klass->nNamespace;

			if (std::string(ns).empty())
				temp = temp + xorstr_("::") + name;
			else
				temp = temp + xorstr_("::") + ns + xorstr_("::") + name;

			Il2CppMethod* mthd;
			void* iter = NULL;
			while (mthd = klass->GetIl2CPPMethods(&iter)) {
				if (!mthd) continue;

				std::string temp2(temp + xorstr_("::") + mthd->GetIl2CPPMethodName());

				if (mthd->paramCount() > 0) {
					temp2 = temp2 + xorstr_("(");
					for (int p = 0; p < mthd->paramCount(); p++) {
						std::string t(mthd->GetIl2CPPMethodParam(p)->GetIl2CPPTypeName());
						t = t.substr(t.find(xorstr_(".")) + 1);
						temp2 = temp2 + t + xorstr_(",");
					}
					std::string t(mthd->GetIl2CPPMethodReturnType()->GetIl2CPPTypeName());
					temp2 = temp2.substr(0, temp2.size() - 1);
					temp2 = temp2 + xorstr_("): ") + t.substr(t.find(".") + 1);
				}
				else {
					std::string t(mthd->GetIl2CPPMethodReturnType()->GetIl2CPPTypeName());
					temp2 = temp2 + xorstr_("(): ") + t.substr(t.find(".") + 1);
				}

				if (RUNTIME_CRC32(temp2.c_str()) == path) {
					offsets.insert(std::make_pair(path, std::uint64_t(mthd)));
					return std::uint64_t(mthd);
				}
			}
		}
	}
}

uint64_t GetMethod(uint32_t path) {
	__try {
		return GetNiggerMethodNebelPasterMan(path);
	}
	__except (true)
	{
		printf("Exception at %s", __FUNCTION__);
	}
}


#define GETOFFSET(path) GetFieldOffset(STATIC_CRC32(path))

#define GETMETHOD(path) *reinterpret_cast<uint64_t*>(GetMethod(STATIC_CRC32(path)))

#define GETCLASS(path) GetClass(STATIC_CRC32(path))

#define GETFIELD(field_path,name,type) type& name() { \
		NP(type) \
		static auto off = GETOFFSET(field_path); \
		return *reinterpret_cast<type*>(this + off); }


#define ASSIGN_HOOK(method_path,hook) { \
	__try { \
		hook = reinterpret_cast<decltype(hook)>(GETMETHOD(method_path)); \
	} \
	__except (true) { \
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl; \
	} \
}

void InitializeClasses() {
	Il2CppDomain* domain = GetIl2CPPDomain();
	Il2CppAssembly** assemblies = domain->GetAssemblies();

	for (int i = 0; i < domain->AssemblyCount(); i++) {
		Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
		for (int c = 0; c < image->ClassCount(); c++) {
			std::string temp(image->assemblyName);
			temp.erase(temp.find(xorstr_(".dll")), 4);

			Il2CppClass* klass = image->GetIl2CPPClass(c);
			char* name = klass->name;
			char* ns = klass->nNamespace;
			if (std::string(ns).empty())
				temp = temp + xorstr_("::") + name;
			else
				temp = temp + xorstr_("::") + ns + xorstr_("::") + name;

			uint64_t ptr = std::uint64_t(klass);

			offsets.insert(std::make_pair(RUNTIME_CRC32(temp.c_str()), ptr));
		}
	}
}

void InitializeMethods() {
	Il2CppDomain* domain = GetIl2CPPDomain();
	Il2CppAssembly** assemblies = domain->GetAssemblies();

	for (int i = 0; i < domain->AssemblyCount(); i++) {
		Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
		for (int c = 0; c < image->ClassCount(); c++) {
			std::string temp(image->assemblyName);
			temp.erase(temp.find(xorstr_(".dll")), 4);

			Il2CppClass* klass = image->GetIl2CPPClass(c);
			if (!klass) continue;

			char* name = klass->name;
			char* ns = klass->nNamespace;
			if (std::string(ns).empty())
				temp = temp + xorstr_("::") + name;
			else
				temp = temp + xorstr_("::") + ns + xorstr_("::") + name;

			Il2CppMethod* mthd;
			void* iter = NULL;
			while (mthd = klass->GetIl2CPPMethods(&iter)) {
				if (!mthd) continue;

				std::string temp2(temp + xorstr_("::") + mthd->GetIl2CPPMethodName());

				if (mthd->paramCount() > 0) {
					temp2 = temp2 + xorstr_("(");
					for (int p = 0; p < mthd->paramCount(); p++) {
						std::string t(mthd->GetIl2CPPMethodParam(p)->GetIl2CPPTypeName());
						t = t.substr(t.find(xorstr_(".")) + 1);
						temp2 = temp2 + t + xorstr_(",");
					}
					std::string t(mthd->GetIl2CPPMethodReturnType()->GetIl2CPPTypeName());
					temp2 = temp2.substr(0, temp2.size() - 1);
					temp2 = temp2 + xorstr_("): ") + t.substr(t.find(".") + 1);
				}
				else {
					std::string t(mthd->GetIl2CPPMethodReturnType()->GetIl2CPPTypeName());
					temp2 = temp2 + xorstr_("(): ") + t.substr(t.find(".") + 1);
				}

				offsets.insert(std::make_pair(RUNTIME_CRC32(temp2.c_str()), std::uint64_t(mthd)));
			}
		}
	}
}

void InitializeFields() {
	Il2CppDomain* domain = GetIl2CPPDomain();
	Il2CppAssembly** assemblies = domain->GetAssemblies();

	for (int i = 0; i < domain->AssemblyCount(); i++) {
		Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
		for (int c = 0; c < image->ClassCount(); c++) {
			std::string temp(image->assemblyName);
			temp.erase(temp.find(xorstr_(".dll")), 4);

			Il2CppClass* klass = image->GetIl2CPPClass(c);
			char* name = klass->name;
			char* ns = klass->nNamespace;
			if (std::string(ns).empty())
				temp = temp + xorstr_("::") + name;
			else
				temp = temp + xorstr_("::") + ns + xorstr_("::") + name;

			Il2CppField* field;
			void* iter = NULL;
			while (field = klass->GetIl2CPPFields(&iter)) {
				if (!field) continue;

				std::string t(temp + xorstr_("::") + field->GetIl2CPPFieldName());
				uint32_t off = field->GetIl2CPPFieldOffset();
				offsets.insert(std::make_pair(RUNTIME_CRC32(t.c_str()), off));
			}
		}
	}
}

void InitializeWrapper()
{
	__try {
		InitializeClasses();
		InitializeMethods();
		InitializeFields();
	}
	__except (true)
	{
		printf("Exception caused at %s", __FUNCTION__);
	}
}