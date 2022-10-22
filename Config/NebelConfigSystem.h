#pragma once
#include <direct.h>
#include <stdint.h>
#include <Windows.h>
#include <psapi.h>
#include <d3d11.h>
#include <emmintrin.h>
#include "winternl.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <thread>
#include "SimpleIni.h"

#include <string>
#include <vector>
#include <Windows.h>

template <typename T>
class VarType
{
public:
	VarType(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};

class CConfig
{
public:
	int CurrentSelectedCFG;
	CConfig()
	{
		ints = std::vector<VarType<int>*>();
		bools = std::vector<VarType<bool>*>();
		floats = std::vector<VarType<float>*>();
		colors = std::vector<VarType<ImColor>*>();
	}

	std::vector<std::string> GetAllCFGs() {
		std::vector<std::string> names;
		std::string search_path = "C:/skidded/*.cfg";
		WIN32_FIND_DATAA fd;
		HANDLE hFind = ::FindFirstFileA(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					names.push_back(fd.cFileName);
				}
			} while (::FindNextFileA(hFind, &fd));
			::FindClose(hFind);
		}
		return names;
	}

	void Initialize() {
		szPath = "C:\\skidded\\";
		Setup();
	}

	void Save() {
		if (GetAllCFGs().empty())
			return;

		std::string file;
		file = szPath + GetAllCFGs().at(CurrentSelectedCFG);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<ImColor>* pValue : colors)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}

	void Create() {
		std::string CreatePath;
		CreatePath = szPath + Globals::ConfigName + ".cfg";
		std::ofstream config(CreatePath, std::ios::out);
		szPath + GetAllCFGs().at(CurrentSelectedCFG);
	}

	void Delete() {
		if (GetAllCFGs().empty())
			return;

		remove((szPath + GetAllCFGs().at(CurrentSelectedCFG)).c_str());
		CurrentSelectedCFG -= 1;
		if (CurrentSelectedCFG < 0)
			CurrentSelectedCFG = 0;
	}

	void Load() {
		Initialize();
		if (GetAllCFGs().empty())
			return;

		std::string file;
		file = szPath + GetAllCFGs().at(CurrentSelectedCFG);
		CreateDirectoryA(szPath.c_str(), NULL);

		char value_l[64] = { '\0' };

		for (VarType<int>* pValue : ints)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 64, file.c_str());
			*pValue->value = atoi(value_l);
		}

		for (VarType<float>* pValue : floats)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 64, file.c_str());
			*pValue->value = (float)atof(value_l);
		}

		for (VarType<ImColor>* pValue : colors)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 64, file.c_str());
			*pValue->value = atoi(value_l);
		}

		for (VarType<bool>* pValue : bools)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 64, file.c_str());
			*pValue->value = !strcmp(value_l, "1");
		}
	}

private:
	void SetupValue(int& value, int def, std::string category, std::string name) /* var, default value of var, category, name of var in filesys */
	{
		value = def;
		ints.push_back(new VarType<int>(category, name, &value));
	}

	void SetupValue(bool& value, bool def, std::string category, std::string name) /* var, default value of var, category, name of var in filesys */
	{
		value = def;
		bools.push_back(new VarType<bool>(category, name, &value));
	}

	void SetupValue(float& value, float def, std::string category, std::string name) /* var, default value of var, category, name of var in filesys */
	{
		value = def;
		floats.push_back(new VarType<float>(category, name, &value));
	}

	void SetupValue(ImColor& value, ImColor def, std::string category, std::string name) /* var, default value of var, category, name of var in filesys */
	{
		value = def;
		colors.push_back(new VarType<ImColor>(category, name, &value));
	}

	void Setup()
	{
#pragma region Combat
		SetupValue(Menu::Vars::combat_alwaysheliweak, false, xorstr_("Combat"), xorstr_("HeliWeak"));
		SetupValue(Menu::Vars::combat_aimfov, 100.f, xorstr_("Combat"), xorstr_("AimFov"));
		SetupValue(Menu::Vars::combat_automatic, false, xorstr_("Combat"), xorstr_("HeliWeak"));
		SetupValue(Menu::Vars::combat_bigbullets, false, xorstr_("Combat"), xorstr_("BigBUllets"));
		SetupValue(Menu::Vars::combat_psilent, false, xorstr_("Combat"), xorstr_("silent"));
		SetupValue(Menu::Vars::combat_autoshoot, false, xorstr_("Combat"), xorstr_("auto"));
		SetupValue(Menu::Vars::combat_fastbullets, false, xorstr_("Combat"), xorstr_("fast"));
		SetupValue(Menu::Vars::combat_instaeoka, false, xorstr_("Combat"), xorstr_("eoka"));
		SetupValue(Menu::Vars::combat_hitboxoverride, false, xorstr_("Combat"), xorstr_("head"));
		SetupValue(Menu::Vars::combat_manipulator, false, xorstr_("Combat"), xorstr_("manip"));
		SetupValue(Menu::Vars::combat_autoshoot, false, xorstr_("Combat"), xorstr_("autoshoot"));
		SetupValue(Menu::Vars::combat_manipulator_bind, false, xorstr_("Combat"), xorstr_("manip bind"));
		SetupValue(Menu::Vars::combat_nosway, false, xorstr_("Combat"), xorstr_("sway"));
		SetupValue(Menu::Vars::combat_automatic, false, xorstr_("Combat"), xorstr_("automaityic"));
		SetupValue(Menu::Vars::fakeshot, false, xorstr_("Combat"), xorstr_("fakeshot"));
		SetupValue(Menu::Vars::combat_hitsound, false, xorstr_("Combat"), xorstr_("hitsound"));
		SetupValue(Menu::Vars::combat_rapid, false, xorstr_("Combat"), xorstr_("raoud"));
		SetupValue(Menu::Vars::combat_eoka, false, xorstr_("Combat"), xorstr_("eokaa"));
		SetupValue(Menu::Vars::combat_bigbullets, false, xorstr_("Combat"), xorstr_("BigBUllets"));


#pragma endregion

#pragma region Visuals
		SetupValue(Menu::Vars::visuals_players, false, xorstr_("Visuals"), xorstr_("players"));
		SetupValue(Menu::Vars::visuals_cornerbox, false, xorstr_("Visuals"), xorstr_("conrner"));
		SetupValue(Menu::Vars::TargetLine, false, xorstr_("Visuals"), xorstr_("target"));
		SetupValue(Menu::Vars::visuals_name, false, xorstr_("Visuals"), xorstr_("name"));
		SetupValue(Menu::Vars::visuals_health, false, xorstr_("Visuals"), xorstr_("health"));
		SetupValue(Menu::Vars::visuals_healthbar, false, xorstr_("Visuals"), xorstr_("Helthbar"));
		SetupValue(Menu::Vars::visuals_chams, false, xorstr_("Visuals"), xorstr_("chams"));
		SetupValue(Menu::Vars::visuals_distance, false, xorstr_("Visuals"), xorstr_("disct"));
		SetupValue(Menu::Vars::visuals_helditem, false, xorstr_("Visuals"), xorstr_("held"));
		SetupValue(Menu::Vars::visuals_sleepers, false, xorstr_("Visuals"), xorstr_("sleep"));
		SetupValue(Menu::Vars::visuals_skeleton, false, xorstr_("Visuals"), xorstr_("skeleton"));
		SetupValue(Menu::Vars::visuals_reloadind, false, xorstr_("Visuals"), xorstr_("rekiadubdu"));
		SetupValue(Menu::Vars::visuals_npc, false, xorstr_("Visuals"), xorstr_("npc"));
		SetupValue(Menu::Vars::visuals_box, false, xorstr_("Visuals"), xorstr_("box"));
		SetupValue(Menu::Vars::visuals_cham, false, xorstr_("Visuals"), xorstr_("cham"));
		SetupValue(Menu::Vars::visuals_lookingdir, false, xorstr_("Visuals"), xorstr_("lookindr"));
		SetupValue(Menu::Vars::visuals_targetplayerbelt, false, xorstr_("Visuals"), xorstr_("belt"));
		SetupValue(Menu::Vars::visuals_playerfov, 90.f, xorstr_("Visuals"), xorstr_("playerfov"));
		SetupValue(Menu::Vars::visuals_boxtype, false, xorstr_("Visuals"), xorstr_("boxtype"));
		SetupValue(Menu::Vars::visuals_chamstype, false, xorstr_("Visuals"), xorstr_("chamstype"));
		SetupValue(Menu::Vars::visuals_ores, false, xorstr_("Visuals"), xorstr_("ores"));
		SetupValue(Menu::Vars::visuals_stashes, false, xorstr_("Visuals"), xorstr_("stash"));
		SetupValue(Menu::Vars::visuals_corpses, false, xorstr_("Visuals"), xorstr_("copre"));
		SetupValue(Menu::Vars::visuals_traps, false, xorstr_("Visuals"), xorstr_("trap"));
		SetupValue(Menu::Vars::visuals_hemp, false, xorstr_("Visuals"), xorstr_("hemp"));
		SetupValue(Menu::Vars::HeliEsp, false, xorstr_("Visuals"), xorstr_("heliesp"));
		SetupValue(Menu::Vars::spider, false, xorstr_("Visuals"), xorstr_("spider"));
		SetupValue(Menu::Vars::visuals_vehicles, false, xorstr_("Visuals"), xorstr_("vehicles"));
		SetupValue(Menu::Vars::visuals_drawaimfov, false, xorstr_("Visuals"), xorstr_("drawaimfov"));
		SetupValue(Menu::Vars::indicators, false, xorstr_("Visuals"), xorstr_("indicatoras"));

#pragma endregion

#pragma region Misc
		SetupValue(Menu::Vars::misc_fakeadmin, false, xorstr_("Misc"), xorstr_("fakeadmin"));
		SetupValue(Menu::Vars::misc_fastloot, false, xorstr_("Misc"), xorstr_("fastloot"));
		SetupValue(Menu::Vars::misc_hitsound, false, xorstr_("Misc"), xorstr_("hitsound"));
		SetupValue(Menu::Vars::misc_antiaim, false, xorstr_("Misc"), xorstr_("antiaim"));
		SetupValue(Menu::Vars::misc_automed, false, xorstr_("Misc"), xorstr_("automed"));
		SetupValue(Menu::Vars::misc_bullettracers, false, xorstr_("Misc"), xorstr_("bullettracer"));
		SetupValue(Menu::Vars::misc_zoom, false, xorstr_("Misc"), xorstr_("zoom"));
		SetupValue(Menu::Vars::misc_lighting, false, xorstr_("Misc"), xorstr_("lighjting"));
		SetupValue(Menu::Vars::misc_crosshair, false, xorstr_("Misc"), xorstr_("crosshair"));
		SetupValue(Menu::Vars::custom, false, xorstr_("Misc"), xorstr_("custom"));
		SetupValue(Menu::Vars::dot, false, xorstr_("Misc"), xorstr_("dot"));
		SetupValue(Menu::Vars::gap, 5.f, xorstr_("Misc"), xorstr_("gap"));
		SetupValue(Menu::Vars::length, 5.f, xorstr_("Misc"), xorstr_("length"));
		SetupValue(Menu::Vars::chams, false, xorstr_("Misc"), xorstr_("chams1"));
		SetupValue(Menu::Vars::misc_nojumpres, false, xorstr_("Misc"), xorstr_("jump"));
		SetupValue(Menu::Vars::misc_noattackres, false, xorstr_("Misc"), xorstr_("noattack"));
		SetupValue(Menu::Vars::misc_nosprintres, false, xorstr_("Misc"), xorstr_("nosprint"));
		SetupValue(Menu::Vars::misc_spiderman, false, xorstr_("Misc"), xorstr_("spiderman"));
		SetupValue(Menu::Vars::misc_Silentwalk, false, xorstr_("Misc"), xorstr_("silentwaklk"));
		SetupValue(Menu::Vars::misc_antiaimrand, false, xorstr_("Misc"), xorstr_("aarandom"));
		SetupValue(Menu::Vars::misc_walkonwater, false, xorstr_("Misc"), xorstr_("walknowater"));
		SetupValue(Menu::Vars::CrosshairSize, false, xorstr_("Misc"), xorstr_("crosshairzie"));
		SetupValue(Menu::Vars::CrosshairGap, false, xorstr_("Misc"), xorstr_("crossgrap"));
		SetupValue(Menu::Vars::CrosshairLength, false, xorstr_("Misc"), xorstr_("crosslentch"));
		SetupValue(Menu::Vars::CrosshairThickness, false, xorstr_("Misc"), xorstr_("thickness"));

#pragma endregion

#pragma region Keybinds

#pragma endregion

#pragma region Colors

#pragma endregion
	}

	std::string szPath = "";

protected:
	std::vector<VarType<int>*> ints;
	std::vector<VarType<bool>*> bools;
	std::vector<VarType<float>*> floats;
	std::vector<VarType<ImColor>*> colors;
};