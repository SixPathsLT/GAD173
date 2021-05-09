#pragma once
#include "app.h"
#include "Scenes/Scene.h"

class SceneManager : public App
{

public:

	SceneManager();
	~SceneManager();
	std::vector<Scene*> scenes;
	int currentSceneIndex;

	void addScene(Scene *scene);
	void removeScene(int index);
	void endScene(int index);
	Scene* loadScene(int index);
	Scene* getScene(int index);

	virtual bool start();
	virtual void update(float deltaT);
	virtual void render();



};

