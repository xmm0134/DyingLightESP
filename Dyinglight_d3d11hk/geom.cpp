#include"Includes.h"

bool W2S(Vector3 pos, Vector2& screen, float matrix[16], int Width, int Height)
{
	screen.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	screen.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	float W = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];
	if (W < 0.01f)
	{
		return false;
	}
	Vector2 NDC = { 0 };
	NDC.x = screen.x / W;
	NDC.y = screen.y / W;

	screen.x = (Width / 2 * NDC.x) + (NDC.x + Width / 2);
	screen.y = -(Height / 2 * NDC.y) + (NDC.y + Height / 2);
	return true;
}