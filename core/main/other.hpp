namespace other {
	Vector3 m_manipulate = Vector3::Zero();

	void find_manipulate_angle() {
		auto loco = LocalPlayer::Entity();
		Vector3 re_p = loco->transform()->position() + loco->transform()->up() * (PlayerEyes::EyeOffset().y + loco->eyes()->viewOffset().y);
		// real eye pos

		Vector3 choice = Vector3::Zero();

		if (GamePhysics::IsVisible(re_p, target_ply->find_mpv_bone()->position) || !target_ply->isCached()) {
			m_manipulate = Vector3::Zero();
			return;
		}

		float desyncTime = (Time::realtimeSinceStartup() - loco->lastSentTickTime()) - 0.03125 * 3;
		float mm_max_eye = (1.0f + ((desyncTime + 2.f / 5.f + 0.125f) * 2.5f) * loco->MaxVelocity()) - 0.05f;

		auto right = loco->eyes()->MovementRight();
		auto forward = loco->eyes()->MovementForward();
		auto position = loco->eyes()->position();
		auto BodyForward = loco->eyes()->BodyForward();
		auto rotation = loco->eyes()->rotation();
		Ray BodyRay = loco->eyes()->BodyRay();

		std::array<Vector3, 12> arr = {
			Vector3(right.x * (mm_max_eye / 2), 0.f, right.z * (mm_max_eye / 2)), // small right
			Vector3(right.x * mm_max_eye, 0.f, right.z * mm_max_eye), // big right

			Vector3(-(right.x * (mm_max_eye / 2)), 0.f, -(right.z * (mm_max_eye / 2))), // small left
			Vector3(-(right.x * mm_max_eye), 0.f, -(right.z * mm_max_eye)), // big left

			Vector3(0.f, (mm_max_eye / 2), 0.f), // small up
			Vector3(0.f, mm_max_eye, 0.f), // big up

			Vector3(forward.x * (mm_max_eye / 2), 0.f, forward.z * (mm_max_eye / 2)), // small forward
			Vector3(forward.x * mm_max_eye, 0.f, forward.z * mm_max_eye), // big forward

			Vector3(0.f, (1.4f / 2), 0.f), // small up
			Vector3(0.f, 1.4f, 0.f), // big up

			Vector3(0.f, -(1.4f / 2), 0.f), // small down
			Vector3(0.f, -1.4f, 0.f), // big down
		};

		for (auto s : arr) {
			Vector3 point = re_p + s;

			if (!GamePhysics::IsVisible(point, re_p))
				continue;

			if (!GamePhysics::IsVisible(re_p, point))
				continue;

			choice = s;
			break;
		}
		if (choice.empty()) {
			m_manipulate = Vector3::Zero();
			return;
		}

		m_manipulate = choice;
	}
	void test_bundle(AssetBundle* bundle) {
		if (!bundle) {
			std::cout << "bundle nfound\n";
			return;
		}

		auto arr = bundle->GetAllAssetNames();
		if (!arr) {
			std::cout << "arr nfound\n";
			return;
		}

		for (int j = 0; j < arr->ArraySize(); j++) {
			auto name = arr->GetArray(j);

			printf("%ls\n", name->buffer);
		}

		std::cout << "bundletest - success\n";
	}
}
void dispatch_keybind(KeyCode& s) {

}
//TestFly();
//float num5 = max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
//float num6 = loco.player->GetJumpHeight() + num5;
//Menu::Vars::misc::max_flyhack = num6;
//if (flyhackDistanceVertical <= num6) {
//	vars::fly::flyhack = flyhackDistanceVertical;
//}
//
//float num7 = max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
//float num8 = 5.f + num7;
//vars::misc::max_hor_flyhack = num8;
//if (flyhackDistanceHorizontal <= num8) {
//	vars::fly::hor_flyhack = flyhackDistanceHorizontal;
//}
//if (flyhackDistanceVertical > num6) {
//	loco.player->movement()->groundAngle(Vector3::Zero());
//	loco.player->movement()->groundAngleNew(Vector3::Zero());
//	loco.player->movement()->TargetMovementk__BackingField(Vector3::Zero());
//	loco.player->get_transform()->set_position(loco.player->get_transform()->position() - Vector3(0, 0.3, 0));
//}
//else {}
//
//if (flyhackDistanceHorizontal > num8) {
//	loco.player->movement()->groundAngle(Vector3::Zero());
//	loco.player->movement()->groundAngleNew(Vector3::Zero());
//	loco.player->movement()->TargetMovementk__BackingField(Vector3::Zero());
//	loco.player->get_transform()->set_position(loco.player->get_transform()->position() - Vector3(0, 0.2, 0));
//}
//else {}