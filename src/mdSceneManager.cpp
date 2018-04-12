#include "mdSceneManager.h"
#include "Application.h"
#include "mdInput.h"
#include "mdParticleSystem.h"
#include "ParticleEmitter.h"

mdSceneManager::mdSceneManager()
{
}


mdSceneManager::~mdSceneManager()
{
}

bool mdSceneManager::awake(const pugi::xml_node & md_config)
{
	//HARDCODE, super easy to make an xml out of this, just sayin'

	//One vs one


	return true;
}

bool mdSceneManager::start()
{
	bool ret = true;

	App->particle_system->createEmitter({ 250,550 }, "particles/goku.xml");
	goku = App->textures->load("particles/Goku_render.png");

	return true;
}

bool mdSceneManager::update(float dt)
{

	if (App->input->getKey(SDL_SCANCODE_1) == KEY_DOWN) //"P" from Particle :-)
	{
		iPoint p;
		fPoint pf;
		App->input->getMousePosition((p.x), p.y);
		pf.x = p.x;
		pf.y = p.y;
		//App->particle_system->create({ p.x,p.y }, { 0, -1 }, 100);
		App->particle_system->createEmitter(pf, "particles/faya.xml");

	}

	if (App->input->getKey(SDL_SCANCODE_2) == KEY_DOWN) //"P" from Particle :-)
	{
		iPoint p;
		fPoint pf;
		App->input->getMousePosition((p.x), p.y);
		pf.x = p.x;
		pf.y = p.y;
		//App->particle_system->create({ p.x,p.y }, { 0, -1 }, 100);
		App->particle_system->createEmitter(pf, "particles/smouk.xml");
	}

	if (App->input->getKey(SDL_SCANCODE_3) == KEY_DOWN) //"P" from Particle :-)
	{
		iPoint p;
		fPoint pf;
		App->input->getMousePosition((p.x), p.y);
		pf.x = p.x;
		pf.y = p.y;
		//App->particle_system->create({ p.x,p.y }, { 0, -1 }, 100);
		App->particle_system->createEmitter(pf, "particles/galaxy.xml");
	}

	App->render->blit(30, goku, 100, 100,NULL,0.5f);


	return true;
}
