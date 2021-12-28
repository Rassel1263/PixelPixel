#pragma once

enum InputState
{
	None = 0,
	Down = 1,
	Press = 2,
	Up = 3,
};

class Input
{
private:

	Input() {}
	Input(const Input&) = delete;
	void operator = (const Input&) = delete;

public:

	static Input& GetInstance()
	{
		static Input instance;
		return instance;
	}

private:

	D3DXVECTOR2 cursorPos = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 worldCursorPos = D3DXVECTOR2(0.0f, 0.0f);
	int keyState[255] = {};

public:

	int GetKeyState(int key)
	{
		return keyState[key];
	}

	D3DXVECTOR2 GetWorldCursorPos()
	{
		return worldCursorPos;
	}

	D3DXVECTOR2 GetCursorPos()
	{
		return cursorPos;
	}

	void Update()
	{
		// 키보드 업데이트
		for (int i = 0; i < 255; ++i)
		{
			if (GetAsyncKeyState(i))
			{
				if (keyState[i] == InputState::None)
					keyState[i] = InputState::Down;
				else if (keyState[i] == InputState::Down)
					keyState[i] = InputState::Press;
			}
			else
			{
				if (keyState[i] == InputState::Up)
					keyState[i] = InputState::None;
				else if (keyState[i] > 0)
					keyState[i] = InputState::Up;
			}
		}

		auto& D3D = Direct3D::GetInstance();
		POINT point;
		::GetCursorPos(&point);
		::ScreenToClient(Direct3D::GetInstance().hWnd, &point);
		point.y = D3D.screenHeight - point.y;

		// 게임 해상도에 맞는 위치를 가져옵니다.
		cursorPos = D3DXVECTOR2(point.x / (float)D3D.screenWidth * D3D.resolutionWidth - D3D.resolutionWidth / 2.0f, point.y / (float)D3D.screenHeight * D3D.resolutionHeight - D3D.resolutionHeight / 2.0f);
		// 확대 축소를 적용합니다.
		D3DXVECTOR2 p2 = D3DXVECTOR2(cursorPos.x / D3D.cameraScale.x, cursorPos.y / D3D.cameraScale.y);
		// 카메라의 이동값만큼 더해줘야 합니다.
		D3DXVECTOR2 p3 = p2 + D3DXVECTOR2(D3D.cameraPos.x, D3D.cameraPos.y);
		// Window는 위에서 아래로 y값이 증가하고, DirectX는 아래에서 위로 y값이 증가합니다.
		worldCursorPos = D3DXVECTOR2(p3.x, p3.y);
	}

};
