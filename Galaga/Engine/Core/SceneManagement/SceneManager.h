#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class Scene;

/** Scene management at run-time. */
class SceneManager
{
	static Scene* activeScene;
public:
	static inline Scene* GetActiveScene() { return activeScene; }
	static void LoadScene(Scene* sceneToLoad);
	static void UnloadScene(Scene* sceneToUnload);
	static void DestroyScene(Scene* sceneToDestroy);
};

#endif // !SCENEMANAGER_H
