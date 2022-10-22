#pragma once
#include "../../ImGui/imgui_internal.h"
#include <functional>

CConfig ConfigSys;
/* Custom ImGui Stuff */
namespace ImGui {
	auto DoCustomTab = [&](const char* name, int index, int& selected_tab, ImVec2 size) {
		PushStyleColor(ImGuiCol_Text, ImVec4(0.65f, 0.65f, 0.65f, 0.9f));
		if (selected_tab == index)
			PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.95f));
		if (Button(name, size)) {
			if (selected_tab == index)
				PopStyleColor();
			PopStyleColor();
			selected_tab = index;
			return;
		}
		if (selected_tab == index)
			PopStyleColor();
		PopStyleColor();
	};

	void ColumnText(const char* text, int x)
	{
		auto text_size = ImGui::CalcTextSize(text);
		ImGui::SetCursorPosY(text_size.y / 4);
		ImGui::SetCursorPosX(x / 2 - text_size.x / 2);
		ImGui::Text(text);
		ImGui::Separator();
	};

	bool ClearKeyButton() {
		ImGui::SameLine();
		if (ImGui::Button("Clear")) {
			return true;
		}
		return false;
	}

	const char* const KeyNames[] = {
	"Unknown",
	"VK_LBUTTON",
	"VK_RBUTTON",
	"VK_CANCEL",
	"VK_MBUTTON",
	"VK_XBUTTON1",
	"VK_XBUTTON2",
	"Unknown",
	"VK_BACK",
	"VK_TAB",
	"Unknown",
	"Unknown",
	"VK_CLEAR",
	"VK_RETURN",
	"Unknown",
	"Unknown",
	"VK_SHIFT",
	"VK_CONTROL",
	"VK_MENU",
	"VK_PAUSE",
	"VK_CAPITAL",
	"VK_KANA",
	"Unknown",
	"VK_JUNJA",
	"VK_FINAL",
	"VK_KANJI",
	"Unknown",
	"VK_ESCAPE",
	"VK_CONVERT",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"VK_SPACE",
	"VK_PRIOR",
	"VK_NEXT",
	"VK_END",
	"VK_HOME",
	"VK_LEFT",
	"VK_UP",
	"VK_RIGHT",
	"VK_DOWN",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"VK_SNAPSHOT",
	"VK_INSERT",
	"VK_DELETE",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"VK_LWIN",
	"VK_RWIN",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"VK_NUMPAD0",
	"VK_NUMPAD1",
	"VK_NUMPAD2",
	"VK_NUMPAD3",
	"VK_NUMPAD4",
	"VK_NUMPAD5",
	"VK_NUMPAD6",
	"VK_NUMPAD7",
	"VK_NUMPAD8",
	"VK_NUMPAD9",
	"VK_MULTIPLY",
	"VK_ADD",
	"VK_SEPARATOR",
	"VK_SUBTRACT",
	"VK_DECIMAL",
	"VK_DIVIDE",
	"VK_F1",
	"VK_F2",
	"VK_F3",
	"VK_F4",
	"VK_F5",
	"VK_F6",
	"VK_F7",
	"VK_F8",
	"VK_F9",
	"VK_F10",
	"VK_F11",
	"VK_F12",
	"VK_F13",
	"VK_F14",
	"VK_F15",
	"VK_F16",
	"VK_F17",
	"VK_F18",
	"VK_F19",
	"VK_F20",
	"VK_F21",
	"VK_F22",
	"VK_F23",
	"VK_F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_NUMLOCK",
	"VK_SCROLL",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_LSHIFT",
	"VK_RSHIFT",
	"VK_LCONTROL",
	"VK_RCONTROL",
	"VK_LMENU",
	"VK_RMENU"
	};

	bool Hotkey(const char* label, int* k, const ImVec2& size_arg = ImVec2{ 45, 20 })
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		ImGuiIO& io = g.IO;
		const ImGuiStyle& style = g.Style;

		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
		const ImRect frame_bb(ImVec2(window->DC.CursorPos.x + ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f).x, window->DC.CursorPos.y + ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f).y), ImVec2(window->DC.CursorPos.x + size.x, window->DC.CursorPos.y + size.y));
		const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

		ImGui::ItemSize(total_bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(total_bb, id))
			return false;

		const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);
		const bool hovered = ImGui::ItemHoverable(frame_bb, id);

		if (hovered)
		{
			ImGui::SetHoveredID(id);
			g.MouseCursor = ImGuiMouseCursor_TextInput;
		}

		const bool user_clicked = hovered && io.MouseClicked[0];

		if (focus_requested || user_clicked)
		{
			if (g.ActiveId != id)
			{
				// Start edition
				memset(io.MouseDown, 0, sizeof(io.MouseDown));
				memset(io.KeysDown, 0, sizeof(io.KeysDown));
				*k = 0;
			}
			ImGui::SetActiveID(id, window);
			ImGui::FocusWindow(window);
		}
		else if (io.MouseClicked[0])
		{
			if (g.ActiveId == id)
				ImGui::ClearActiveID();
		}

		bool value_changed = false;
		int key = *k;
		if (g.ActiveId == id)
		{
			for (auto i = 0; i < 5; i++)
			{
				if (io.MouseDown[i])
				{
					switch (i)
					{
					case 0:
						key = VK_LBUTTON;
						break;
					case 1:
						key = VK_RBUTTON;
						break;
					case 2:
						key = VK_MBUTTON;
						break;
					case 3:
						key = VK_XBUTTON1;
						break;
					case 4:
						key = VK_XBUTTON2;
						break;
					}
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
			if (!value_changed)
			{
				for (auto i = VK_BACK; i <= VK_RMENU; i++)
				{
					if (io.KeysDown[i])
					{
						key = i;
						value_changed = true;
						ImGui::ClearActiveID();
					}
				}
			}
			*k = key;
		}

		if (ClearKeyButton())
		{
			*k = 0;
			ImGui::ClearActiveID();
		}

		char buf_display[64] = "None";

		ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), true, style.FrameRounding);

		if (*k != 0 && g.ActiveId != id)
		{
			if (*k > 210)
			{
				strcpy_s(buf_display, "Invalid Key");
			}
			else
			{
				strcpy_s(buf_display, KeyNames[*k]);
			}
		}
		else if (g.ActiveId == id)
		{
			strcpy_s(buf_display, "<Key>");
		}

		const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
		ImVec2 render_pos = ImVec2(frame_bb.Min.x + style.FramePadding.x, frame_bb.Min.y + style.FramePadding.y);

		ImGui::RenderTextClipped(ImVec2(frame_bb.Min.x + style.FramePadding.x, frame_bb.Min.y + style.FramePadding.y), ImVec2(frame_bb.Max.x - style.FramePadding.x, frame_bb.Max.y - style.FramePadding.y), buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);

		if (label_size.x > 0)
			ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), label);

		return value_changed;
	}

	namespace CustomListBox
	{
		static auto VectorGetter = [](void* vec, int idx, const char** out_text)
		{
			auto& vector = *static_cast<std::vector<std::string>*>(vec);
			if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
			*out_text = vector.at(idx).c_str();
			return true;
		};

		bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values, int height_in_items = -1)
		{
			/*if (values.empty()) { return false; }*/
			return ImGui::ListBox(label, currIndex, VectorGetter, static_cast<void*>(&values), values.size(), height_in_items);
		}
	}
}
bool CustomTab(const char* icon, bool selected)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImGuiContext& g = *GImGui;
	ImGuiID id = window->GetID(icon);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 labelSize(ImGui::CalcTextSize(icon).x + 10, 23);
	ImRect totalBb(pos, { pos.x + labelSize.x, pos.y + labelSize.y });

	ImGui::ItemSize(totalBb);
	ImGui::ItemAdd(totalBb, id);

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(totalBb, id, &hovered, &held);

	if (selected)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetColorU32(ImGuiCol_ButtonActive));
		ImGui::RenderText(totalBb.Min, icon);
		ImGui::PopStyleColor();
	}
	else if (!selected)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetColorU32(ImGuiCol_Text, 1.f));
		ImGui::RenderText(totalBb.Min, icon);
		ImGui::PopStyleColor();
	}

	return pressed;
}

ImVec4 RGBToImVec4(float r, float g, float b, float a = 255.f) {
	return ImVec4(r / 255, g / 255, b / 255, a / 255);
}
//auto SetupMenu() -> void
//{
//	auto m_checkbox_color = ImVec4(255 / 255.f, 155 / 255.f, 255 / 255.f, 255.f / 255.f);
//	auto m_slider_color = ImVec4(255 / 255.f, 155 / 255.f, 255 / 255.f, 255.f / 255.f);
//	auto m_button_color = ImVec4(255 / 255.f, 155 / 255.f, 255 / 255.f, 255.f / 255.f);
//
//
//	ImGui::SetNextWindowSize({ 550, 600 });
//	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(24.f / 255.f, 23.f / 255.f, 24.f / 255.f, 255.f / 255.f));
//	if (ImGui::Begin("##MENU", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar))
//		ImGui::PopStyleColor();
//	{
//		auto wnd_pos = ImGui::GetWindowPos();
//		auto wnd_sz = ImGui::GetWindowSize();
//
//		static bool m_draw_top_bar = true;
//
//		if (auto draw = ImGui::GetForegroundDrawList())
//		{
//			if (m_draw_top_bar)
//			{
//				draw->AddRectFilled({ wnd_pos.x, wnd_pos.y - 5 }, { wnd_pos.x + wnd_sz.x, wnd_pos.y - 50 }, ImColor(24, 23, 24, 255));
//				draw->AddRect({ wnd_pos.x + (5 /*padding*/) , wnd_pos.y - 5 - (5 /*padding*/) }, { wnd_pos.x + wnd_sz.x - (5 /*padding*/), wnd_pos.y - 50 + (5 /*padding*/) }, ImColor(42, 42, 42, 255));
//				draw->AddText({ wnd_pos.x + 10 + (2 /*padding*/),wnd_pos.y - 5 - (35 /*padding*/) }, ImColor(190, 190, 190, 255), "fucking pasted ! omg");
//			}
//		}
//
//		ImGui::SetCursorPos({ 4, 4 });
//		if (ImGui::BeginChild("##CHILD", { ImGui::GetWindowSize().x - (4 * 2 /*padding*/), ImGui::GetWindowSize().y - (4 * 2 /*padding*/) }, true))
//		{
//			ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_button_color);
//			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(150.f / 255.f, 150.f / 255.f, 150.f / 255.f, 255.f / 255.f));
//
//			ImGui::SetCursorPos({ 10, 10 });
//			if (ImGui::BeginChild("##BUTTON", { ImGui::GetWindowSize().x - (10 * 2 /*padding */) , 60 /*button height */ }, true))
//			{
//				ImGui::SetCursorPos({ 15, 15 + 3 });
//
//				static int tab = 0;
//				if (CustomTab("aimbot", tab == NULL)) tab = 0; ImGui::SameLine();
//				if (CustomTab("visuals", tab == 1)) tab = 1; ImGui::SameLine();
//				if (CustomTab("settings", tab == 2)) tab = 2; ImGui::SameLine();
//
//
//				ImGui::EndChild();
//			}
//
//			ImGui::SetCursorPosX(10);
//			if (ImGui::BeginChild("##SUB_BUTTON", { ImGui::GetWindowSize().x - (10 * 2 /*padding */) , 60 /*button height */ }, true))
//			{
//				ImGui::SetCursorPos({ 10, 15 + 3 });
//
//				static int tab = 0;
//				ImGui::SetCursorPosX(65);
//
//
//				ImGui::EndChild();
//			}
//			ImGui::PopStyleColor();
//			ImGui::PopStyleColor();
//
//			ImGui::PushStyleColor(ImGuiCol_CheckMark, m_checkbox_color);
//			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, m_slider_color);
//			ImGui::PushStyleColor(ImGuiCol_SliderGrab, m_slider_color);
//			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(19.f / 255.f, 18.f / 255.f, 19.f / 255.f, 255.f / 255.f));
//			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(19.f / 255.f, 18.f / 255.f, 19.f / 255.f, 255.f / 255.f));
//			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(19.f / 255.f, 18.f / 255.f, 19.f / 255.f, 255.f / 255.f));
//
//			ImGui::SetCursorPosX(10);
//			if (ImGui::BeginChild("##LEFT", { (ImGui::GetWindowSize().x / 2) - 15 + 1, 250 /*button height */ }, true))
//			{
//
//				static bool m_checkbox[3];
//				ImGui::Checkbox("checkbox", &m_checkbox[0]);
//				ImGui::Checkbox("checkbox one ", &m_checkbox[1]);
//				ImGui::Checkbox("checkbox two", &m_checkbox[2]);
//
//				static float m_slider = NULL;
//				ImGui::SliderFloat("##value", &m_slider, 0, 100);
//
//				ImGui::EndChild();
//			}
//
//			ImGui::SameLine();
//			if (ImGui::BeginChild("##RIGHT", { (ImGui::GetWindowSize().x / 2) - 15 + 1, 250 /*button height */ }, true))
//			{
//				ImGui::EndChild();
//			}
//			ImGui::PopFont();
//
//			ImGui::PopStyleColor();
//			ImGui::PopStyleColor();
//			ImGui::PopStyleColor();
//			ImGui::PopStyleColor();
//			ImGui::PopStyleColor();
//			ImGui::PopStyleColor();
//
//			ImGui::EndChild();
//		}
//		ImGui::End();
//	}
//
//	// Rendering
//	ImGui::Render();
//}
ImVec4 rgb_to_imvec4(float r, float g, float b, float a)
{
	return ImVec4(r / 255, g / 255, b / 255, a / 255);
}

void SetupMenu()
{
	auto& st = ImGui::GetStyle();
	st.FrameBorderSize = 1.0f;
	st.FramePadding = ImVec2(4.0f, 2.0f);
	st.ItemSpacing = ImVec2(8.0f, 2.0f);
	st.WindowBorderSize = 1.0f;
	st.WindowRounding = 1.0f;
	st.ChildRounding = 1.0f;
	st.AntiAliasedFill = false;
	st.AntiAliasedLines = true;
	st.WindowRounding = 7.000f;
	st.ChildRounding = 6.000f;
	st.PopupRounding = 4.000f;
	st.WindowTitleAlign = ImVec2(0.500f, 0.500f);
	st.FrameRounding = 3.000f;
	st.ScrollbarRounding = 6.000f;
	st.GrabRounding = 5.000f;
	st.TabRounding = 6.000f;
	st.WindowBorderSize = 0.0f;

	// Setup style
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.18f, 0.18f, 0.18f, 0.41f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.07f, 0.07f, 0.07f, 0.74f);
	colors[ImGuiCol_FrameBgHovered] = RGBToImVec4(128, 105, 212);
	colors[ImGuiCol_FrameBgActive] = RGBToImVec4(128, 105, 212);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.15f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = RGBToImVec4(128, 105, 212);
	colors[ImGuiCol_ScrollbarGrabActive] = RGBToImVec4(148, 125, 232);
	colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = RGBToImVec4(148, 125, 232, 255);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = RGBToImVec4(148, 125, 232);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_Header] = RGBToImVec4(255, 255, 255, 255);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.06f, 0.06f, 0.07f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.06f, 0.05f, 0.05f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.35f, 0.35f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	ImGui::SetNextWindowSize(ImVec2(510, 550));
	if (ImGui::Begin(xorstr_("skidded.xyz"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings)) {
		ImGui::GetStyle().WindowPadding = { 10.f, 10.f };
		static bool doOnce = false;
		if (!doOnce) {
			ConfigSys.Initialize();
			doOnce = true;
		}
		if (ImGui::BeginChild(xorstr_("CatRewrite"), ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysUseWindowPadding)) {
			const char* BoxTypes[] = { "Cornered", "Full", "3D" };
			const char* Lighting[] = { "Default", "Dark", "Light" };
			const char* Chams[] = { "Disable", "Rainbow", "Reflect" };
			const char* Crosshair[] = { "Disabled", "plusminus", "evilcheats", "circle", "swastika" };
			static int SelectedTab = 0;
			ImGui::SetCursorPosX(8.f);
			ImGui::DoCustomTab(xorstr_("Combat"), 0, SelectedTab, ImVec2(111.f, 28.f));
			ImGui::SameLine();
			ImGui::DoCustomTab(xorstr_("Visuals"), 1, SelectedTab, ImVec2(111.f, 28.f));
			ImGui::SameLine();
			ImGui::SetCursorPosX(251.f);
			ImGui::DoCustomTab(xorstr_("Misc"), 2, SelectedTab, ImVec2(111.f, 28.f));
			ImGui::SameLine();
			ImGui::DoCustomTab(xorstr_("Config"), 3, SelectedTab, ImVec2(111.f, 28.f));

			switch (SelectedTab) {
			case 0:
				/* Aimbot Tab */
				ImGui::Columns(2, nullptr, false);
				ImGui::BeginChild("##Main", ImVec2(230, 300), true); {
					ImGui::ColumnText("Main", 230);
					ImGui::Checkbox("pSilent", &Menu::Vars::combat_psilent);
					ImGui::Checkbox("HeliWeak", &Menu::Vars::combat_alwaysheliweak);
					ImGui::Checkbox("Always Headshot", &Menu::Vars::combat_hitboxoverride);
					ImGui::Checkbox("Auto Shoot", &Menu::Vars::combat_autoshoot);
					ImGui::Checkbox("Peirce", &Menu::Vars::combat_pierce);
					ImGui::Checkbox("Manipulator", &Menu::Vars::combat_manipulator); ImGui::SameLine(); ImGui::Hotkey("##ManipulatorKey", &Menu::Vars::combat_manipulator_bind);
					ImGui::SliderFloat("Aim FOV", &Menu::Vars::combat_aimfov, 10.f, 1000.f);
				} ImGui::EndChild();
				ImGui::NextColumn(); /* Second Column */
				ImGui::BeginChild("##Weapon", ImVec2(230, 300), true); {
					ImGui::ColumnText("Weapon", 230);
					ImGui::Checkbox("BigBullets", &Menu::Vars::combat_bigbullets);
					ImGui::Checkbox("Fast Bullets", &Menu::Vars::combat_fastbullets);
					ImGui::Checkbox("Insta Eoka", &Menu::Vars::combat_instaeoka);
					ImGui::Checkbox("Automatic", &Menu::Vars::combat_automatic);
					ImGui::Checkbox("No Sway", &Menu::Vars::combat_nosway);
					ImGui::SliderFloat("Recoil Amt", &Menu::Vars::combat_recoil, 0.f, 100.f);
					ImGui::SliderFloat("Spread Amt", &Menu::Vars::combat_spread, 0.f, 100.f);
				} ImGui::EndChild();
				break;
			case 1:
				/* Visuals Tab */
				ImGui::Columns(2, nullptr, false);
				ImGui::BeginChild("##PlayerEntity", ImVec2(230, 300), true); {
					ImGui::ColumnText("Player Entity", 230);
					ImGui::Checkbox("Players", &Menu::Vars::visuals_players);
					ImGui::Checkbox("Sleepers", &Menu::Vars::visuals_sleepers);
					ImGui::Checkbox("NPCs", &Menu::Vars::visuals_npc);
					ImGui::Checkbox("Box ESP", &Menu::Vars::visuals_box);
					ImGui::Checkbox("Heatlbar", &Menu::Vars::visuals_healthbar);
					ImGui::Checkbox("Skeleton ESP", &Menu::Vars::visuals_skeleton);
					ImGui::Checkbox("Looking Direction", &Menu::Vars::visuals_lookingdir);
					ImGui::Checkbox("Chams", &Menu::Vars::chams);
					ImGui::Checkbox("TPlayer Belt", &Menu::Vars::visuals_targetplayerbelt);
					ImGui::Combo("Box Type", &Menu::Vars::visuals_boxtype, BoxTypes, ARRAYSIZE(BoxTypes));
					ImGui::SliderFloat("Player FOV", &Menu::Vars::visuals_playerfov, 60.f, 135.f);
				} ImGui::EndChild();
				ImGui::NextColumn(); /* Second Column */
				ImGui::BeginChild("##World", ImVec2(230, 300), true); {
					ImGui::ColumnText("World", 230);
					ImGui::Checkbox("Ore ESP", &Menu::Vars::visuals_ores);
					ImGui::Checkbox("Stash ESP", &Menu::Vars::visuals_stashes);
					ImGui::Checkbox("Corpse ESP", &Menu::Vars::visuals_corpses);
					ImGui::Checkbox("Trap ESP", &Menu::Vars::visuals_traps);
					ImGui::Checkbox("Hemp ESP", &Menu::Vars::visuals_hemp);
					ImGui::Checkbox("Vehicle ESP", &Menu::Vars::visuals_vehicles);
					ImGui::Checkbox("PatolHeliCopter ESP", &Menu::Vars::HeliEsp);
					ImGui::Checkbox("Draw Aim FOV", &Menu::Vars::visuals_drawaimfov);
					ImGui::Checkbox("Reload Indicator", &Menu::Vars::visuals_reloadind);
				} ImGui::EndChild();
				break;
			case 2:
				/* Misc Tab */
				ImGui::Columns(2, nullptr, false);
				ImGui::BeginChild("##Main", ImVec2(230, 300), true); {
					ImGui::ColumnText("Main", 230);
					ImGui::Checkbox("Fake Admin", &Menu::Vars::misc_fakeadmin);
					ImGui::Checkbox("FakeAdmin", &Menu::Vars::misc_fakeadmin);
					ImGui::Checkbox("Fast Loot", &Menu::Vars::misc_fastloot);
					ImGui::Checkbox("Auto Med", &Menu::Vars::misc_automed);
					ImGui::Checkbox("Bullet Tracers", &Menu::Vars::misc_bullettracers);
					ImGui::Checkbox("Antiaim", &Menu::Vars::misc_antiaim);
					ImGui::Checkbox("Zoom", &Menu::Vars::misc_zoom); ImGui::SameLine(); ImGui::Hotkey("##ZoomKey", &Menu::Vars::misc_zoomkey);
					ImGui::Combo("Lighting", &Menu::Vars::misc_lighting, Lighting, ARRAYSIZE(Lighting));
					ImGui::Combo("Crosshair", &Menu::Vars::misc_crosshair, Crosshair, ARRAYSIZE(Crosshair));
					ImGui::Checkbox(xorstr_("Custom Crosshair"), &Menu::Vars::custom);
					if (Menu::Vars::custom) {
						ImGui::SliderFloat(xorstr_("Gap"), &Menu::Vars::gap, 0.f, 50.f);
						ImGui::SliderFloat(xorstr_("Length"), &Menu::Vars::length, 0.f, 50.f);
						ImGui::Checkbox(xorstr_("Dot"), &Menu::Vars::dot);
						ImGui::SameLine(); ImGui::ColorButton(xorstr_("Crosshair##Color"), Menu::Vars::color_customcrosshair);
					}
				} ImGui::EndChild();
				ImGui::NextColumn(); /* Second Column */
				ImGui::BeginChild("##Movement", ImVec2(230, 300), true); {
					ImGui::ColumnText("Weapon", 230);
					ImGui::Checkbox("Infinite Jump", &Menu::Vars::misc_nojumpres);
					ImGui::Checkbox("No Attack Restriction", &Menu::Vars::misc_noattackres);
					ImGui::Checkbox("omnisprint", &Menu::Vars::misc_nosprintres);
					ImGui::Checkbox("No Fall Damage", &Menu::Vars::misc_nofalldmg);
					ImGui::Checkbox("Walk On Water", &Menu::Vars::misc_walkonwater);
					ImGui::Checkbox("Hitsound", &Menu::Vars::misc_hitsound);
					ImGui::Checkbox("FakeShots", &Menu::Vars::fakeshot);
				} ImGui::EndChild();
				break;
			case 3:
				std::vector<std::string> CFGList = ConfigSys.GetAllCFGs();
				ImGui::BeginChild("##CFGList", ImVec2(480, 300), true); {
					ImGui::ColumnText("Configs", 480);
					ImGui::SetCursorPos(ImVec2(80, 18));
					ImGui::CustomListBox::ListBox("##CFGList", &ConfigSys.CurrentSelectedCFG, CFGList, 8);
					ImGui::SetCursorPos(ImVec2(2, 155));
					if (ImGui::Button("Create Config", ImVec2(100.f, 0)))
						ConfigSys.Create();
					ImGui::SameLine();
					if (ImGui::Button("Delete Config", ImVec2(100.f, 0)))
						ConfigSys.Delete();
					ImGui::SameLine();
					if (ImGui::Button("Panic"))
						Globals::HitPanic = true;
					ImGui::SameLine();
					if (ImGui::Button("Save Config", ImVec2(100.f, 0)))
						ConfigSys.Save();
					ImGui::SameLine();
					if (ImGui::Button("Load Config", ImVec2(100.f, 0)))
						ConfigSys.Load();
					if (Globals::ConfigName != NULL && Globals::ConfigName[0] == '\0') {
						ImGui::SetCursorPos(ImVec2(206, 135));
						ImGui::Text("Config Name");
					}
					ImGui::SetCursorPos(ImVec2(80, 135));
					ImGui::InputText("##Config Name", Globals::ConfigName, 0x100);
				} ImGui::EndChild();
				break;
			}
		}
	}
}