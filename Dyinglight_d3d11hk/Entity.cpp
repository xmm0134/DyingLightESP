#include"Includes.h"
bool IsValidReadPtr(uintptr_t* addr)
{
	try
	{
		uintptr_t var = *(uintptr_t*)(addr);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

Entity::Entity(uintptr_t _Entity)
{
	this->handle = _Entity;
	if (handle)
	{
		if (!IsValidReadPtr((uintptr_t*)Offsets::ZombiePosition + handle))
		{
			handle = NULL;
			return;
		}
		this->Position = *(Vector3*)(Offsets::ZombiePosition + handle);
		if (!IsValidReadPtr((uintptr_t*)this->handle + Offsets::ZombieComponentModules::ZombieArmourHealthModule))
		{
			handle = NULL;
			return;
		}
		this->HealthModule = *(uintptr_t*)(this->handle + Offsets::ZombieComponentModules::ZombieArmourHealthModule);
		uintptr_t Charptr = *(uintptr_t*)(handle + Offsets::Entity_name);
		if (Charptr && Charptr > 0x1000000000 && Charptr < 0x7fffffffffff)
		{	
			this->Name = *(char**)(handle + Offsets::Entity_name);
		}
		if (HealthModule)
		{
			if (!IsValidReadPtr((uintptr_t*)Offsets::ZombieHealth + this->HealthModule))
			{
				handle = NULL;
				return;
			}
			this->Health = *(float*)(Offsets::ZombieHealth + this->HealthModule);
		}
		else
		{
			handle = NULL;
		}
	}
}

bool Entity::IsValid()
{
	if (handle)
	{
		if (HealthModule)
		{
			if (Health <= 0.0f || Health > 30000.0f)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

uintptr_t Entity::Gethandle()
{
	return handle;
}

Vector3 Entity::GetEntityBone(short int ID)
{
	Vector3 Ret;
	oGetBonePose((void*)this->handle, &Ret, ID);
	return Ret;
}

uintptr_t Entity::GetEntity(int listnum, int index)
{
	try
	{
		uintptr_t levelid = *(uintptr_t*)(GameModule + Offsets::LevelID);
		if (levelid)
		{
			uintptr_t AIManager = *(uintptr_t*)(levelid + Offsets::AIManager);
			uintptr_t Entlist = NULL;
			if (AIManager)
			{
				switch (listnum)
				{
				case 1:
					Entlist = *(uintptr_t*)(AIManager + Offsets::EntityList_1);
					if (Entlist)
					{
						return *(uintptr_t*)(Entlist + index * 8);
					}
					else
					{
						return NULL;
					}
					break;
				case 2:
					Entlist = *(uintptr_t*)(AIManager + Offsets::EntityList_2);
					if (Entlist)
					{
						return *(uintptr_t*)(Entlist + index * 8);
					}
					else
					{
						return NULL;
					}
					break;
				case 3:
					Entlist = *(uintptr_t*)(AIManager + Offsets::EntityList_3);
					if (Entlist)
					{
						return *(uintptr_t*)(Entlist + index * 8);
					}
					else
					{
						return NULL;
					}
					break;
				default:
					break;
				}
			}
		}
		else
		{
			return NULL;
		}
	}
	catch (...)
	{
		LogError("Exception inside GetEnity");
	}
}
