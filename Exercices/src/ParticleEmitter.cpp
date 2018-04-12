#include "ParticleEmitter.h"
#include "Application.h"
#include "mdFilesystem.h"
#include "DebLog.h"
#include <cstdlib>
#include <time.h>     



ParticleEmitter::ParticleEmitter(fPoint pos, string config_path)
{
	//TODO 3.1 Load the frequency from the xml and calculate the period
	///Now you should see emitters emitting faster
	start_pos = pos;
	emission_timer.start();
	srand(time(NULL));

	loadConfig(config_file, config, config_path);

	frequency = 1;
	period = 1000; //Change this line and calculate it, leave it in ms

	max_emissions = config.child("max_emissions").attribute("value").as_int(1000);
	current_emissions = 0;

	type = (emmiterType)config.child("type").attribute("value").as_int(0);

	if (type == EXPLOSION) {
		//TODO 5.1 Create all the particles at once and make sure that they are not recreated later. You should use the active atribute
		///When you finish you should be able to see an explosion pressing "e"
	}
}


ParticleEmitter::~ParticleEmitter()
{
}

Particle * ParticleEmitter::createParticle()
{
	ParticleInfo info;

	configureParticle(info); //This loads the configuration from an XML

	emission_timer.start();

	return App->particle_system->create(info);
}

void ParticleEmitter::update(float dt)
{
	//TODO 2 Create Particles when needed using the emission_timer and the period
	///You should see particles doing strange things when you finish. Try pressing 1, 2 or 3

}

float ParticleEmitter::addOrSubstractRand(float atribute, int maxVariation) const
{
	//TODO 4: Return the atribute with +- a random number beween 0 and maxVariation
	///When you finish you should be able to see the variations

	float atribute_variated = atribute;


	return atribute_variated;
}

bool ParticleEmitter::loadConfig(pugi::xml_document & config_file, pugi::xml_node & config_node, string path)
{
	char* buffer;
	int size = App->filesystem->load(path.c_str(), &buffer);
	pugi::xml_parse_result result = config_file.load_buffer(buffer, size);
	if (size != 0)
		RELEASE(buffer);

	if (result == NULL) {
		LOG("Application : Could not load xml - %s", result.description());
		return false;
	}
	else {
		config_node = config_file.child("config");
		return true;
	}
}

void ParticleEmitter::configureParticle(ParticleInfo & info)
{
	//TODO 3.2 Load the hardcoded atributes from the xml
	///When you finish emitter should behave more differently
	info.angle = 270;

	info.vel_mag = 0;

	fPoint pos_var;
	pos_var.x = config.child("pos_var").attribute("x").as_float(0);
	pos_var.y = config.child("pos_var").attribute("y").as_float(0);

	info.pos.x = addOrSubstractRand(start_pos.x, pos_var.x);
	info.pos.y = addOrSubstractRand(start_pos.y, pos_var.y);

	int lifetime = config.child("lifetime").attribute("value").as_float(100);
	int lifetime_var = config.child("lifetime").attribute("variation").as_float(0);
	info.lifetime = addOrSubstractRand(lifetime, lifetime_var);

	float initial_scale = config.child("initial_scale").attribute("value").as_float(1);
	float initial_scale_var = config.child("initial_scale").attribute("variation").as_float(0);
	info.initial_scale = addOrSubstractRand(initial_scale, initial_scale_var);

	float final_scale = config.child("final_scale").attribute("value").as_float(1);
	float final_scale_var = config.child("final_scale").attribute("variation").as_float(0);
	info.final_scale = addOrSubstractRand(final_scale, final_scale_var);

	info.initial_color.r = config.child("initial_color").attribute("r").as_int(255);
	info.initial_color.g = config.child("initial_color").attribute("g").as_int(255);
	info.initial_color.b = config.child("initial_color").attribute("b").as_int(255);
	info.initial_color.alpha = config.child("initial_color").attribute("a").as_int(255);

	info.final_color.r = 255;
	info.final_color.g = 255;
	info.final_color.b = 255;
	info.final_color.alpha = 255;

	info.blend = (SDL_BlendMode)config.child("blend_mode").attribute("value").as_int(0);

	info.texture_path = config.child("texture_path").attribute("value").as_string("Error path");

	info.initial_spin = config.child("spin").attribute("initial").as_float(0);
	float final_spin = config.child("spin").attribute("final").as_float(0);
	float final_spin_var = config.child("spin").attribute("variation").as_float(0);
	info.final_spin = addOrSubstractRand(final_spin, final_spin_var);

	info.draw_priority = config.child("draw_priority").attribute("value").as_int(1);
}

