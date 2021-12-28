#pragma once
class Mouse : public Object
{
public:
	Mouse();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

