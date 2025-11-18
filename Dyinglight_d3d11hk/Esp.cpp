#include"Includes.h"
#include"Menu.h"
#include"ErrorLogger.h"

void RunEsp(ID3D11Device* Device, ID3D11DeviceContext* Context)
{
	Player Localplayer;
	if (Localplayer.IsHackAbleState())
	{
		if (!Drawing::Initialized)
		{
			Drawing::InitDraw(Device, Context);
		}
		
		Drawing::BeginFrame();
		for (int i = 0; i < ENTLIST_1_MAX; i++)
		{
			uintptr_t _Entity = Entity::GetEntity(2, i);

			if (_Entity == Localplayer.GetHandle())
			{
				continue;
			}
			if (_Entity)
			{
				Entity TheEntity(_Entity);
				if (TheEntity.IsValid())
				{
					Vector3 Position = TheEntity.Position;
					uintptr_t TheCamera = Player::GetCamera();
					if (TheCamera)
					{
						ViewMatrix Vmatrix = *(ViewMatrix*)(TheCamera + Offsets::ViewMatrx);
						Vector2 Buffer;
						float oldy;
						if (W2S(Position, Buffer, Vmatrix.VMatrix, 1920, 1080))
						{
							oldy = Buffer.y;
							Buffer.y = 1080 - Buffer.y;
							if (Menu::MenuVars::Boxes)
							{
								Vector3 HeadPosition;
								auto Ent = Entity::GetEntity(2, i);
								if (Ent == _Entity)
								{
									oGetBonePose((void*)_Entity, &HeadPosition, HEAD);
									Vector2 HeadBuffer;
									W2S(HeadPosition, HeadBuffer, Vmatrix.VMatrix, 1920, 1080);
									HeadBuffer.y = 1080 - HeadBuffer.y;
									float height = HeadBuffer.y - Buffer.y;
									float Width = height / 4;
									HeadBuffer.x -= Width;
									Drawing::DrawOutlinedRect(HeadBuffer, Width * 2, height, Drawing::Colors::Yellow);
								}
								else
								{
									continue;
								}
							}
							if (Menu::MenuVars::BoneEsp)
							{
								Vector3 Throat3D;
								Vector3 UpperChest3D;
								Vector3 UpperPelvis3D;
								Vector3 Pelvis3D;
								Vector3 RightShoulder3D;
								Vector3 RightElbow3D;
								Vector3 RightHand3D;
								Vector3 RightFoot3D;
								Vector3 RightKnee3D;
								Vector3 LeftShoulder3D;
								Vector3 LeftElbow3D;
								Vector3 LeftHand3D;
								Vector3 Foot3D;
								Vector3 Knee3D;
								Vector2 Throat2D;
								Vector2 LeftShoulder2D;
								Vector2 LeftElbow2D;
								Vector2 LeftHand2D;
								Vector2 Foot2D;
								Vector2 Knee2D;
								Vector2 RightShoulder2D;
								Vector2 RightElbow2D;
								Vector2 RightHand2D;
								Vector2 RightKnee2D;
								Vector2 RightFoot2D;
								Vector2 Pelvis2D;
								Vector2 UpperPelvis2D;
								Vector2 UpperChest2D;
								auto Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue; 

								oGetBonePose((void*)_Entity, &Foot3D, LEFTFOOT);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &Knee3D, LEFTKNEECAP);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &RightFoot3D, RIGHTFOOT);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &RightKnee3D, RIGHTKNEECAP);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &Pelvis3D, PELVIS);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &UpperPelvis3D, UPPERPELVIS);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &UpperChest3D, UPPERCHEST);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &Throat3D, THROAT );
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &RightShoulder3D, RIGHTSHOULDER);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &RightElbow3D, RIGHTELBOW);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &RightHand3D, RIGHTHAND);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &LeftShoulder3D, LEFTSHOULDER);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &LeftElbow3D, LEFTELBOW);
								Ent = Entity::GetEntity(2, i);
								if (Ent != _Entity)
									continue;
								oGetBonePose((void*)_Entity, &LeftHand3D, LEFTHAND);

								if (!W2S(Foot3D, Foot2D, Vmatrix.VMatrix, 1920, 1080))
									continue;

								W2S(Knee3D, Knee2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(RightFoot3D, RightFoot2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(RightKnee3D, RightKnee2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(Pelvis3D, Pelvis2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(UpperPelvis3D, UpperPelvis2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(UpperChest3D, UpperChest2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(Throat3D, Throat2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(LeftShoulder3D, LeftShoulder2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(LeftElbow3D, LeftElbow2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(LeftHand3D, LeftHand2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(RightShoulder3D, RightShoulder2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(RightElbow3D, RightElbow2D, Vmatrix.VMatrix, 1920, 1080);
								W2S(RightHand3D, RightHand2D, Vmatrix.VMatrix, 1920, 1080);
								LeftHand2D.y = 1080 - LeftHand2D.y;
								LeftElbow2D.y = 1080 - LeftElbow2D.y;
								LeftShoulder2D.y = 1080 - LeftShoulder2D.y;
								RightShoulder2D.y = 1080 - RightShoulder2D.y;
								RightElbow2D.y = 1080 - RightElbow2D.y;
								RightHand2D.y = 1080 - RightHand2D.y;
								Throat2D.y = 1080 - Throat2D.y;
								UpperChest2D.y = 1080 - UpperChest2D.y;
								Pelvis2D.y = 1080 - Pelvis2D.y;
								UpperPelvis2D.y = 1080 - UpperPelvis2D.y;
								Foot2D.y = 1080 - Foot2D.y;
								Knee2D.y = 1080 - Knee2D.y;
								RightFoot2D.y = 1080 - RightFoot2D.y;
								RightKnee2D.y = 1080 - RightKnee2D.y;
								Drawing::DrawOutLinedLine(Foot2D, Knee2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(RightFoot2D, RightKnee2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(Knee2D, Pelvis2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(RightKnee2D, Pelvis2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(Pelvis2D, UpperPelvis2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(UpperPelvis2D, UpperChest2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(UpperChest2D, Throat2D, Drawing::Colors::Yellow);

								Drawing::DrawOutLinedLine(UpperChest2D, RightShoulder2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(RightShoulder2D, RightElbow2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(RightElbow2D, RightHand2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(UpperChest2D, LeftShoulder2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(LeftShoulder2D, LeftElbow2D, Drawing::Colors::Yellow);
								Drawing::DrawOutLinedLine(LeftElbow2D, LeftHand2D, Drawing::Colors::Yellow);
								
							}
							if (Menu::MenuVars::Lines)
							{
								Drawing::DrawOutLinedLine(Buffer, Vector2(960, 0), Drawing::Colors::Yellow);
							}
							if (Menu::MenuVars::NameEsp)
							{
								Buffer.y = oldy;
								Drawing::DrawOutlinedText(Buffer, TheEntity.Name, strlen(TheEntity.Name) + 1, 0.5f, Vector3(1.0f, 0, 0));
							}
						}
					}
				}
			}
		}
		
	}
}