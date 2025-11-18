
struct ViewMatrix
{
	float VMatrix[16];
};

bool W2S(Vector3 pos, Vector2& screen, float matrix[16], int width, int height);
bool WorldToScreen(Vector3 coords, Vector3& Ret, float ViewMatrix[16]);