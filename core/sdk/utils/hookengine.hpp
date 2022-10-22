namespace hookengine {
	template<typename Function>
	void hook(Function*& func, void* detour) {
		__try {
			DetourAttach(&(PVOID&)func, detour);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}

	template<typename Function>
	void unhook(Function*& func, void* detour) {
		__try {
			DetourDetach(&(PVOID&)func, detour);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
}