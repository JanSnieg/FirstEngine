#pragma once

#include "NonCopyable.h"
#include <memory>
#include <vector>

// TEMP STUFF
class Pawn;
// TEMP END

class CameraManager;
class FrameRenderer;
class Game;
class Object;

class Level : private NonCopyable
{
public:
	Level();
	~Level();

	void StartUp(Game* game);
	void ShutDown();

	void Update(float deltaTime);
	void Render( FrameRenderer& frame ) const;


	void RegisterObject( Object* object );
	void UnregisterObject( Object* object );

	template< class TObject, typename... TArgs >
	TObject* CreateObject( TArgs&&... args );
	void DestroyObject( Object* object );


	Game* GetGame() const;
	CameraManager* GetCameraManager() const;

private:
	Game* m_game;

	std::unique_ptr<CameraManager> m_cameraManager;

	std::vector< Object* > m_objects;
	std::vector< Object* > m_registeredObjects;

	// TEMP STUFF
	Pawn* m_tiger;
	float m_cameraDistance;
	// TEMP END
};

template< class TObject, typename... TArgs >
TObject* Level::CreateObject( TArgs&&... args )
{
	TObject* object = new TObject( std::forward< TArgs >( args )... );
	object->StartUp( this );
	return object;
}
