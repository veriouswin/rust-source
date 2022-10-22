namespace bonecache {
	box_bounds get_bounds(BasePlayer* player, float expand = 0) {
		box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };

		for (auto j : valid_bones) {
			auto arr = player->model()->boneTransforms();
			if (arr) {
				auto transform = player->model()->boneTransforms()->GetArray(j);
				if (transform) {
					Vector2 sc;
					auto world_pos = transform->position();

					if (j == 48)
						world_pos.y += 0.2f;

					if (Camera::world_to_screen(world_pos, sc)) {
						Vector2 bone_screen = sc;

						if (bone_screen.x < ret.left)
							ret.left = bone_screen.x;
						if (bone_screen.x > ret.right)
							ret.right = bone_screen.x;
						if (bone_screen.y < ret.top)
							ret.top = bone_screen.y;
						if (bone_screen.y > ret.bottom)
							ret.bottom = bone_screen.y;
					}
				}
			}
		}

		if (ret.left == FLT_MAX)
			return box_bounds::null();
		if (ret.right == FLT_MIN)
			return box_bounds::null();
		if (ret.top == FLT_MAX)
			return box_bounds::null();
		if (ret.bottom == FLT_MIN)
			return box_bounds::null();

		ret.left -= expand;
		ret.right += expand;
		ret.top -= expand;
		ret.bottom += expand;

		return ret;
	};
	void Chams(BasePlayer* player)
	{
		static int cases = 0;
		static float r = 1.00f, g = 0.00f, b = 1.00f;
		switch (cases) {
		case 0: { r -= 0.0004f; if (r <= 0) cases += 1; break; }
		case 1: { g += 0.0004f; b -= 0.0004f; if (g >= 1) cases += 1; break; }
		case 2: { r += 0.0004f; if (r >= 1) cases += 1; break; }
		case 3: { b += 0.0004f; g -= 0.0004f; if (b >= 1) cases = 0; break; }
		default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
		}
		if (Menu::Vars::visuals_chams) {
			Shader* chamsShader = nullptr;
			if (player->playerModel()->_multiMesh()->Renderers()) {
				List<Renderer_*>* renderers = player->playerModel()->_multiMesh()->Renderers();

				if (!player) return;
				if (player->health() <= 5.0f || player->lifestate() == BaseCombatEntity::Lifestate::Dead) return;

				if (!player->playerModel()) return;
				if (!player->playerModel()->_multiMesh()) return;
				if (!player->playerModel()->_multiMesh()->Renderers()) return;



				for (int i = 0; i < renderers->size; i++)
				{
					Renderer_* renderer = reinterpret_cast<Renderer_*>(renderers->get(i));
					if (!renderer) continue;
					if (!renderer->material()) continue;

					if (chamsShader == nullptr)
						chamsShader = renderer->material()->shader()->Find((char*)"Hidden/InternalErrorShader");
					else
						renderer->material()->set_shader(chamsShader);

					renderer->material()->SetColor((char*)"_Color", Color(r, g, b, 8));

					//renderer->material()->SetColor("_Color", Color(Menu::Color::ChamColor[0], Menu::Color::ChamColor[1], Menu::Color::ChamColor[2], Menu::Color::ChamColor[3]));
				}




			}
		}
	}
	//void Chams(BasePlayer* player)
	//{
	//	static int cases = 0;
	//	static float r = 1.00f, g = 0.00f, b = 1.00f;
	//	switch (cases) {
	//	case 0: { r -= 0.0004f; if (r <= 0) cases += 1; break; }
	//	case 1: { g += 0.0004f; b -= 0.0004f; if (g >= 1) cases += 1; break; }
	//	case 2: { r += 0.0004f; if (r >= 1) cases += 1; break; }
	//	case 3: { b += 0.0004f; g -= 0.0004f; if (b >= 1) cases = 0; break; }
	//	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	//	}
	//	if (Menu::Vars::visuals_chamsglow) {
	//		Shader* chamsShader = nullptr;
	//		if (player->playerModel()->_multiMesh()->Renderers()) {
	//			List<Renderer_*>* renderers = player->playerModel()->_multiMesh()->Renderers();

	//			if (!player) return;
	//			if (player->health() <= 5.0f || player->lifestate() == BaseCombatEntity::Lifestate::Dead) return;

	//			if (!player->playerModel()) return;
	//			if (!player->playerModel()->_multiMesh()) return;
	//			if (!player->playerModel()->_multiMesh()->Renderers()) return;



	//			for (int i = 0; i < renderers->size; i++)
	//			{
	//				Renderer_* renderer = reinterpret_cast<Renderer_*>(renderers->get(i));
	//				if (!renderer) continue;
	//				if (!renderer->material()) continue;

	//				if (chamsShader == nullptr)
	//					chamsShader = renderer->material()->shader()->Find((char*)"Hidden/Internal-Colored");
	//				else
	//					renderer->material()->set_shader(chamsShader);

	//				renderer->material()->SetColor((char*)"_Color", Color(r, g, b, 0));

	//				renderer->material()->SetColor("_Color", Color(Menu::Color::ChamColor[0], Menu::Color::ChamColor[1], Menu::Color::ChamColor[2], Menu::Color::ChamColor[3]));
	//			}




	//		}
	//	}
	//}

	void cachePlayer(BasePlayer* player) {
		auto model = player->model();
		if (model) {
			auto cache = new BoneCache();

			cache->head = model->resolve(STATIC_CRC32("head"));
			cache->neck = model->resolve(STATIC_CRC32("neck"));
			cache->spine4 = model->resolve(STATIC_CRC32("spine4"));
			cache->spine1 = model->resolve(STATIC_CRC32("spine1"));
			cache->l_upperarm = model->resolve(STATIC_CRC32("l_upperarm"));
			cache->l_forearm = model->resolve(STATIC_CRC32("l_forearm"));
			cache->l_hand = model->resolve(STATIC_CRC32("l_hand"));
			cache->r_upperarm = model->resolve(STATIC_CRC32("r_upperarm"));
			cache->r_forearm = model->resolve(STATIC_CRC32("r_forearm"));
			cache->r_hand = model->resolve(STATIC_CRC32("r_hand"));
			cache->pelvis = model->resolve(STATIC_CRC32("pelvis"));
			cache->l_hip = model->resolve(STATIC_CRC32("l_hip"));
			cache->l_knee = model->resolve(STATIC_CRC32("l_knee"));
			cache->l_foot = model->resolve(STATIC_CRC32("l_foot"));
			cache->r_hip = model->resolve(STATIC_CRC32("r_hip"));
			cache->r_knee = model->resolve(STATIC_CRC32("r_knee"));
			cache->r_foot = model->resolve(STATIC_CRC32("r_foot"));
			cache->r_toe = model->resolve(STATIC_CRC32("r_toe"));
			cache->l_toe = model->resolve(STATIC_CRC32("l_toe"));

			if (player->userID() != LocalPlayer::Entity()->userID()) {
				box_bounds bo = get_bounds(player, 2.f);
				if (!bo.empty())
					cache->bounds = bo;

				Vector2 footPos;
				if (Camera::world_to_screen(cache->head->position, footPos))
					cache->dfc = footPos;

				Vector2 forwardd;
				if (Camera::world_to_screen(cache->head->position + (player->eyes()->BodyForward() * 2), forwardd)) {
					cache->forward = forwardd;
				}

				auto mpv = player->find_mpv_bone();
				Vector3 target;
				if (mpv != nullptr)
					target = mpv->position;
				else
					target = player->bones()->head->position;

				cache->eye_rot = player->eyes()->rotation();
			}
			Chams(player);

			if (!MapContainsKey(cachedBones, player->userID()))
				cachedBones.insert(std::make_pair(player->userID(), cache));
			else
				cachedBones[player->userID()] = cache;
		}
	}
}
bool play_sound(const char* name) {
	return PlaySoundA(name, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
}