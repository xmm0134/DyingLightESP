#define ENTLIST_1_MAX 16
#define ENTLIST_2_MAX 26
#define ENTLIST_3_MAX 27

namespace Offsets 
{
	constexpr static uintptr_t IModelObject = 0x8;
	constexpr static uintptr_t m_HeadPos = 0x2CC;
	constexpr static uintptr_t GameID = 0x1C15288;
	constexpr static uintptr_t SessionID = 0x540;
	constexpr static uintptr_t CameraManager = 0xC0;
	constexpr static uintptr_t Camera = 0x50;
	constexpr static uintptr_t BaseCamera = 0x8;
	constexpr static uintptr_t ViewMatrx = 0xB0;
	constexpr static uintptr_t Localplayer = 0x1C15298;
	constexpr static uintptr_t LocalplayerPtrChain[] = { 0x780, 0xAB0 };
	constexpr static uintptr_t Position = 0x1194;
	constexpr static uintptr_t Health = 0x125C;
	constexpr static uintptr_t CurWeaponPtr = 0x16B8;
	constexpr static uintptr_t WeaponDur = 0x44;
	constexpr static uintptr_t WeaponAmmo = 0x40;
	constexpr static uintptr_t StaminModuleptr = 0x1340;
	constexpr static uintptr_t m_Stamina = 0x10;
	constexpr static uintptr_t ModuleParent = 0x40;
	constexpr static uintptr_t ZombieHealth = 0x78;
	constexpr static uintptr_t AIManager = 0x9F0;
	constexpr static uintptr_t LevelID = 0x1C153D0;
	constexpr static uintptr_t EntityList_1 = 0x178;
	constexpr static uintptr_t EntityList_2 = 0x190;
	constexpr static uintptr_t EntityList_3 = 0xE0;
	constexpr static uintptr_t ZombiePosition = 0x958;
	constexpr static uintptr_t Entity_name = 0x250;
	namespace ZombieComponentModules
	{
		constexpr static uintptr_t ZombieArmourHealthModule = 0xCE8;
		constexpr static uintptr_t ZombieAlarmingModule = 0xC98;
		constexpr static uintptr_t KnockdownModule = 0xCA8;
		constexpr static uintptr_t StandingupModule = 0xCC0;
		constexpr static uintptr_t IdleingModule = 0xCC8;
		constexpr static uintptr_t StaminaModule = 0xD10;
		constexpr static uintptr_t TransformModule = 0xD20;
		constexpr static uintptr_t ZombieLogicModule = 0xD50;
		constexpr static uintptr_t MimicModule = 0xDA0;
		constexpr static uintptr_t ZombieMovmentModule = 0xDD8;
		constexpr static uintptr_t TurnModule = 0xDF8;
	}
	namespace Writabels 
	{
		constexpr static uintptr_t decrease_stamina = 0xCF0083;
		constexpr static uintptr_t decrease_ammo = 0x6F2E95;
	}
}