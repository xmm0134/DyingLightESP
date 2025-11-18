
class Entity 
{
private:
	uintptr_t handle;
	uintptr_t HealthModule;
	uintptr_t IModelClass;
public:
	char* Name = nullptr;
	float Health;
	Vector3 Position;
	Vector3 HeadPos;
public:
	Entity(uintptr_t Entity);
	bool IsValid();
	uintptr_t Gethandle();
	Vector3 GetEntityBone(short int ID);
	static uintptr_t GetEntity(int listnum, int index);
};