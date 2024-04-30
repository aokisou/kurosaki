#pragma once

class BaseScene
{
public:
	BaseScene(){}
	~BaseScene(){}

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Init() = 0;
	virtual void Release() = 0;
protected:
private:
};