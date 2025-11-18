#include"Includes.h"

Player::Player()
{
	try {
		uintptr_t PTR1 = *(uintptr_t*)(GameModule + Offsets::Localplayer);
		if (PTR1)
		{
			uintptr_t PTR2 = *(uintptr_t*)(PTR1 + Offsets::LocalplayerPtrChain[0]);
			if (PTR2)
			{
				uintptr_t PTR3 = *(uintptr_t*)(PTR2 + Offsets::LocalplayerPtrChain[1]);
				this->handle = PTR3;
				if (handle)
				{
					Health = *(float*)(handle + Offsets::Health);
					Position = *(Vector3*)(handle + Offsets::Position);
					this->Current_Weapon = *(uintptr_t*)(handle + Offsets::CurWeaponPtr);
					if (Current_Weapon)
					{
						CurrentWeaponAmmo = *(int*)(this->Current_Weapon + Offsets::WeaponAmmo);
						CurrentWeaponDurability = *(float*)(this->Current_Weapon + Offsets::WeaponDur);
					}
					this->StaminaModule = *(uintptr_t*)(this->handle + Offsets::StaminModuleptr);
					if (this->StaminaModule)
					{
						this->Stamina = *(float*)(this->StaminaModule + Offsets::m_Stamina);
					}
					Status = true;
				}
				else
				{
					Status = false;
				}
			}
		}
	}
	catch(...)
	{
		LogError("Exception in Player");
	}
}

uintptr_t Player::GetHandle()
{
	return handle;
}

uintptr_t Player::GetCurrentWeapon()
{
	return Current_Weapon;
}

uintptr_t Player::GetStaminaModule()
{
	return StaminaModule;
}

uintptr_t Player::GetCamera()
{
	try
	{
		uintptr_t GameID = *(uintptr_t*)(GameModule + Offsets::GameID);
		if (GameID)
		{
			uintptr_t GameSession = *(uintptr_t*)(GameID + Offsets::SessionID);
			if (GameSession)
			{
				uintptr_t CameraManager = *(uintptr_t*)(GameSession + Offsets::CameraManager);
				if (CameraManager)
				{
					uintptr_t Camera = *(uintptr_t*)(CameraManager + Offsets::Camera);
					if (Camera)
					{
						return *(uintptr_t*)(Camera + Offsets::BaseCamera);
					}
				}
			}
		}
	}
	catch (...)
	{
		LogError("Exception inside GetCamera");
	}
	return NULL;
}

uintptr_t Player::GetCameraHandle()
{
	try
	{
		uintptr_t GameID = *(uintptr_t*)(GameModule + Offsets::GameID);
		if (GameID)
		{
			uintptr_t GameSession = *(uintptr_t*)(GameID + Offsets::SessionID);
			uintptr_t CameraManager = *(uintptr_t*)(GameSession + Offsets::CameraManager);
			return *(uintptr_t*)(CameraManager + Offsets::Camera);
		}
	}
	catch (...)
	{
		LogError("Exception in GetCameraHandle!");
	}
	return NULL;
}

bool Player::IsHackAbleState()
{
	try
	{
		uintptr_t PTR1 = *(uintptr_t*)(GameModule + Offsets::Localplayer);
		if (PTR1)
		{
			uintptr_t PTR2 = *(uintptr_t*)(PTR1 + Offsets::LocalplayerPtrChain[0]);
			if (PTR2)
			{
				uintptr_t PTR3 = *(uintptr_t*)(PTR2 + Offsets::LocalplayerPtrChain[1]);
				if (PTR3)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	catch (...)
	{
		LogError("exception inside static IsHackAbleState");
	}
	return false;
}

bool Player::PlayerAlive()
{
	if (Status && this->Health < 1000.0f && this->Health > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::SetHealth(float val)
{
	if (this->StaminaModule)
	{
		*(float*)(handle + Offsets::Health) = val;
	}
}

void Player::SetAmmo(int Ammo)
{
	if (Current_Weapon)
	{
		*(int*)(this->Current_Weapon + Offsets::WeaponAmmo) = Ammo;
	}
}

void Player::SetStamina(float val)
{
	if (this->StaminaModule)
	{
		*(float*)(this->StaminaModule + Offsets::m_Stamina) = val;
	}
}

void Player::SetDurability(float val)
{
	if (Current_Weapon)
	{
		*(float*)(this->Current_Weapon + Offsets::WeaponDur) = val;
	}
}
