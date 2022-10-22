#include <intrin.h>
#define CALLED_BY(func,off) (reinterpret_cast<std::uint64_t>(_ReturnAddress()) > func && reinterpret_cast<std::uint64_t>(_ReturnAddress()) < func + off)



void ClientUpdate_hk(BasePlayer* player) {
	__try {
		auto local = LocalPlayer::Entity();
		if (local) {
			if (Menu::Vars::visuals_players || Menu::Vars::visuals_sleepers) {
				bonecache::cachePlayer(player);
			}
		}
		return player->ClientUpdate();
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}

void ClientUpdate_Sleeping_hk(BasePlayer* player)
{
	__try {
		auto local = LocalPlayer::Entity();
		if (local) {
			if (Menu::Vars::visuals_players || Menu::Vars::visuals_sleepers) {
				bonecache::cachePlayer(player);
			}
		}

		return player->ClientUpdate_Sleeping();
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}

void LaunchProjectile(BaseProjectile* pr)
{

	 return BaseProjectile::LaunchProjectile_(pr);
}
Vector3 GetModifiedAimConeDirection_hk(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
	__try {
		auto mpv = target_ply->find_mpv_bone();
		Vector3 target;
		if (mpv != nullptr)
			target = mpv->position;
		else
			target = target_ply->bones()->head->position;

		if (Menu::Vars::combat_psilent && target_ply != nullptr && target_ply->isCached() && GamePhysics::IsVisible(target, LocalPlayer::Entity()->eyes()->position())) {
			inputVec = (aimutils::get_prediction() - LocalPlayer::Entity()->eyes()->position()).normalized();
		}


		aimCone *= Menu::Vars::combat_spread / 100.0f;

		return AimConeUtil::GetModifiedAimConeDirection(aimCone, inputVec, anywhereInside);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
Attack* BuildAttackMessage_hk(HitTest* self) {
	__try {
		auto ret = self->BuildAttackMessage();
		auto entity = BaseNetworkable::clientEntities()->Find<BasePlayer*>(ret->hitID());

		if (Menu::Vars::combat_alwaysheliweak)
		{
			if (entity->class_name_hash() == STATIC_CRC32("BaseHelicopter"))
			{
				if (entity->health() <= 5000.0f)
					ret->hitBone() = StringPool::Get(xorstr_("tail_rotor_col"));
				else
					ret->hitBone() = StringPool::Get(xorstr_("engine_col"));
			}
		}


		auto localPlayer = LocalPlayer::Entity();
		if (localPlayer) {

			if (reinterpret_cast<BasePlayer*>(self->ignoreEntity())->userID() == localPlayer->userID()) { // isAuthoritative
				if (Menu::Vars::misc_bullettracers) {
					DDraw::Line(localPlayer->eyes()->position(), ret->hitPositionWorld(), Color(1, 0, 0, 1), 1.5f, false, true);
				}

				if (entity) {
					if (entity->IsPlayer()) {
						if (entity->isCached()) {
							if (localPlayer->isCached()) {
								if (Menu::Vars::combat_bigbullets) {
									auto bone = entity->model()->find_bone(ret->hitPositionWorld());
									if (bone.second) {
										ret->hitPositionWorld() = bone.first->position();
									}
								}

								if (Menu::Vars::combat_hitboxoverride)
									ret->hitBone() = StringPool::Get(xorstr_("head"));
								else {
									int num = rand() % 100;
									if (num > 90)
										ret->hitBone() = StringPool::Get(xorstr_("head"));
									else if (num < 90 && num > 80)
										ret->hitBone() = StringPool::Get(xorstr_("neck"));
									else if (num < 80 && num > 70)
										ret->hitBone() = StringPool::Get(xorstr_("l_clavicle"));
									else if (num < 70 && num > 60)
										ret->hitBone() = StringPool::Get(xorstr_("pelvis"));
									else if (num < 60 && num > 50)
										ret->hitBone() = StringPool::Get(xorstr_("r_hip"));
									else if (num < 50 && num > 40)
										ret->hitBone() = StringPool::Get(xorstr_("r_foot"));
									else if (num < 40 && num > 30)
										ret->hitBone() = StringPool::Get(xorstr_("spine1"));
									else if (num < 30 && num > 20)
										ret->hitBone() = StringPool::Get(xorstr_("l_hand"));
									else if (num < 20 && num > 10)
										ret->hitBone() = StringPool::Get(xorstr_("r_upperarm"));
									else if (num < 10)
										ret->hitBone() = StringPool::Get(xorstr_("l_knee"));
									else
										ret->hitBone() = StringPool::Get(xorstr_("spine4"));
								}
							}
						}
					}
				}
			}
		}

		return ret;
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void DoAttack_hk(FlintStrikeWeapon* weapon) {
	__try {
		if (Menu::Vars::combat_instaeoka)
			weapon->_didSparkThisFrame() = true;

		return weapon->DoAttack();
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
Vector3 BodyLeanOffset_hk(PlayerEyes* a1) {
	__try {
		if (Menu::Vars::combat_manipulator && GKey(Menu::Vars::combat_manipulator_bind)) {
			if (target_ply != nullptr) {
				if (other::m_manipulate.empty() || !LocalPlayer::Entity()->GetHeldEntity())
					return a1->BodyLeanOffset();

				return other::m_manipulate;
			}
		}

		return a1->BodyLeanOffset();
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void DoFirstPersonCamera_hk(PlayerEyes* a1, Component* cam) {
	__try {
		a1->DoFirstPersonCamera(cam);
		if (Menu::Vars::combat_manipulator) {
			Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);
			cam->transform()->set_position(re_p);
		}
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
bool CanAttack_hk(BasePlayer* self) {
	__try {
		if (Menu::Vars::misc_noattackres)
			return true;

		return self->CanAttack();
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
//static bool IsSpeeding(BasePlayer* ply, TickInterpolator ticks, float deltaTime)
//{
//	float speedhackDistance{};
//	float speedhackPauseTime{};
//	bool result;
//
//	speedhackPauseTime = std::max(0.0f, speedhackPauseTime - deltaTime);
//	bool flag = ply->transform()->position();
//	Matrix matrix4x = ply->transform()->get_localToWorldMatrix();
//	Vector3 vector = flag ? ticks.StartPoint : matrix4x.MultiplyPoint3x4(ticks.StartPoint);
//	Vector3 a = flag ? ticks.EndPoint : matrix4x.MultiplyPoint3x4(ticks.EndPoint);
//	float running = 1.0f;
//	float ducking = 0.0f;
//	float crawling = 0.0f;
//
//	bool flag2 = ply->IsRunning();
//	bool flag3 = ply->IsDucked();
//	bool flag4 = ply->IsSwimming();
//	bool flag5 = ply->IsCrawling();
//	running = (flag2 ? 1.0f : 0.0f);
//	ducking = ((flag3 || flag4) ? 1.0f : 0.0f);
//	crawling = (flag5 ? 1.0f : 0.0f);
//
//	float speed = ply->GetSpeed(running, ducking, crawling);
//	Vector3 v = a - vector;
//	float num = v.magnitude();
//	float num2 = deltaTime * speed;
//
//	float num4 = std::max((speedhackPauseTime > 0.0f) ? 10.0f : 2.0f, 0.1f);
//	float num5 = num4 + std::max(2.0f, 0.1f);
//	speedhackDistance = std::clamp(speedhackDistance, -num5, num5);
//	speedhackDistance = std::clamp(speedhackDistance - num2, -num5, num5);
//	if (speedhackDistance > num4)
//	{
//		result = true;
//	}
//	else
//	{
//		speedhackDistance = std::clamp(speedhackDistance + num, -num5, num5);
//		if (speedhackDistance > num4)
//		{
//			result = true;
//		}
//		else
//		{
//			result = false;
//		}
//	}
//	return result;
//}
void UpdateVelocity_hk(PlayerWalkMovement* self) {
	BasePlayer* ply = LocalPlayer::Entity();

	if (!self->flying()) {
		Vector3 vel = self->TargetMovement();
		if (Menu::Vars::misc_nosprintres) {
			float max_speed = (self->swimming() || self->Ducking() > 0.5) ? 1.7f : 5.78f;
			if (vel.length() > 0.f) {
				Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
				self->TargetMovement() = target_vel;
			}
		}
		if (Menu::Vars::combat_manipulator && GKey(Menu::Vars::combat_manipulator_bind)) {
			float max_speed = (self->swimming() || self->Ducking() > 0.5) ? 1.7f : 5.5f;
			if (vel.length() > 0.f) {
				self->TargetMovement() = Vector3::Zero();
			}
		}
	}

	return self->UpdateVelocity();
}

Vector3 EyePositionForPlayer_hk(BaseMountable* mount, BasePlayer* player, Quaternion lookRot) {
	__try {
		if (player->userID() == LocalPlayer::Entity()->userID()) {
			if (Menu::Vars::combat_manipulator && GKey(Menu::Vars::combat_manipulator_bind)) {
				return mount->EyePositionForPlayer(player, lookRot) + other::m_manipulate;
			}
		}

		return mount->EyePositionForPlayer(player, lookRot);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void HandleJumping_hk(PlayerWalkMovement* a1, ModelState* state, bool wantsJump, bool jumpInDirection = false) {
	__try {
		if (Menu::Vars::misc_nojumpres) {
			if (!wantsJump)
				return;

			a1->grounded() = (a1->climbing() = (a1->sliding() = false));
			state->set_ducked(false);
			a1->jumping() = true;
			state->set_jumped(true);
			a1->jumpTime() = Time::time();
			a1->ladder() = nullptr;

			Vector3 curVel = a1->body()->velocity();
			a1->body()->set_velocity({ curVel.x, 10, curVel.z });
			return;
		}

		return a1->HandleJumping(state, wantsJump, jumpInDirection);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void OnLand_hk(BasePlayer* ply, float vel) {
	__try {
		if (!Menu::Vars::misc_nofalldmg)
			ply->OnLand(vel);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
bool IsDown_hk(InputState* self, BUTTON btn) {
	__try {
		if (Menu::Vars::combat_autoshoot || (Menu::Vars::combat_manipulator && GKey(Menu::Vars::combat_manipulator_bind))) {
			if (btn == BUTTON::FIRE_PRIMARY) {
				auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
				if (held && !held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
					if (target_ply != nullptr && target_ply->isCached()) {
						auto mpv = target_ply->find_mpv_bone();
						Vector3 target;
						if (mpv != nullptr)
							target = mpv->position;
						else
							target = target_ply->bones()->head->position;

						if (GamePhysics::IsVisible(target, LocalPlayer::Entity()->eyes()->position()))
							return true;
					}
				}
			}
		}

		return self->IsDown(btn);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void OnAttacked_hk(BaseCombatEntity* self, HitInfo* info) {
	__try {
		self->OnAttacked(info);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}

void NiggaDoAutoMed() {
	if (Menu::Vars::misc_automed) {
		auto held = LocalPlayer::Entity()->GetHeldItem();
		auto ent = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		float curtime = LocalPlayer::Entity()->lastSentTickTime();

		if (std::wstring(held->info()->shortname()).find(wxorstr_(L"syringe")) != std::string::npos ||
			std::wstring(held->info()->shortname()).find(wxorstr_(L"bandage")) != std::string::npos &&
			ent->timeSinceDeployed() > ent->deployDelay()) {
			if (LocalPlayer::Entity()->health() < 98.0f) {
				ent->ServerRPC(xorstr_("UseSelf"));
			}
		}
	}
}


void do_attack(BasePlayer* pEnt) {


	auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();

	if (held->class_name_hash() == STATIC_CRC32("BaseMelee") || held->class_name_hash() == STATIC_CRC32("Jackhammer") || held->class_name_hash() == STATIC_CRC32("Chainsaw")) {



		static auto hitTests = (UINT_PTR)GETCLASS("Assembly-CSharp::HitTest");
		//	if (!hit_test_class)
			//	return;

		HitTest* hitTest = (HitTest*)NewIl2CPPObject(hitTests);

		if (!hitTest)
			return;

		auto entitys = hitTest->HitEntity();

		Transform* transform = hitTest->HitTransform();

		BaseMelee* baseMelee = LocalPlayer::Entity()->GetHeldEntity<BaseMelee>();


		if (baseMelee->nextAttackTime() >= Time::time())
			return;

		if (baseMelee->timeSinceDeployed() < baseMelee->deployDelay())
			return;

		Ray ray = Ray(LocalPlayer::Entity()->bones()->head->position, (pEnt->bones()->head->position - LocalPlayer::Entity()->bones()->head->position).normalized());


		hitTest->MaxDistance() = 1000.0f;
		hitTest->HitTransform() = pEnt->bones()->head->transform;
		hitTest->AttackRay() = ray;
		hitTest->DidHit() = true;
		hitTest->HitEntity() = pEnt;
		hitTest->HitPoint() = transform->InverseTransformPoint(pEnt->bones()->head->position);
		hitTest->HitNormal() = transform->InverseTransformDirection(pEnt->bones()->head->position);

		hitTest->damageProperties() = baseMelee->damageProperties();

		//held->StartAttackCooldown(held->repeatDelay());

		if (baseMelee->CanHit(hitTest)) {
			baseMelee->ProcessAttacks(hitTest);
		}

		LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>()->StartAttackCooldown(baseMelee->repeatDelay());

	}
}
void ClientInput_hk(BasePlayer* plly, uintptr_t state) {
	__try {
		if (!plly)
			return plly->ClientInput(state);



		if (target_ply->bones()->head->position.distance(LocalPlayer::Entity()->bones()->head->position) < 3.99f && Menu::Vars::combat_silentmelee) {
			do_attack(all_ply);
		}



		if (plly->userID() == LocalPlayer::Entity()->userID()) {
			if (Menu::Vars::combat_manipulator && target_ply != nullptr && target_ply->isCached() && GKey(Menu::Vars::combat_manipulator_bind) && Menu::Vars::combat_silentmelee)
				plly->clientTickInterval() = 0.99f;
			else
				plly->clientTickInterval() = FLT_MIN;

			auto held = plly->GetHeldEntity<BaseProjectile>();
			if (held) {
				if (Menu::Vars::combat_nosway && held->class_name_hash() != STATIC_CRC32("BaseMelee")) {
					held->aimSway() = 0.f;
					held->aimSwaySpeed() = 0.f;
				}

				if (Menu::Vars::combat_rapid)
					held->repeatDelay() = 0.05f;

				else if (held->class_name_hash() == STATIC_CRC32("Baseprojectile"))
					held->repeatDelay() = 0.12f;

				if (Menu::Vars::combat_automatic)
					held->automatic() = true;

				NiggaDoAutoMed();
				if (Menu::Vars::combat_autoshoot || (Menu::Vars::combat_manipulator && GKey(Menu::Vars::combat_manipulator_bind))) {
					if (!held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
						if (target_ply != nullptr && target_ply->isCached()) {
							auto mpv = target_ply->find_mpv_bone();
							Vector3 target;
							if (mpv != nullptr)
								target = mpv->position;
							else
								target = target_ply->bones()->head->position;

							if (GamePhysics::IsVisible(target, plly->eyes()->position()))
								held->DoAttack();
						}
					}
				}
			}

			Globals::ManipulatorData::IsManipulating = Menu::Vars::combat_manipulator && GKey(Menu::Vars::combat_manipulator_bind);

			GLOBAL_TIME = Time::time();

			if (Menu::Vars::combat_manipulator && target_ply != nullptr && target_ply->isCached() && GKey(Menu::Vars::combat_manipulator_bind))
				other::find_manipulate_angle();
			else
				if (!other::m_manipulate.empty())
					other::m_manipulate = Vector3::Zero();

			Physics::IgnoreLayerCollision(4, 12, !Menu::Vars::misc_walkonwater);
			Physics::IgnoreLayerCollision(30, 12, Menu::Vars::misc_walkonwater);
			Physics::IgnoreLayerCollision(11, 12, Menu::Vars::misc_walkonwater);

			if (GetAsyncKeyState(Menu::Vars::misc_zoomkey))
				ConVar::Graphics::_fov() = 15.f;
			else
				ConVar::Graphics::_fov() = Menu::Vars::visuals_playerfov;

			if (Menu::Vars::misc_fakeadmin)
				plly->playerFlags() |= PlayerFlags::IsAdmin;

			if (Menu::Vars::misc_noattackres)
				if (plly->mounted())
					plly->mounted()->canWieldItems() = true;

			if (Menu::Vars::misc_lighting != 0) {
				auto list = TOD_Sky::instances();
				if (list) {
					for (int j = 0; j < list->size; j++) {
						auto sky = (TOD_Sky*)list->get(j);
						if (!sky)
							continue;

						float amb = 1.f;
						if (Menu::Vars::misc_lighting == 1)
							amb = 4.f;
						else if (Menu::Vars::misc_lighting == 2)
							amb = 6.f;

						sky->Stars()->Size() = amb == 70.f ? 0.90f : 1.f;
						sky->Stars()->Brightness() = amb;
						sky->Day()->AmbientMultiplier() = amb == 4.f ? 0.2f : 1.f;
						sky->Night()->AmbientMultiplier() = amb;
					}
				}
			}
		}

		plly->ClientInput(state);

		// before network 
		if (Menu::Vars::misc_antiaim)
			plly->input()->state()->current()->aimAngles() = Vector3(100, rand() % 99 + -99, 100);


		if (Menu::Vars::misc_Silentwalk)
			LocalPlayer::Entity()->add_modelstate_flag(ModelState::Flags::OnLadder);



		if (Menu::Vars::misc_nosprintres)
			LocalPlayer::Entity()->add_modelstate_flag(ModelState::Flags::Sprinting);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void DoMovement_hk(Projectile* pr, float deltaTime) {
	__try {
		float thickness_value = 0.1f;
		if (pr->isAuthoritative())
			if (Menu::Vars::combat_bigbullets)
				thickness_value += .9f;



		pr->thickness() = thickness_value;


		return pr->DoMovement(deltaTime);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
float GetRandomVelocity_hk(ItemModProjectile* self) {
	__try {
		float modifier = 1.f;

		if (Menu::Vars::combat_fastbullets)
			modifier += 0.49f;

		return self->GetRandomVelocity() * modifier;
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void ProcessAttack_hk(BaseMelee* self, HitTest* hit) {
	__try {
		auto entity = hit->HitEntity();




		if (!Menu::Vars::combat_silentmelee || !entity)
			return self->ProcessAttack(hit);

		if (entity->class_name_hash() == STATIC_CRC32("OreResourceEntity")) {
			BaseNetworkable* marker = BaseNetworkable::clientEntities()->FindClosest(STATIC_CRC32("OreHotSpot"), entity, 5.0f);
			if (marker) {
				entity = marker;
				hit->HitTransform() = marker->transform();
				hit->HitPoint() = marker->transform()->InverseTransformPoint(marker->transform()->position());
				hit->HitMaterial() = String::Il2CPPNewString(xorstr_("MetalOre"));
			}
		}
		else if (entity->class_name_hash() == STATIC_CRC32("TreeEntity")) {
			BaseNetworkable* marker = BaseNetworkable::clientEntities()->FindClosest(STATIC_CRC32("TreeMarker"), entity, 5.0f);
			if (marker) {
				hit->HitTransform() = marker->transform();
				hit->HitPoint() = marker->transform()->InverseTransformPoint(marker->transform()->position());
				hit->HitMaterial() = String::Il2CPPNewString(xorstr_("Wood"));
			}
		}

		return self->ProcessAttack(hit);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void AddPunch_hk(HeldEntity* attackEntity, Vector3 amount, float duration) {
	__try {
		amount *= Menu::Vars::combat_recoil / 100.0f;

		attackEntity->AddPunch(amount, duration);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}

Vector3 MoveTowards_hk(Vector3 current, Vector3 target, float maxDelta) {
	static auto ptr = GETMETHOD("Assembly-CSharp::BaseProjectile::SimulateAimcone(): Void");
	if (CALLED_BY(ptr, 0x800)) {
		target *= Menu::Vars::combat_recoil / 100.0f;
		maxDelta *= Menu::Vars::combat_recoil / 100.0f;
	}

	return Vector3_::MoveTowards(current, target, maxDelta);
}
bool Refract(Projectile* prj, uint64_t& seed, Vector3 point, Vector3 normal, float resistancePower) {

	return prj->Refract_(prj, seed, point, normal, resistancePower);
}
void FatBullets(Projectile* self)
{

	if (self->isAuthoritative() && self->isAlive() && self->integrity() > 0.50f)
	{
		auto cpos = self->transform()->position();
		auto zbone = target_ply->model()->find_bone(cpos).first;
		//auto zbone = target_ply->bones()->head;
		Vector3 target = zbone->position();

		if (target.distance(cpos) < 2.2f)
		{
			self->transform()->set_position(Vector3_::MoveTowards(cpos, target, 1.0f));
			if (self->transform()->position().distance(target) <= 1.2f)
			{
				Vector3 t = Vector3_::MoveTowards(self->transform()->position(), target, 0.2f);

				HitTest* hitTest = self->hitTest();
				hitTest->DidHit() = true;
				hitTest->HitEntity() = (target_ply);
				hitTest->HitTransform() = (zbone->transform());
				hitTest->HitPoint() = zbone->transform()->InverseTransformPoint(self->transform()->position());
				hitTest->HitNormal() = zbone->transform()->InverseTransformDirection(self->transform()->position());
				hitTest->AttackRay() = Ray(self->transform()->position(), t - self->transform()->position());

				printf("Value %f \n", target_ply->bones()->head->position.distance(self->currentPosition()));

				self->DoHit(hitTest, t, self->hitTest()->HitNormalWorld());
			}
		}
	}
}
bool DoHit_hk(Projectile* prj, HitTest* test, Vector3 point, Vector3 normal) {
	__try {

		if (Menu::Vars::combat_pierce) {
			if (prj->isAuthoritative()) {
				auto lol = test->HitEntity();
				auto go = test->gameObject();

				if (go && !lol) {
					if (go->layer() == 0 || go->layer() == 24) {
						return false;
					}
				}
				if (lol) {
					if (lol->class_name_hash() == STATIC_CRC32("CargoShip") || lol->class_name_hash() == STATIC_CRC32("BaseOven")
						|| lol->class_name_hash() == STATIC_CRC32("TreeEntity") || lol->class_name_hash() == STATIC_CRC32("OreResourceEntity")
						|| lol->class_name_hash() == STATIC_CRC32("CH47HelicopterAIController") || lol->class_name_hash() == STATIC_CRC32("MiniCopter")
						|| lol->class_name_hash() == STATIC_CRC32("BoxStorage") || lol->class_name_hash() == STATIC_CRC32("Workbench")
						|| lol->class_name_hash() == STATIC_CRC32("VendingMachine") || lol->class_name_hash() == STATIC_CRC32("Barricade")
						|| lol->class_name_hash() == STATIC_CRC32("BuildingPrivlidge") || lol->class_name_hash() == STATIC_CRC32("LootContainer")
						|| lol->class_name_hash() == STATIC_CRC32("HackableLockedCrate") || lol->class_name_hash() == STATIC_CRC32("ResourceEntity")
						|| lol->class_name_hash() == STATIC_CRC32("RidableHorse") || lol->class_name_hash() == STATIC_CRC32("MotorRowboat")
						|| lol->class_name_hash() == STATIC_CRC32("ScrapTransportHelicopter") || lol->class_name_hash() == STATIC_CRC32("JunkPile")
						|| lol->class_name_hash() == STATIC_CRC32("MiningQuarry") || lol->class_name_hash() == STATIC_CRC32("WaterCatcher")
						|| lol->class_name_hash() == STATIC_CRC32("RHIB")) {
						return false;
					}
				}
			}
		}
		return prj->DoHit(test, point, normal);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void SetEffectScale_hk(Projectile* self, float eScale) {
	__try {

		return self->SetEffectScale((Menu::Vars::combat_psilent && self->isAuthoritative()) ? 1.5f : eScale);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
System::Object_* StartCoroutine_hk(MonoBehaviour* a1, System::Object_* un2) {
	if (Menu::Vars::misc_fastloot) {
		static auto v = GETMETHOD("Assembly-CSharp::ItemIcon::SetTimedLootAction(UInt32,Action): Void");
		if (CALLED_BY(v, 0x656)) {
			*reinterpret_cast<float*>(un2 + 0x28) = -0.2f;
		}
	}

	return a1->StartCoroutine(un2);
}
String* ConsoleRun_hk(ConsoleSystem::Option* optiom, String* str, Array<System::Object_*>* args) {
	if (optiom->IsFromServer()) {
		if (str->buffer) {
			auto string = std::wstring(str->buffer);
			if (string.find(wxorstr_(L"noclip")) != std::wstring::npos ||
				string.find(wxorstr_(L"debugcamera")) != std::wstring::npos ||
				string.find(wxorstr_(L"admintime")) != std::wstring::npos ||
				string.find(wxorstr_(L"camlerp")) != std::wstring::npos ||
				string.find(wxorstr_(L"camspeed")) != std::wstring::npos) {

				str = String::Il2CPPNewString(xorstr_(""));
			}
		}
	}

	return ConsoleSystem::Run(optiom, str, args);
}
void set_flying_hk(ModelState* modelState, bool state) {
	__try {
		modelState->set_flying(false);
	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}


void HookAll() {
	__try {

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		hookengine::hook(oPresent, Present_hk);
		hookengine::hook(oResize, Resize_hk);

		hookengine::hook(BasePlayer::ClientUpdate_, ClientUpdate_hk);
		hookengine::hook(BasePlayer::ClientUpdate_Sleeping_, ClientUpdate_Sleeping_hk);
		hookengine::hook(PlayerWalkMovement::UpdateVelocity_, UpdateVelocity_hk);
		hookengine::hook(PlayerWalkMovement::HandleJumping_, HandleJumping_hk);
		hookengine::hook(BasePlayer::CanAttack_, CanAttack_hk);
		hookengine::hook(BasePlayer::OnLand_, OnLand_hk);
		hookengine::hook(Projectile::DoMovement_, DoMovement_hk);
		hookengine::hook(FlintStrikeWeapon::DoAttack_, DoAttack_hk);
		hookengine::hook(InputState::IsDown_, IsDown_hk);
		hookengine::hook(BaseCombatEntity::OnAttacked_, OnAttacked_hk);
		hookengine::hook(ConsoleSystem::Run_, ConsoleRun_hk);
		hookengine::hook(ModelState::set_flying_, set_flying_hk);
		hookengine::hook(HitTest::BuildAttackMessage_, BuildAttackMessage_hk);
		//hookengine::hook(BaseMelee::ProcessAttack_, ProcessAttack_hk);
		hookengine::hook(Projectile::DoHit_, DoHit_hk);
		hookengine::hook(BaseMountable::EyePositionForPlayer_, EyePositionForPlayer_hk);
		hookengine::hook(MonoBehaviour::StartCoroutine_, StartCoroutine_hk);
		hookengine::hook(Projectile::SetEffectScale_, SetEffectScale_hk);
		hookengine::hook(BasePlayer::ClientInput_, ClientInput_hk);
		hookengine::hook(ItemModProjectile::GetRandomVelocity_, GetRandomVelocity_hk);
		hookengine::hook(PlayerEyes::BodyLeanOffset_, BodyLeanOffset_hk);
		hookengine::hook(AimConeUtil::GetModifiedAimConeDirection_, GetModifiedAimConeDirection_hk);
		hookengine::hook(PlayerEyes::DoFirstPersonCamera_, DoFirstPersonCamera_hk);
		hookengine::hook(Vector3_::MoveTowards_, MoveTowards_hk);
		hookengine::hook(HeldEntity::AddPunch_, AddPunch_hk);

		DetourTransactionCommit();

	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}
void UnhookAll() {
	__try {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		hookengine::unhook(oPresent, Present_hk);
		hookengine::unhook(oResize, Resize_hk);

		hookengine::unhook(BasePlayer::ClientUpdate_, ClientUpdate_hk);
		hookengine::unhook(PlayerWalkMovement::UpdateVelocity_, UpdateVelocity_hk);
		hookengine::unhook(PlayerWalkMovement::HandleJumping_, HandleJumping_hk);
		hookengine::unhook(BasePlayer::CanAttack_, CanAttack_hk);
		hookengine::unhook(BasePlayer::OnLand_, OnLand_hk);
		hookengine::unhook(Projectile::DoMovement_, DoMovement_hk);
		hookengine::unhook(FlintStrikeWeapon::DoAttack_, DoAttack_hk);
		hookengine::unhook(InputState::IsDown_, IsDown_hk);
		hookengine::unhook(BaseCombatEntity::OnAttacked_, OnAttacked_hk);
		hookengine::unhook(ConsoleSystem::Run_, ConsoleRun_hk);
		hookengine::unhook(ModelState::set_flying_, set_flying_hk);
		hookengine::unhook(HitTest::BuildAttackMessage_, BuildAttackMessage_hk);
		//hookengine::unhook(BaseMelee::ProcessAttack_, ProcessAttack_hk);
		hookengine::unhook(Projectile::DoHit_, DoHit_hk);
		hookengine::unhook(BaseMountable::EyePositionForPlayer_, EyePositionForPlayer_hk);
		hookengine::unhook(MonoBehaviour::StartCoroutine_, StartCoroutine_hk);
		hookengine::unhook(Projectile::SetEffectScale_, SetEffectScale_hk);
		hookengine::unhook(BasePlayer::ClientInput_, ClientInput_hk);
		hookengine::unhook(ItemModProjectile::GetRandomVelocity_, GetRandomVelocity_hk);
		hookengine::unhook(PlayerEyes::BodyLeanOffset_, BodyLeanOffset_hk);
		hookengine::unhook(AimConeUtil::GetModifiedAimConeDirection_, GetModifiedAimConeDirection_hk);
		hookengine::unhook(PlayerEyes::DoFirstPersonCamera_, DoFirstPersonCamera_hk);
		hookengine::unhook(Vector3_::MoveTowards_, MoveTowards_hk);
		hookengine::unhook(HeldEntity::AddPunch_, AddPunch_hk);


		DetourTransactionCommit();

	}
	__except (true) {
		std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
	}
}