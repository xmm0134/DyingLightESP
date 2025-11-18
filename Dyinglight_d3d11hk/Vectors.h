#pragma once

struct Vector3
{
	float x, y, z;
	Vector3(
		float x = 0.f,
		float y = 0.f,
		float z = 0.f)
		:x(x), y(y), z(z) {}

	const Vector3& operator+(const Vector3& other)
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	const Vector3& operator-(const Vector3& other)
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	const Vector3& operator*(const Vector3& other)
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	const Vector3& operator/(const Vector3& other)
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}
	void Reformat()
	{
		x = z;
		y = x;
		z = y;
	}
};

struct Vector2
{
	float x, y;
	Vector2(
		float x = 0,
		float y = 0)
		:x(x), y(y) {};
	Vector2 operator+(const Vector2 other)
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator-(const Vector2 other)
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 operator*(const Vector2 other)
	{
		return Vector2(x * other.x, y * other.y);
	}
	Vector2 operator/(const Vector2 other)
	{
		return Vector2(x / other.x, y / other.y);
	}
};