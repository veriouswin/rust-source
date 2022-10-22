Vector2 ScreenSize = { 0, 0 };
Vector2 ScreenCenter = { 0, 0 };
D3D11_VIEWPORT nViewPort;

HRESULT(*oPresent)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
HRESULT(*oResize)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;

ID3D11Device* vDevice = nullptr;
ID3D11DeviceContext* ImmediateCTX = nullptr;
ID3D11RenderTargetView* RenderTargetView = nullptr;

WNDPROC oWndProc = nullptr;
UINT vps = 1;

std::string GetActiveWindowTitle() {
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow();
	GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
	return wnd_title;
}
bool GKey(int key) {
	return GetAsyncKeyState(key) && GetActiveWindowTitle().find(xorstr_("Rust")) != std::string::npos;
}