void HookAll();
void UnhookAll();

HWND game_window;
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WndProcHook(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	__try {
		if (Globals::ShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		if (GetAsyncKeyState(VK_INSERT) & 1) {
			Globals::ShowMenu = !Globals::ShowMenu;
		}
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
	return CallWindowProcA(oWndProc, hWnd, uMsg, wParam, lParam);
}
void InitFonts() {
	__try {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplWin32_Init(game_window);
		ImGui_ImplDX11_Init(vDevice, ImmediateCTX);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
HRESULT Present_hk(IDXGISwapChain* swapChain, UINT SyncInterval, UINT Flags) {
	__try {
		if (!vDevice) {
			swapChain->GetDevice(__uuidof(vDevice), reinterpret_cast<PVOID*>(&vDevice));
			vDevice->GetImmediateContext(&ImmediateCTX);
			ID3D11Texture2D* renderTarget = nullptr;
			swapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<PVOID*>(&renderTarget));
			vDevice->CreateRenderTargetView(renderTarget, nullptr, &RenderTargetView);
			Renderer::Init(swapChain);
			renderTarget->Release();
			InitFonts();
		}
		ImmediateCTX->OMSetRenderTargets(1, &RenderTargetView, nullptr);
		ImmediateCTX->RSGetViewports(&vps, &nViewPort);
		ScreenSize = { nViewPort.Width, nViewPort.Height };
		ScreenCenter = { nViewPort.Width / 2.0f, nViewPort.Height / 2.0f };

		if (!Globals::HitPanic) {

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			if (Renderer::new_frame(swapChain)) {
				SYSTEMTIME st;
				GetLocalTime(&st);
				Renderer::text(Vector2(5, 4), RGBToImVec4(255, 0, 255), 14.f, false, true, wxorstr_(L"skidded.xyz | %d:%d:%d"), (int)st.wHour, (int)st.wMinute, (int)st.wSecond);
				entities::loop();

				if (Menu::Vars::visuals_drawaimfov && BaseNetworkable::clientEntities()->entityList() && BaseNetworkable::clientEntities()->entityList()->vals->size >= 1)
					Renderer::circle(ScreenCenter, Menu::Vars::color_playeraimfov, Menu::Vars::combat_aimfov, 1.f);

				Renderer::end_frame();
			}
			if (Globals::ShowMenu)
				SetupMenu();

			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
		else {
			static bool once = false;
			if (!once) {
				Globals::ShowMenu = false;
				UnhookAll();
				ShowWindow(GetConsoleWindow(), SW_HIDE);
				once = true;
			}
		}
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
	return oPresent(swapChain, SyncInterval, Flags);
}

HRESULT Resize_hk(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	__try {
		Renderer::reset_canvas();
		if (RenderTargetView) RenderTargetView->Release();
		if (ImmediateCTX) ImmediateCTX->Release();
		if (vDevice) vDevice->Release();
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
	return oResize(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}

void CreateCFGBeans() {
	//NEBEL IS PASTER

	if (!std::filesystem::exists("C:\\InternalRost")) {
		std::filesystem::create_directories(xorstr_("C:\\InternalRost"));
	}
	Globals::DataDirectory = xorstr_("C:\\InternalRost");
}
DWORD __stdcall MainThread(LPVOID) {
	__try {
		UnityPlayer = (UINT_PTR)GetModuleHandleA(xorstr_("UnityPlayer.dll"));
		GameAssembly = (UINT_PTR)GetModuleHandleA(xorstr_("GameAssembly.dll"));

		while (!game_window) {
			EnumWindows([](HWND hWnd, LPARAM lParam) -> BOOL {
				DWORD pid = 0;
				GetWindowThreadProcessId(hWnd, &pid);
				if (pid == GetCurrentProcessId()) {
					*reinterpret_cast<HWND*>(lParam) = hWnd;
					return FALSE;
				}

				return TRUE;
				}, reinterpret_cast<LPARAM>(&game_window));
		}
		auto addr = mem::find_pattern(UnityPlayer, (PBYTE)"\x48\x83\xEC\x28\xE8\x00\x00\x00\x00\x48\x8B\x80\xA0\x03\x00\x00", xorstr_("xxxxx????xxxxxxx"));

		if (!addr)
			return false;

		auto swapchain = reinterpret_cast<IDXGISwapChain * (__fastcall*)()>(addr)();

		if (swapchain) {
			auto table = *reinterpret_cast<PVOID**>(swapchain);
			oPresent = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT)>(table[8]);
			oResize = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT)>(table[13]);

			oWndProc = (WNDPROC)SetWindowLongPtrW(game_window, GWLP_WNDPROC, (LONG_PTR)WndProcHook);


			/* -------------------Console----------------- */

			AllocConsole();
			SetConsoleTitleA(xorstr_("[+] Debug Console"));
			freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
			freopen_s((FILE**)stdin, "CONIN$", "r", stdin);

			/* ------------------------------------------- */

			InitializeCheat();
			HookAll();

			FILE* fp; AllocConsole();
			freopen_s(&fp, "CONOUT$", "w", stdout);

			return true;
		}
		return false;
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}