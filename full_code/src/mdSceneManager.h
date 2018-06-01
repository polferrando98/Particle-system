#ifndef __MDSCENEMANAGER__
#define __MDSCENEMANAGER__
#include "Module.h"
#include <list>
#include "SDL\include\SDL.h"
#include "p2Point.h"
#include "Character.h"

class ParticleEmitter;

class mdSceneManager : public Module{
public:
	mdSceneManager();
	~mdSceneManager();

	bool awake(const pugi::xml_node& md_config) override;
	bool start() override;
	bool update(float dt) override;

	static const int wave_emitters = 20;
	ParticleEmitter* wave[wave_emitters];

private:
	SDL_Texture * goku = nullptr;
};

#endif