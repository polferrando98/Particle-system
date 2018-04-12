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

	App->particle_system->createEmitter({ 150,550 }, "particles/faya.xml");
	App->particle_system->createEmitter({ 350,550 }, "particles/smouk.xml");
	App->particle_system->createEmitter({ 1060,550 }, "particles/goku-solution.xml");
	goku = App->textures->load("particles/Goku_render.png");

	return true;
}

bool mdSceneManager::update(float dt)
{
	if (App->input->getKey(SDL_SCANCODE_P) == KEY_DOWN) //"P" from Particle :-)
	{
		iPoint p;
		fPoint pf;
		App->input->getMousePosition((p.x), p.y);
		pf.x = p.x;
		pf.y = p.y;
		//Hardcode for the exercice
		ParticleInfo info;

		info.lifetime = 100;

		info.initial_scale = 1;

		info.final_scale = 0;

		info.texture_path = "particles/fire.png";


		info.initial_color.r = 255;
		info.initial_color.g = 255;
		info.initial_color.b = 255;
		info.initial_color.alpha = 255;

		info.final_color.r = 255;
		info.final_color.g = 255;
		info.final_color.b = 255;
		info.final_color.alpha = 255;

		info.pos = { pf.x,pf.y };

		info.vel_mag = 0;
		info.angle = 90;

		App->particle_system->create(info);
	}
	if (App->input->getKey(SDL_SCANCODE_1) == KEY_DOWN) 
	{
		iPoint p;
		fPoint pf;
		App->input->getMousePosition((p.x), p.y);
		pf.x = p.x;
		pf.y = p.y;
		//App->particle_system->create({ p.x,p.y }, { 0, -1 }, 100);
		App->particle_system->createEmitter(pf, "particles/faya.xml");

	}

	if (App->input->getKey(SDL_SCANCODE_2) == KEY_DOWN) 
	{
		iPoint p;
		fPoint pf;
		App->input->getMousePosition((p.x), p.y);
		pf.x = p.x;
		pf.y = p.y;
		//App->particle_system->create({ p.x,p.y }, { 0, -1 }, 100);
		App->particle_system->createEmitter(pf, "particles/smouk.xml");
	}

	if (App->input->getKey(SDL_SCANCODE_3) == KEY_DOWN || App->input->getKey(SDL_SCANCODE_E) == KEY_DOWN) {
		iPoint p;
		fPoint pf;
		App->input->getMousePosition((p.x), p.y);
		pf.x = p.x;
		pf.y = p.y;
		//App->particle_system->create({ p.x,p.y }, { 0, -1 }, 100);
		App->particle_system->createEmitter(pf, "particles/galaxy.xml");
	}


	App->render->blit(30, goku, 900, 100, NULL, 0.5f);


	return true;
}
