#pragma once
#pragma warning(disable : 26495)

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <vector>
#include <map>
#include <string>
#include <istream>
#include <fstream>
#include <filesystem>
#include <crtdbg.h>
#include <assert.h>
#include <functional>

#define SAFE_RELEASE(x) if (x != NULL) x->Release()

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "Direct3D.h"
#include "Input.h"
#include "TextureManager.h"
#include "Sprite.h"

#include "Object.h"
#include "ObjectCollider2D.h"

#include "Mouse.h"

#include "IBullet.h"
#include "Bullet.h"
#include "EnemyBullet.h"

#include "Player.h"

#include "Boss.h"
#include "Enemy.h"
#include "EnemySpawner.h"

#include "Background.h"
#include "Button.h"

#include "IEffect.h"
#include "moveEft.h"
#include "BulletEft.h"
#include "HitEft.h"
#include "BoomEft.h"

#include "Scene.h"
#include "GameScene.h"
#include "TitleScene.h"
