namespace Globals {
	std::string DataDirectory = xorstr_("");
	char ConfigName[0x100] = "";
	bool InitializedCheat,
		 HitPanic,
		 ShowMenu = false;

	namespace ManipulatorData {
		bool IsManipulating = false;
	}
}

uintptr_t GameAssembly = 0;
uintptr_t UnityPlayer = 0;