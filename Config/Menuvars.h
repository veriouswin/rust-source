#pragma once
namespace settings {
	std::string data_dir = xorstr_("");

	bool cheat_init = false;
	float flyhack = 0.f;
	float hor_flyhack = 0.f;
	float max_flyhack = 0.f;
	float max_hor_flyhack = 0.f;
	bool panic = false;
	bool desynctime = false;
	bool desync = false;
	bool desync_key = false;
}
namespace Menu {

	namespace Vars {
		/* Combat */
		/* Main */
		std::wstring dlldirectory;
		char ConfigName[0x100] = "cfg";
		bool combat_psilent = false;
		bool noattackanim = false;
		bool speedhack = false;
		bool remove_attack_anim = false;
		bool combat_alwaysheliweak = false;
		bool combat_hitboxoverride = false;
		bool combat_manipulator = false;
		bool combat_fakeshoot = false;
		bool combat_silentmelee = false;
		bool combat_autoshoot = false;
		bool combat_pierce = false;
		bool fakelag = false;
		float combat_aimfov = 100.f;
		int combat_manipulator_bind = 0;


		/* Weapon */
		bool combat_bigbullets = false;
		bool combat_fastbullets = false;
		bool combat_instaeoka = false;
		bool combat_nosway = false;
		bool combat_automatic = false;
		int FakeShotkey = 0;
		bool fakeshot = false;
		bool combat_hitsound = false;
		bool combat_silentautoshoot = false;
		bool combat_rapid = false;
		bool combat_eoka = false;
		float combat_recoil = 100.f;
		float combat_spread = 100.f;

		/* Visuals */
		/* PlayerEntity */
		bool visuals_players = false;
		bool visuals_cornerbox = false;
		bool TargetLine = false;
		bool visuals_name = false;
		bool visuals_health = false;
		bool visuals_healthbar = false;
		bool visuals_chams = false;
		bool chams12 = false;
		bool visuals_chamsglow = false;
		bool visuals_chamsnormal = false;
		bool visuals_flatChams = false;
		bool visuals_rainbowchams = false;
		bool visuals_distance = false;
		bool visuals_helditem = false;
		bool visuals_sleepers = false;
		bool visuals_radar = false;
		bool InvisiblePlayerIndicator = false;
		bool visuals_npc = false;
		bool visuals_box = false;
		bool visuals_cham = false;
		bool visuals_skeleton = false;
		bool visuals_lookingdir = false;
		bool visuals_targetplayerbelt = false;
		float visuals_playerfov = 90.f;
		int visuals_boxtype = 0;
		int visuals_chamstype = 0;

		/* World */
		bool visuals_ores = false;
		bool visuals_stashes = false;
		bool visuals_corpses = false;
		bool visuals_traps = false;
		bool visuals_hemp = false;
		bool HeliEsp = false;
		bool spider = false;
		bool visuals_vehicles = false;
		bool visuals_drawaimfov = false;
		bool visuals_reloadind = false;
		bool indicators = false;

		/* Misc */
		/* Main */
		bool misc_fakeadmin = false;
		bool misc_fastloot = false;
		float misc_rayleigh_changer = 100.f;
		bool misc_rayleigh = false;
		bool gBase = false;
		bool misc_hitsound = false;
		float rayleigh = 10.f;
		bool misc_antiaim = false;
		bool misc_automed = false;
		bool Skeet_indicator = false;
		bool misc_powershoot = false;
		bool misc_bullettracers = false;
		bool misc_zoom = false;
		bool misc_hitlogs = false;
		int misc_zoomkey = 0;
		bool misc_interactive = false;
		int misc_misc_interactivekey = 0;
		int misc_lighting = 0;
		int misc_powershoot_bind = 0;
		int misc_crosshair = 0;
		bool custom = false;
		bool dot = false;
		float gap = 5.f;
		float length = 5.f;
		bool chams = false;
		inline float Chams[] = { 1.f,1.f,1.f,1.f };
		inline float VisibleChams[] = { 0.f,1.f,0.f,1.f };
		inline float InVisibleChams[] = { 1.f,0.f,0.f,1.f };
		inline float namecolor[] = { 52, 80, 237 };
		inline float boxcolor[] = { 52, 80, 237 };
		inline float healthcolor[] = { 52, 80, 237 };
		inline float distancecolor[] = { 52, 80, 237 };
		inline float helditemcolor[] = { 52, 80, 237 };
		inline float skeletoncolor[] = { 52, 80, 237 };
		inline float oofcolor[] = { 52, 80, 237 };
		/* Movement */
		bool misc_nojumpres = false;
		bool misc_noattackres = false;
		bool misc_nosprintres = false;
		bool misc_spiderman = false;
		bool misc_Silentwalk = false;
		bool misc_antiaimrand = false;
		bool misc_nofalldmg = false;
		bool misc_walkonwater = false;
		inline int CrosshairSize = 5; inline int CrosshairGap = 5; inline int CrosshairLength = 5; inline int CrosshairThickness = 5;//inline bool AnimateCrosshair = false; inline int CrosshairRotation = 0;


		/* Colors */
		/* Player */
		ImColor color_playersvis = ImColor(131, 255, 0);
		ImColor color_playersinvis = ImColor(255, 0, 0);
		ImColor color_teamvis = ImColor(159, 226, 191);
		ImColor color_teaminvis = ImColor(2255, 0, 255);
		ImColor color_sleepervis = ImColor(223, 255, 0);
		ImColor color_sleeperinvis = ImColor(255, 0, 255);
		ImColor color_sleeperskeletonvis = ImColor(255, 255, 255, 255);
		ImColor color_sleeperskeletoninvis = ImColor(255, 255, 255, 255);
		ImColor color_playerskeletonvis = ImColor(131, 255, 0);
		ImColor color_playerskeletoninvis = ImColor(255, 0, 0);

		ImColor color_playerlookingdir = ImColor(84, 84, 84);
		ImColor color_playeraimfov = ImColor(84, 84, 84);
		ImColor color_bullettracer = ImColor(255, 255, 255, 255);
		ImVec4 color_customcrosshair = ImColor(255, 255, 255, 255);


		/* Player Boxes */
		ImColor color_playerboxvis = ImColor(131, 255, 0);
		ImColor color_playerboxinvis = ImColor(255, 0, 255);
		ImColor color_targetplayerbox = ImColor(255, 0, 255);

		/* NPC */
		ImColor color_npcvis = ImColor(131, 255, 0);
		ImColor color_npcinvis = ImColor(255, 255, 255, 255);
		ImColor color_npcskeletonvis = ImColor(255, 255, 255, 255);
		ImColor color_npcskeletoninvis = ImColor(255, 255, 255, 255);

		/* World */
		ImColor color_ores = ImColor(248, 255, 103);
		ImColor HeliEsp_Color = ImColor(248, 255, 103);
		ImColor color_stashes = ImColor(248, 255, 103);
		ImColor color_corpses = ImColor(248, 255, 103);
		ImColor color_traps = ImColor(248, 255, 103);
		ImColor color_hemp = ImColor(248, 255, 103);
		ImColor color_vehicles = ImColor(248, 255, 103);
	}
}

namespace stor {
	uintptr_t uBase = NULL;
	uintptr_t gBase = NULL;
	uintptr_t closestPlayer = NULL;
	uintptr_t closestHeli = NULL;
	uintptr_t meme_target = NULL;
}
namespace Functions
{
	inline UINT_PTR g_PresentImplementation = 0;
	inline UINT_PTR g_OriginalWndProcHandler = 0;

	inline HRESULT(*Original_DxgiPresent)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
	inline HRESULT(*Original_DxgiResizeBuffer)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);

	inline void(*Original_VisUpdateUsingCulling)(void*, float, bool);
	inline Vector3(*Original_MoveTowards)(Vector3, Vector3, float);
	inline void(*Original_AddPunch)(UINT_PTR, Vector3, float);
	inline void(*Original_EokaDoAttack)(UINT_PTR);
	inline void(*Original_HandleJumping)(UINT_PTR, UINT_PTR, bool, bool);
	inline void(*Original_HandleRunDuckCrawl)(UINT_PTR, UINT_PTR, bool, bool, bool);
	inline void(*Original_DoAttack)(UINT_PTR);
	inline void(*Original_SetFlying)(UINT_PTR);
	inline void(*Original_UpdateGravity)(UINT_PTR, UINT_PTR);
	inline void(*Original_EditViewAngles)(UINT_PTR);
	inline void(*Original_FrameUpdate)(UINT_PTR, bool);
	inline void(*Original_OnCameraPositionChanged)(UINT_PTR, UINT_PTR, UINT_PTR);
	inline bool(*Original_CanHoldItems)(UINT_PTR);
	inline bool(*Original_IsWaterMaterial)(UINT_PTR, UINT_PTR);
	inline bool(*Original_CanAttack)(UINT_PTR);
	inline void(*Original_SendProjectileAttack)(UINT_PTR, UINT_PTR);
	inline bool(*Original_GetIsHeadshot)(UINT_PTR);
	inline void(*Original_ProjectileMovement)(UINT_PTR, float);
	inline void(*Original_OnAttacked)(UINT_PTR, UINT_PTR);
	inline void(*Original_DoHitNotify)(UINT_PTR, UINT_PTR);
	inline void(*Original_OnLand)(UINT_PTR, float);
	inline bool(*Original_DoHit)(UINT_PTR, UINT_PTR, Vector3, Vector3);
	inline void(*Original_Launch)(UINT_PTR);
	inline void(*Original_OnGUI)(UINT_PTR);
	inline void(*Original_ClientInput)(UINT_PTR, UINT_PTR);
	inline bool(*Original_ShouldShowHud)(void);
	inline Vector3(*Original_GetModifiedAimConeDirection)(float, Vector3, bool);
	inline UINT_PTR(*Original_CreateProjectile)(void*, void*, Vector3, Vector3, Vector3);
}
