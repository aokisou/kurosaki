#pragma once

class BaseScene;

class SceneManager
{
public:
	enum SceneType
	{
		Title,
		Game,
	};

	void PreUpdate();	//更新処理の前にやりたい処理
	void Update();		//更新処理
	void Draw();

	//次のシーンを設定する
	void SetNextScene(SceneType _sceneType) { m_nextSceneType = _sceneType; }

	//現在のシーンを取得
	SceneType GetCurrentSceneType() { return m_currentSceneType; }

private:
	void Init();
	void Release();
	//シーンの切り替え
	void ChangeScene(SceneType _sceneType);

	std::shared_ptr<BaseScene> m_currentScene = nullptr;

	//現在のシーンを管理している
	SceneType m_currentSceneType = SceneType::Title;

	//次のシーンを管理している
	SceneType m_nextSceneType = m_currentSceneType;

//シングルトンパターン
//そのクラスが一つしか生成されないことを保証するデザインパターン
private:
	SceneManager() { Init(); }
	~SceneManager() { Release(); }
public:
	static SceneManager& Instance()
	{
		static SceneManager inst;//実体化
		return inst;
	}
};