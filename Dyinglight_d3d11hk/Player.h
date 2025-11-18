
class Player 
{
public:
	float Health;
	Vector3 Position;
	int CurrentWeaponAmmo;
	float CurrentWeaponDurability;
	float Stamina;

	Player();
	uintptr_t GetHandle();
	uintptr_t GetCurrentWeapon();
	uintptr_t GetStaminaModule();
	static uintptr_t GetCamera();
	static uintptr_t GetCameraHandle();
	static bool IsHackAbleState();
	bool PlayerAlive();
	void SetHealth(float val);
	void SetAmmo(int Ammo);
	void SetStamina(float val);
	void SetDurability(float val);

private:
	bool Status;
	uintptr_t handle;
	uintptr_t Current_Weapon;
	uintptr_t StaminaModule;
};