#pragma once
#include <core/drawing/D2DRender/ActualRender.hpp>
#include <core/drawing/D2DRender/ActualRender.hpp>
#include <core/drawing/D2DRender/ActualRender.hpp>
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
Vector3 LocalPosition;
Quaternion LocalRotation;
Item heldEntity;
Vector3 beforeInvalid = Vector3().Zero();

namespace entities {
	namespace belt {
		Vector2 pos = Vector2(200, 200);
		bool should_drag = false;
		bool should_move = false;

		POINT cursor;
		POINT cursor_corrected;
		void belt_tab_mov(Vector2 size) {
			GetCursorPos(&cursor);

			if (GetAsyncKeyState(VK_LBUTTON) && (cursor.x > pos.x && cursor.y > pos.y && cursor.x < pos.x + size.x && cursor.y < pos.y + size.y)) {
				should_drag = true;
				if (!should_move) {
					cursor_corrected.x = cursor.x - pos.x;
					cursor_corrected.y = cursor.y - pos.y;
					should_move = true;
				}
			}

			if (should_drag) {
				pos.x = cursor.x - cursor_corrected.x;
				pos.y = cursor.y - cursor_corrected.y;
			}

			if (GetAsyncKeyState(VK_LBUTTON) == 0) {
				should_drag = false;
				should_move = false;
			}
		}
	}

	float dfc(BasePlayer* player) {
		if (!player)
			return 1000.f;

		if (!player->isCached())
			return 1000.f;

		if (player->bones()->dfc.empty())
			return 1000.f;

		return ScreenCenter.distance_2d(player->bones()->dfc);
	}
	ImColor get_color(BasePlayer* player, bool boxes = false) {
		if (!boxes) {
			if (player->HasPlayerFlag(PlayerFlags::Sleeping)) {
				if (player->is_visible())
					return Menu::Vars::color_sleepervis;
				else
					return Menu::Vars::color_sleeperinvis;
			}

			if (!player->playerModel()->isNpc()) {
				if (player->is_target())
					if (player->is_visible())
						return Menu::Vars::color_playersvis;
					else
						return Menu::Vars::color_playersinvis;
				else
					if (player->is_teammate())
						if (player->is_visible())
							return Menu::Vars::color_teamvis;
						else
							return Menu::Vars::color_teaminvis;
					else
						if (player->is_visible())
							return Menu::Vars::color_playersvis;
						else
							return Menu::Vars::color_playersinvis;
			}
			else {
				if (!player->is_target())
					if (player->is_visible())
						return Menu::Vars::color_npcvis;
					else
						return Menu::Vars::color_npcinvis;
				else
					if (player->is_visible())
						return Menu::Vars::color_npcvis;
					else
						return Menu::Vars::color_npcinvis;
			}
		}

		if (boxes) {
			if (player->is_target())
				return Menu::Vars::color_targetplayerbox;
			else
				if (player->is_visible())
					return Menu::Vars::color_playerboxvis;
				else
					return Menu::Vars::color_playerboxinvis;
		}
	}

	float BOG_TO_GRD(float BOG) {
		return (180 / M_PI) * BOG;
	}

	float GRD_TO_BOG(float GRD) {
		return (M_PI / 180) * GRD;
	}

	__forceinline uint32_t RandomInteger(uint32_t Min, uint32_t Max)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		const std::uniform_int_distribution<uint32_t> distr(Min, Max);
		return distr(eng);
	}

	void loop() {
		static int cases = 0;
		static float r = 1.00f, g = 0.00f, b = 1.00f;
		switch (cases) {
		case 0: { r -= 0.0004f; if (r <= 0) cases += 1; break; }
		case 1: { g += 0.0004f; b -= 0.0004f; if (g >= 1) cases += 1; break; }
		case 2: { r += 0.0004f; if (r >= 1) cases += 1; break; }
		case 3: { b += 0.0004f; g -= 0.0004f; if (b >= 1) cases = 1; break; }
		default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
		}
		static ImColor clr = ImColor(RandomInteger(58, 60), RandomInteger(247, 255), RandomInteger(255, 0), 0);
		static float faken_rot = 0.0f;
		static int gamerjuice = 0;
		float a = ScreenCenter.y / 30.0f;
		float gamma = atan(a / a);
		switch (Menu::Vars::misc_crosshair) {
		case 1:
			Renderer::rectangle_filled(Vector2{ ScreenCenter.x + 5, ScreenCenter.y }, Vector2{ 4, 2 }, ImColor(r, g, b)); // right
			Renderer::rectangle_filled(Vector2{ ScreenCenter.x - 5 + 2, ScreenCenter.y }, Vector2{ -4 , 2 }, ImColor(r, g, b));  // left
			Renderer::rectangle_filled(Vector2{ ScreenCenter.x , ScreenCenter.y - 5 + 2 }, Vector2{ 2 , -4 }, ImColor(r, g, b)); // up
			Renderer::rectangle_filled(Vector2{ ScreenCenter.x , ScreenCenter.y + 5 }, Vector2{ 2 , 4 }, ImColor(r, g, b)); // down
			break;
		case 2:
			Renderer::line(ScreenCenter, Vector2{ ScreenCenter.x + 25, ScreenCenter.y - 25 }, ImColor(0, 255, 255), false, 0.93f);
			Renderer::line(ScreenCenter, Vector2{ ScreenCenter.x + 25, ScreenCenter.y - 25 }, ImColor(0, 255, 255), false, 0.94f);

			Renderer::line(Vector2{ ScreenCenter.y + 4, ScreenCenter.y + 4 }, Vector2{ ScreenCenter.y + 4 + 4, ScreenCenter.y + 4 + 4 }, ImColor(0, 0, 0), false, 0.7f);
			Renderer::line(Vector2{ ScreenCenter.y + 4, ScreenCenter.y + 4 }, Vector2{ ScreenCenter.y + 4 + 4, ScreenCenter.y - 4 - 4 }, ImColor(0, 0, 0), false, 0.7f);
			Renderer::line(Vector2{ ScreenCenter.y + 4, ScreenCenter.y + 4 }, Vector2{ ScreenCenter.y + 4 + 4, ScreenCenter.y - 4 - 4 }, ImColor(0, 0, 0), false, 0.7f);
			Renderer::line(Vector2{ ScreenCenter.y - 4, ScreenCenter.y + 4 }, Vector2{ ScreenCenter.y + 4 + 4, ScreenCenter.y + 4 + 4 }, ImColor(0, 0, 0), false, 0.7f);
			break;
		case 3:
			Renderer::circle(ScreenCenter, ImColor(0, 0, 0), 2.f, 1.f);
			Renderer::circle(ScreenCenter, ImColor(0, 0, 0), 4.f, 1.f);
			Renderer::circle(ScreenCenter, ImColor(255, 255, 255), 3.f, 1.f);
		case 4:
			if ((int)faken_rot > 89) { faken_rot = (float)0; }
			faken_rot++;

			if (gamerjuice > 30)
			{
				gamerjuice = 0;
				clr = ImColor(RandomInteger(58, 60), RandomInteger(247, 255), RandomInteger(255, 0), 0);
			}
			else
				gamerjuice++;

			for (int i = 0; i < 4; i++)
			{
				std::vector <int> p;
				p.push_back(a * sin(GRD_TO_BOG(faken_rot + (i * 90))));									//p[0]		p0_A.x
				p.push_back(a * cos(GRD_TO_BOG(faken_rot + (i * 90))));									//p[1]		p0_A.y
				p.push_back((a / cos(gamma)) * sin(GRD_TO_BOG(faken_rot + (i * 90) + BOG_TO_GRD(gamma))));	//p[2]		p0_B.x
				p.push_back((a / cos(gamma)) * cos(GRD_TO_BOG(faken_rot + (i * 90) + BOG_TO_GRD(gamma))));	//p[3]		p0_B.y


				Renderer::line(ScreenCenter, { ScreenCenter.x + p[0], ScreenCenter.y - p[1] }, clr, true);
				Renderer::line({ ScreenCenter.x + p[0], ScreenCenter.y - p[1] }, { ScreenCenter.x + p[2], ScreenCenter.y - p[3] }, clr, true);
			}
		default:
			break;
		}

		if (Menu::Vars::custom) {
			if (Menu::Vars::dot) {
				Renderer::rectangle_filled(Vector2{ ScreenCenter.x ,  ScreenCenter.y }, Vector2{ 2, 2 }, Menu::Vars::color_customcrosshair);
			}
			// i did it ! lol
			Renderer::rectangle_filled(Vector2{ ScreenCenter.x + Menu::Vars::gap, ScreenCenter.y }, Vector2{ Menu::Vars::length, 2 }, Menu::Vars::color_customcrosshair); // right
			Renderer::rectangle_filled(Vector2{ ScreenCenter.x - Menu::Vars::gap + 2, ScreenCenter.y }, Vector2{ -Menu::Vars::length , 2 }, Menu::Vars::color_customcrosshair); // left
			Renderer::rectangle_filled(Vector2{ ScreenCenter.x , ScreenCenter.y - Menu::Vars::gap + 2 }, Vector2{ 2 , -Menu::Vars::length }, Menu::Vars::color_customcrosshair); // up
			Renderer::rectangle_filled(Vector2{ ScreenCenter.x , ScreenCenter.y + Menu::Vars::gap }, Vector2{ 2 , Menu::Vars::length }, Menu::Vars::color_customcrosshair); // down
		}

		if (Menu::Vars::visuals_targetplayerbelt && Globals::ShowMenu) {
			int w = 200, h = 102;

			belt::belt_tab_mov(Vector2(w, h + 20.0f));

			Renderer::rectangle_filled({ belt::pos.x, belt::pos.y }, Vector2(w, 20), ImColor(25, 25, 25, 140));
			Renderer::rectangle_filled(Vector2(belt::pos.x, belt::pos.y + 15.0f), Vector2(w, h), ImColor(36, 36, 36, 140));
			Renderer::rectangle_filled(Vector2(belt::pos.x + 3.0f, belt::pos.y + 20.0f + 5.0f), Vector2(w - 10, h - 10), ImColor(25, 25, 25, 140));
		}

		//if (Globals::ManipulatorData::IsManipulating) {
		//	Renderer::text({ ScreenCenter.x, ScreenCenter.y + 150 }, ImColor(173, 0, 0), 11.f, true, true, wxorstr_(L"[manipulating]"));
		//}

		auto local = LocalPlayer::Entity();
		if (local == nullptr) {
			target_ply = nullptr;
			return;
		}

		//if (Globals::ManipulatorData::IsManipulating) {

		//	//			Renderer::text({ screen_center.x, screen_center.y + 150 }, Color3(173, 0, 0), 11.f, true, true, wxorstr_(L"[Power Shoot]"));
		//	float desyncTime = (Time::realtimeSinceStartup() - local->lastSentTickTime()) - 0.03125 * 3;
		//	Renderer::rectangle_filled({ ScreenCenter.x - 950, ScreenCenter.y + 2 }, { 110, 5 }, D2D1::ColorF::LightPink);
		//	Renderer::rectangle_filled({ ScreenCenter.x - 950, ScreenCenter.y + 2 }, { 110 * (desyncTime), 5 }, RGBToImVec4(r, g, b, a));
		//	Renderer::text({ (ScreenCenter.x - 950) + (18 * 3), ScreenCenter.y - 10 }, RGBToImVec4(r, g, b, a), 12.f, true, true, wxorstr_(L"Manipulating"), (int)(desyncTime));
		//	//			Renderer::text({ (screen_center.x - 32) + (70 * (desyncTime)), screen_center.y + 27 }, Color3(255, 255, 255), 12.f, true, true, wxorstr_(L"%d"), (int)desyncTime);

		//}

		if (Menu::Vars::visuals_reloadind) {
			auto held = local->GetHeldEntity<BaseProjectile>();
			if (held) {
				if (held->HasReloadCooldown() && held->class_name_hash() != STATIC_CRC32("BowWeapon") && held->class_name_hash() != STATIC_CRC32("CompoundBowWeapon")) { // im sorry for my sins
					float time_left = held->nextReloadTime() - GLOBAL_TIME;
					float time_full = held->CalculateCooldownTime(held->nextReloadTime(), held->reloadTime()) - GLOBAL_TIME;

					Renderer::rectangle_filled({ ScreenCenter.x - 950, ScreenCenter.y + 30 }, { 110, 5 }, ImColor(0, 0, 0));
					Renderer::rectangle_filled({ ScreenCenter.x - 950, ScreenCenter.y + 30 }, { 110 * (time_left / time_full), 5 }, D2D1::ColorF::LightPink);
					Renderer::text({ (ScreenCenter.x - 950) + (18 * 3), ScreenCenter.y + 17 }, RGBToImVec4(r, g, b, a), 12.f, true, true, wxorstr_(L"Reloadíng"), (int)ceil(time_left));
					Renderer::text({ (ScreenCenter.x - 950) + (30 * (time_left / time_full)), ScreenCenter.y + 30 }, ImColor(255, 255, 255), 12.f, true, true, wxorstr_(L"%d"), (int)ceil(time_left));
				}
				if (held->class_name_hash() == STATIC_CRC32("BaseProjectile") ||
					held->class_name_hash() == STATIC_CRC32("BowWeapon") ||
					held->class_name_hash() == STATIC_CRC32("CompoundBowWeapon") ||
					held->class_name_hash() == STATIC_CRC32("BaseLauncher") ||
					held->class_name_hash() == STATIC_CRC32("CrossbowWeapon")) {
					if (held->Empty()) {
						Renderer::text({ ScreenCenter.x, ScreenCenter.y + 48 }, ImColor(89, 227, 255), 12.f, true, true, wxorstr_(L"[Weapon Empty]"));
					}
				}
			}
		}
		if (Menu::Vars::visuals_players ||
			Menu::Vars::visuals_ores ||
			Menu::Vars::visuals_stashes ||
			Menu::Vars::visuals_corpses ||
			Menu::Vars::visuals_traps ||
			Menu::Vars::visuals_hemp ||
			Menu::Vars::visuals_vehicles) {
			auto entityList = BaseNetworkable::clientEntities()->entityList();
			if (!entityList) {
				target_ply = nullptr;
				return;
			}

			if (entityList->vals->size <= 1) {
				target_ply = nullptr;
				return;
			}

			viewMatrix = Camera::getViewMatrix();

			if (target_ply != nullptr) {
				if (!target_ply->IsValid() || target_ply->health() <= 0 || target_ply->is_teammate() || target_ply->HasPlayerFlag(PlayerFlags::Sleeping) || entities::dfc(target_ply) > Menu::Vars::combat_aimfov || (target_ply->playerModel()->isNpc() && !Menu::Vars::visuals_npc)) {
					target_ply = nullptr;
				}
				else {
					if (target_ply->isCached()) {
						auto bounds = target_ply->bones()->bounds;
						if (!bounds.empty())
							if (Menu::Vars::TargetLine);
						Renderer::line({ bounds.left + ((bounds.right - bounds.left) / 2), bounds.bottom }, { ScreenCenter.x, ScreenSize.y }, ImColor(255, 255, 255), true);

						auto mpv = target_ply->find_mpv_bone();
						Bone* target;
						if (mpv != nullptr)
							target = mpv;
						else
							target = target_ply->bones()->head;

						if (target->visible)
							Renderer::boldtext({ ScreenCenter.x + 20, ScreenCenter.y - 20 }, ImColor(66, 135, 245), 12.f, true, true, wxorstr_(L"[s]"));

						Renderer::boldtext({ ScreenCenter.x - 20, ScreenCenter.y + 20 }, ImColor(255, 0, 0), 12.f, true, true, wxorstr_(L"[t]"));

						if (Menu::Vars::visuals_targetplayerbelt && !Globals::ShowMenu) {
							int w = 200, h = 102;

							belt::belt_tab_mov(Vector2(w, -20));

							Renderer::rectangle_filled({ belt::pos.x, belt::pos.y - 20.0f }, Vector2(w, 20), ImColor(25, 25, 25));
							Renderer::rectangle_filled(Vector2(belt::pos.x, belt::pos.y), Vector2(w, h), ImColor(36, 36, 36));
							Renderer::rectangle_filled(Vector2(belt::pos.x + 5.0f, belt::pos.y + 5.0f), Vector2(w - 10, h - 10), ImColor(25, 25, 25));

							Renderer::text({ belt::pos.x + 7.0f, belt::pos.y - 16.0f }, ImColor(r, g, b), 12.f, false, false, target_ply->_displayName());

							auto list = target_ply->inventory()->containerBelt()->itemList();
							if (list) {
								if (list->size) {
									int y = 0;
									for (int i = 0; i < list->size; i++) {
										auto item = (Item*)list->get(i);
										if (!item)
											continue;

										ImColor col = item->uid() == target_ply->clActiveItem() ? ImColor(255, 0, 0) : ImColor(255, 255, 255);

										Renderer::text({ belt::pos.x + 12.0f, belt::pos.y + 7.0f + y }, col, 12.f, false, false, wxorstr_(L"%s [x%d]"), item->info()->displayName()->english(), item->amount());

										y += 15;
									}
								}
							}
						}
					}
				}
			}

			for (int i = 0; i < entityList->vals->size; i++) {
				auto entity = *reinterpret_cast<BaseEntity**>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
				if (!entity) continue;

				if (!entity->IsValid()) continue;
				if (entity->class_name_hash() == STATIC_CRC32("BasePlayer") ||
					entity->class_name_hash() == STATIC_CRC32("NPCPlayerApex") ||
					entity->class_name_hash() == STATIC_CRC32("NPCMurderer") ||
					entity->class_name_hash() == STATIC_CRC32("NPCPlayer") ||
					entity->class_name_hash() == STATIC_CRC32("HumanNPC") ||
					entity->class_name_hash() == STATIC_CRC32("Scientist") ||
					entity->class_name_hash() == STATIC_CRC32("HTNPlayer") ||
					entity->class_name_hash() == STATIC_CRC32("HumanNPCNew") ||
					entity->class_name_hash() == STATIC_CRC32("HumanNPC") ||
					entity->class_name_hash() == STATIC_CRC32("ScientistNPCNew") ||
					entity->class_name_hash() == STATIC_CRC32("ScientistNPC") ||
					entity->class_name_hash() == STATIC_CRC32("TunnelDweller") ||
					entity->class_name_hash() == STATIC_CRC32("BanditGuard")) {
					if (!Menu::Vars::visuals_players && !Menu::Vars::visuals_sleepers) continue;
					auto player = reinterpret_cast<BasePlayer*>(entity);

					if (!player->isCached()) continue;
					if (player->health() <= 0.0f) continue;
					if (player->HasPlayerFlag(PlayerFlags::Sleeping) && !Menu::Vars::visuals_sleepers) continue;
					if (player->playerModel()->isNpc() && !Menu::Vars::visuals_npc) continue;
					if (player->userID() == LocalPlayer::Entity()->userID()) continue;

					auto bounds = player->bones()->bounds;
					if (!bounds.empty()) {
						int y_ = 0;
						int x_ = 10;

						float box_width = bounds.right - bounds.left;
						float box_height = bounds.bottom - bounds.top;
						float box_left = bounds.left - bounds.bottom;
						Vector2 footPos = { bounds.left + (box_width / 2), bounds.bottom + 20.47f };
						Vector2 headPos = { bounds.left + (box_width / 2), bounds.top - 9.54f };
						Vector2 left = { bounds.left + (box_width / 4), bounds.top + 0.0f };

						ImColor col = get_color(player);
						ImColor box_col = get_color(player, true);

						if (Menu::Vars::visuals_skeleton) {
							float dist = player->bones()->head->position.distance(local->bones()->head->position);
							if (dist < 60.f) {

								auto info = player->bones();

								auto head_b = info->head;
								auto spine4_b = info->spine4;
								auto l_upperarm_b = info->l_upperarm;
								auto l_forearm_b = info->l_forearm;
								auto l_hand_b = info->l_hand;
								auto r_upperarm_b = info->r_upperarm;
								auto r_forearm_b = info->r_forearm;
								auto r_hand_b = info->r_hand;
								auto pelvis_b = info->pelvis;
								auto l_hip_b = info->l_hip;
								auto l_knee_b = info->l_knee;
								auto l_foot_b = info->l_foot;
								auto r_hip_b = info->r_hip;
								auto r_knee_b = info->r_knee;
								auto r_foot_b = info->r_foot;
								auto r_toe_b = info->r_toe;
								auto l_toe_b = info->l_toe;

								Vector2 head, spine, l_upperarm, l_forearm, l_hand, r_upperarm, r_forearm, r_hand, pelvis, l_hip, l_knee, l_foot, r_hip, r_knee, r_foot, l_toe, r_toe;
								if (Camera::world_to_screen(head_b->position, head) &&
									Camera::world_to_screen(spine4_b->position, spine) &&
									Camera::world_to_screen(l_upperarm_b->position, l_upperarm) &&
									Camera::world_to_screen(l_forearm_b->position, l_forearm) &&
									Camera::world_to_screen(l_hand_b->position, l_hand) &&
									Camera::world_to_screen(r_upperarm_b->position, r_upperarm) &&
									Camera::world_to_screen(r_forearm_b->position, r_forearm) &&
									Camera::world_to_screen(r_hand_b->position, r_hand) &&
									Camera::world_to_screen(pelvis_b->position, pelvis) &&
									Camera::world_to_screen(l_hip_b->position, l_hip) &&
									Camera::world_to_screen(l_knee_b->position, l_knee) &&
									Camera::world_to_screen(l_foot_b->position, l_foot) &&
									Camera::world_to_screen(r_hip_b->position, r_hip) &&
									Camera::world_to_screen(r_knee_b->position, r_knee) &&
									Camera::world_to_screen(r_toe_b->position, r_toe) &&
									Camera::world_to_screen(l_toe_b->position, l_toe) &&
									Camera::world_to_screen(r_foot_b->position, r_foot)) {

									ImColor viscol = player->playerModel()->isNpc() ? ImColor(38, 255, 0) : ImColor(0, 250, 255);
									ImColor inviscol = player->playerModel()->isNpc() ? ImColor(22, 145, 0) : ImColor(0, 152, 156);

									if (player->HasPlayerFlag(PlayerFlags::Sleeping)) {
										viscol = Menu::Vars::color_sleeperskeletonvis;
										inviscol = Menu::Vars::color_sleeperskeletoninvis;
									}
									else if (!player->playerModel()->isNpc()) {
										viscol = Menu::Vars::color_playerskeletonvis;
										inviscol = Menu::Vars::color_playerskeletoninvis;
									}
									else {
										viscol = Menu::Vars::color_npcskeletonvis;
										inviscol = Menu::Vars::color_npcskeletoninvis;
									}

									Renderer::line(head, spine, (head_b->visible || spine4_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(spine, l_upperarm, (spine4_b->visible || l_upperarm_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(l_upperarm, l_forearm, (l_upperarm_b->visible || l_forearm_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(l_forearm, l_hand, (l_forearm_b->visible || l_hand_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(spine, r_upperarm, (spine4_b->visible || r_upperarm_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(r_upperarm, r_forearm, (r_upperarm_b->visible || r_forearm_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(r_forearm, r_hand, (r_forearm_b->visible || r_hand_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(spine, pelvis, (spine4_b->visible || pelvis_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(pelvis, l_hip, (pelvis_b->visible || l_hip_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(l_hip, l_knee, (l_hip_b->visible || l_knee_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(l_knee, l_foot, (l_knee_b->visible || l_foot_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(pelvis, r_hip, (pelvis_b->visible || r_hip_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(r_hip, r_knee, (r_hip_b->visible || r_knee_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(r_knee, r_foot, (r_knee_b->visible || r_foot_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(r_foot, r_toe, (r_foot_b->visible || r_toe_b->visible) ? viscol : inviscol, 3.f);
									Renderer::line(l_foot, l_toe, (l_foot_b->visible || l_toe_b->visible) ? viscol : inviscol, 3.f);
								}
							}
						}

						if (Menu::Vars::visuals_healthbar)
						{
							int health = player->health();
							float maxheal = (player->isNpc() ? player->maxHealth() : 100);
							const auto health_pc = min(health / maxheal, 1);
							const auto height = (bounds.left - bounds.right - bounds.bottom) * health_pc;
							Renderer::rectangle_filled(footPos + Vector2(0, y_) - Vector2(30, 0), { 60, 5 }, Color3(0, 0, 0, 2555));
							Renderer::rectangle_filled(footPos + Vector2(0, y_) - Vector2(30, 0), { 60 * (health / maxheal), 5 }, Color3(0, 255, 0));
							Renderer::rectangle(footPos + Vector2(0, y_) - Vector2(30, 0), { 60, 5 }, Color3(0, 0, 0, 255));
							//Renderer::text(footPos + Vector2(60 * (health / maxheal), y_), Color3(255, 255, 255), 8.f, true, true, wxorstr_(L"%d"), (int)health);
							//		Renderer::t({ (screen_center.x - 32) + (70 * (time_left / time_full)), screen_center.y + 79 }, Color3(255, 255, 255), 12.f, true, true, wxorstr_(L"[%.2f]"), time_left);
							y_ += 10;
						}

						Renderer::text(headPos, col, 12.f, true, true, wxorstr_(L"%s [%dhp]"), player->_displayName(), (int)ceil(player->health()));

						if (Menu::Vars::visuals_lookingdir && !player->HasPlayerFlag(PlayerFlags::Sleeping))
							Renderer::line(player->bones()->dfc, player->bones()->forward, Menu::Vars::color_playerlookingdir, true);

						if (Menu::Vars::visuals_box) {
							switch (Menu::Vars::visuals_boxtype) {
							case 0: // cornered
								Renderer::line({ bounds.left, bounds.top }, { bounds.left + (box_width / 3.5f), bounds.top }, box_col, true, 1.5f);
								Renderer::line({ bounds.right, bounds.top }, { bounds.right - (box_width / 3.5f), bounds.top }, box_col, true, 1.5f);

								Renderer::line({ bounds.left, bounds.bottom }, { bounds.left + (box_width / 3.5f), bounds.bottom }, box_col, true, 1.5f);
								Renderer::line({ bounds.right, bounds.bottom }, { bounds.right - (box_width / 3.5f), bounds.bottom }, box_col, true, 1.5f);

								Renderer::line({ bounds.left, bounds.top }, { bounds.left, bounds.top + (box_width / 3.5f) }, box_col, true, 1.5f);
								Renderer::line({ bounds.right, bounds.top }, { bounds.right, bounds.top + (box_width / 3.5f) }, box_col, true, 1.5f);

								Renderer::line({ bounds.left, bounds.bottom }, { bounds.left, bounds.bottom - (box_width / 3.5f) }, box_col, true, 1.5f);
								Renderer::line({ bounds.right, bounds.bottom }, { bounds.right, bounds.bottom - (box_width / 3.5f) }, box_col, true, 1.5f);
								break;
							case 1: // 2d
								Renderer::line({ bounds.left, bounds.top }, { bounds.right, bounds.top }, box_col, true, 1.5f);
								Renderer::line({ bounds.left, bounds.bottom }, { bounds.right, bounds.bottom }, box_col, true, 1.5f);

								Renderer::line({ bounds.left, bounds.top }, { bounds.left, bounds.bottom }, box_col, true, 1.5f);
								Renderer::line({ bounds.right, bounds.top }, { bounds.right, bounds.bottom }, box_col, true, 1.5f);
								break;
							case 2: // 3d (hippity hoppity your 3d box is now my property)
								CBounds bounds = CBounds();

								if (player->IsDucked()) {
									bounds.center = player->midPoint() + Vector3(0.0f, 0.55f, 0.0f);
									bounds.extents = Vector3(0.4f, 0.65f, 0.4f);
								}
								else {
									if (player->HasPlayerFlag(PlayerFlags::Wounded) || player->HasPlayerFlag(PlayerFlags::Sleeping)) {
										bounds.center = player->bones()->pelvis->position;
										bounds.extents = Vector3(0.9f, 0.2f, 0.4f);
									}
									else {
										bounds.center = player->midPoint() + Vector3(0.0f, 0.85f, 0.0f);
										bounds.extents = Vector3(0.4f, 0.9f, 0.4f);
									}
								}

								float y = math::euler_angles(player->bones()->eye_rot).y;
								Vector3 center = bounds.center;
								Vector3 extents = bounds.extents;
								Vector3 frontTopLeft = math::rotate_point(center, Vector3(center.x - extents.x, center.y + extents.y, center.z - extents.z), y);
								Vector3 frontTopRight = math::rotate_point(center, Vector3(center.x + extents.x, center.y + extents.y, center.z - extents.z), y);
								Vector3 frontBottomLeft = math::rotate_point(center, Vector3(center.x - extents.x, center.y - extents.y, center.z - extents.z), y);
								Vector3 frontBottomRight = math::rotate_point(center, Vector3(center.x + extents.x, center.y - extents.y, center.z - extents.z), y);
								Vector3 backTopLeft = math::rotate_point(center, Vector3(center.x - extents.x, center.y + extents.y, center.z + extents.z), y);
								Vector3 backTopRight = math::rotate_point(center, Vector3(center.x + extents.x, center.y + extents.y, center.z + extents.z), y);
								Vector3 backBottomLeft = math::rotate_point(center, Vector3(center.x - extents.x, center.y - extents.y, center.z + extents.z), y);
								Vector3 backBottomRight = math::rotate_point(center, Vector3(center.x + extents.x, center.y - extents.y, center.z + extents.z), y);

								Vector2 frontTopLeft_2d, frontTopRight_2d, frontBottomLeft_2d, frontBottomRight_2d, backTopLeft_2d, backTopRight_2d, backBottomLeft_2d, backBottomRight_2d;
								if (Camera::world_to_screen(frontTopLeft, frontTopLeft_2d) &&
									Camera::world_to_screen(frontTopRight, frontTopRight_2d) &&
									Camera::world_to_screen(frontBottomLeft, frontBottomLeft_2d) &&
									Camera::world_to_screen(frontBottomRight, frontBottomRight_2d) &&
									Camera::world_to_screen(backTopLeft, backTopLeft_2d) &&
									Camera::world_to_screen(backTopRight, backTopRight_2d) &&
									Camera::world_to_screen(backBottomLeft, backBottomLeft_2d) &&
									Camera::world_to_screen(backBottomRight, backBottomRight_2d)) {

									Renderer::line(frontTopLeft_2d, frontTopRight_2d, box_col, true, 1.5f);
									Renderer::line(frontTopRight_2d, frontBottomRight_2d, box_col, true, 1.5f);
									Renderer::line(frontBottomRight_2d, frontBottomLeft_2d, box_col, true, 1.5f);
									Renderer::line(frontBottomLeft_2d, frontTopLeft_2d, box_col, true, 1.5f);
									Renderer::line(backTopLeft_2d, backTopRight_2d, box_col, true, 1.5f);
									Renderer::line(backTopRight_2d, backBottomRight_2d, box_col, true, 1.5f);
									Renderer::line(backBottomRight_2d, backBottomLeft_2d, box_col, true, 1.5f);
									Renderer::line(backBottomLeft_2d, backTopLeft_2d, box_col, true, 1.5f);
									Renderer::line(frontTopLeft_2d, backTopLeft_2d, box_col, true, 1.5f);
									Renderer::line(frontTopRight_2d, backTopRight_2d, box_col, true, 1.5f);
									Renderer::line(frontBottomRight_2d, backBottomRight_2d, box_col, true, 1.5f);
									Renderer::line(frontBottomLeft_2d, backBottomLeft_2d, box_col, true, 1.5f);

									Vector2 tempFeetR, tempFeetL;

									Vector2 tempHead;


									Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
									float Entity_h = tempHead.y - tempFeet.y;
									float w = Entity_h / 4;
									float Entity_x = tempFeet.x - w;
									float Entity_y = tempFeet.y;
									float Entity_w = Entity_h / 2;
								}
								break;
							}
						}

						if (player->GetHeldItem() && !player->HasPlayerFlag(PlayerFlags::Sleeping)) {
							Renderer::text(footPos, col, 12.f, true, true, player->GetHeldItem()->info()->displayName()->english());
							y_ += 16;
						}
						if (player->HasPlayerFlag(PlayerFlags::Wounded)) {
							Renderer::boldtext(footPos + Vector2(0, y_), ImColor(255, 0, 0, 200), 12.f, true, true, wxorstr_(L"*wounded*"));
							y_ += 16;
						}


						//if (Menu::Vars::InvisiblePlayerIndicator);
						//{
						//	Renderer::InvisiblePlayerIndicator(LocalPosition, RGBToImVec4(255, 0, 0));
						//}

						if (!player->is_teammate() && !player->HasPlayerFlag(PlayerFlags::Sleeping)) {
							if (dfc(player) <= Menu::Vars::combat_aimfov) {
								if (target_ply == nullptr)
									target_ply = player;
								else
									if (dfc(target_ply) >= dfc(player))
										target_ply = player;
							}
						}
					}
				}

				if (entity->class_name_hash() == STATIC_CRC32("OreResourceEntity") && Menu::Vars::visuals_ores) {
					if (entity->ShortPrefabName_hash() == STATIC_CRC32("stone-ore") ||
						entity->ShortPrefabName_hash() == STATIC_CRC32("sulfur-ore") ||
						entity->ShortPrefabName_hash() == STATIC_CRC32("metal-ore")) {
						Vector2 screen;
						if (Camera::world_to_screen(entity->transform()->position(), screen)) {
							switch (entity->ShortPrefabName_hash()) {
							case STATIC_CRC32("stone-ore"):
								Renderer::text(screen, Menu::Vars::color_ores, 12.f, true, true, wxorstr_(L"Stone Ore"));
								break;
							case STATIC_CRC32("sulfur-ore"):
								Renderer::text(screen, Menu::Vars::color_ores, 12.f, true, true, wxorstr_(L"Sulfur Ore"));
								break;
							case STATIC_CRC32("metal-ore"):
								Renderer::text(screen, Menu::Vars::color_ores, 12.f, true, true, wxorstr_(L"Metal Ore"));
								break;
							}
						}
					}
				}
				if (entity->ShortPrefabName_hash() == STATIC_CRC32("small_stash_deployed") && Menu::Vars::visuals_stashes) {
					Vector2 screen;
					if (Camera::world_to_screen(entity->transform()->position(), screen)) {
						if (entity->HasFlag(BaseEntity::Flags::Reserved5)) {
							Renderer::text(screen, Menu::Vars::color_stashes, 12.f, true, true, wxorstr_(L"Stash (Hidden)"));
						}
						else {
							Renderer::text(screen, Menu::Vars::color_stashes, 12.f, true, true, wxorstr_(L"Stash"));
						}
					}

				}
				if (entity->ShortPrefabName_hash() == STATIC_CRC32("patrolhelicopter") && Menu::Vars::HeliEsp)
				{

					auto patrol = reinterpret_cast<BasePlayer*>(entity);
					Vector2 screen;
					if (Camera::world_to_screen(entity->transform()->position(), screen)) {
						float distance = LocalPlayer::Entity()->bones()->l_foot->position.distance(entity->transform()->position());
						Renderer::text(screen, Menu::Vars::HeliEsp_Color, 12.f, true, true, wxorstr_(L"Patrol Helicopter [%1.0fm] [%dhp]"), distance, patrol->health());
					}
				}
				if ((entity->ShortPrefabName_hash() == STATIC_CRC32("rhib") ||
					entity->ShortPrefabName_hash() == STATIC_CRC32("rowboat") ||
					entity->ShortPrefabName_hash() == STATIC_CRC32("hotairballoon") ||
					entity->ShortPrefabName_hash() == STATIC_CRC32("minicopter.entity") ||
					entity->ShortPrefabName_hash() == STATIC_CRC32("scraptransporthelicopter") ||
					entity->ShortPrefabName_hash() == STATIC_CRC32("submarineduo.entity") ||
					entity->ShortPrefabName_hash() == STATIC_CRC32("submarinesolo.entity") ||
					entity->ShortPrefabName_hash() == STATIC_CRC32("testridablehorse")) && Menu::Vars::visuals_vehicles) {
					Vector2 screen;
					if (Camera::world_to_screen(entity->transform()->position(), screen)) {
						switch (entity->ShortPrefabName_hash()) {
						case STATIC_CRC32("rhib"):
							Renderer::text(screen, Menu::Vars::color_vehicles, 12.f, true, true, wxorstr_(L"RHIB"));
							break;
						case STATIC_CRC32("rowboat"):
							Renderer::text(screen, Menu::Vars::color_vehicles, 12.f, true, true, wxorstr_(L"Boat"));
							break;
						case STATIC_CRC32("hotairballoon"):
							Renderer::text(screen, Menu::Vars::color_vehicles, 12.f, true, true, wxorstr_(L"Hot Air Balloon"));
							break;
						case STATIC_CRC32("minicopter.entity"):
							Renderer::text(screen, Menu::Vars::color_vehicles, 12.f, true, true, wxorstr_(L"Minicopter"));
							break;
						case STATIC_CRC32("scraptransporthelicopter"):
							Renderer::text(screen, Menu::Vars::color_vehicles, 12.f, true, true, wxorstr_(L"Scrap Heli"));
							break;
						case STATIC_CRC32("testridablehorse"):
							Renderer::text(screen, Menu::Vars::color_vehicles, 12.f, true, true, wxorstr_(L"Horse"));
							break;
						case STATIC_CRC32("submarineduo.entity"):
							Renderer::text(screen, Menu::Vars::color_vehicles, 12.f, true, true, wxorstr_(L"Submarine (Duo)"));
							break;
						case STATIC_CRC32("submarinesolo.entity"):
							Renderer::text(screen, Menu::Vars::color_vehicles, 12.f, true, true, wxorstr_(L"Submarine (Solo)"));
							break;
						}
					}
				}
				if (entity->ShortPrefabName_hash() == STATIC_CRC32("hemp-collectable") && Menu::Vars::visuals_hemp) {
					Vector2 screen;
					if (Camera::world_to_screen(entity->transform()->position(), screen)) {
						Renderer::text(screen, Menu::Vars::color_hemp, 12.f, true, true, wxorstr_(L"Hemp"));
					}

				}
				if ((entity->class_name_hash() == STATIC_CRC32("PlayerCorpse") ||
					entity->class_name_hash() == STATIC_CRC32("NPCPlayerCorpse")) && Menu::Vars::visuals_corpses) {
					Vector2 screen;
					if (Camera::world_to_screen(entity->transform()->position(), screen)) {
						Renderer::text(screen, Menu::Vars::color_corpses, 12.f, true, true, wxorstr_(L"Corpse"));
					}
				}
				if ((entity->class_name_hash() == STATIC_CRC32("AutoTurret") ||
					entity->class_name_hash() == STATIC_CRC32("Landmine") ||
					entity->class_name_hash() == STATIC_CRC32("BearTrap") ||
					entity->class_name_hash() == STATIC_CRC32("SamSite") ||
					entity->class_name_hash() == STATIC_CRC32("GunTrap")) && Menu::Vars::visuals_traps) {
					Vector2 screen;
					if (Camera::world_to_screen(entity->transform()->position(), screen)) {
						switch (entity->class_name_hash()) {
						case STATIC_CRC32("AutoTurret"):
							Renderer::text(screen, Menu::Vars::color_traps, 12.f, true, true, wxorstr_(L"Auto Turret"));
							break;
						case STATIC_CRC32("Landmine"):
							Renderer::text(screen, Menu::Vars::color_traps, 12.f, true, true, wxorstr_(L"Landmine"));
							break;
						case STATIC_CRC32("BearTrap"):
							Renderer::text(screen, Menu::Vars::color_traps, 12.f, true, true, wxorstr_(L"Bear Trap"));
							break;
						case STATIC_CRC32("SamSite"):
							Renderer::text(screen, Menu::Vars::color_traps, 12.f, true, true, wxorstr_(L"SAM Site"));
							break;
						case STATIC_CRC32("GunTrap"):
							Renderer::text(screen, Menu::Vars::color_traps, 12.f, true, true, wxorstr_(L"Shotgun Trap"));
							break;
						}
					}
				}
			}
		}
		else {
			if (target_ply != nullptr)
				target_ply = nullptr;
		}
	}
}
void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b)
{
	if (s == 0.0f)
	{
		// gray
		out_r = out_g = out_b = v;
		return;
	}

	h = fmodf(h, 1.0f) / (60.0f / 360.0f);
	int   i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i)
	{
	case 0: out_r = v; out_g = t; out_b = p; break;
	case 1: out_r = q; out_g = v; out_b = p; break;
	case 2: out_r = p; out_g = v; out_b = t; break;
	case 3: out_r = p; out_g = q; out_b = v; break;
	case 4: out_r = t; out_g = p; out_b = v; break;
	case 5: default: out_r = v; out_g = p; out_b = q; break;
	}
}

Color hsv(float h, float s, float v, float a = 1.0f) { float r, g, b; ColorConvertHSVtoRGB(h, s, v, r, g, b); return Color(r, g, b, a); }
