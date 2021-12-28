#pragma once

class MoveEft : public IEffect
{
public:
	MoveEft(D3DXVECTOR2 pos, D3DXVECTOR2 scale, Color color, float rotate = 0);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

