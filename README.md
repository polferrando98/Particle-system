
I am [Pol Ferrando Folch](https://www.linkedin.com/in/pol-ferrando-ab8170b9/), student of the [Bachelor’s Degree in 
Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s 
subject Project 2, under supervision of lecturer [Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

# Particle systems

## What is a Particle system?

In a 2D videogame, a Particle system is a technique that uses a large number of small sprites in order to represent fuzzy phenomena, such as fire, rain, explosions...

Even simple games benefit a lot from particle effects:

<iframe width="560" height="315" src="https://www.youtube.com/embed/_RqebZ5weG4?rel=0" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

But advanced particle systems can accomplish amazing things:

<iframe width="560" height="315" src="https://www.youtube.com/embed/2gp7-ejkwBQ?rel=0" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>


## How do they work?

Basically, a particle system needs three elements:

- Particles

- Emitters

- A container

### Particles

Particles are the small sprites. They have a combiantion of diverse atributes, the change of this atributes during the lifetime of a particle is a key ingredient in simulating the fuzzy effects. These atributes usually include:

- Scale
Useful to make things get smaller untill they dissapear

- Lifetime
How long will the particle last?

- Position variation
A value between this and 0 will be added or substracted of the position

- Velocity
The magnitude of the velocity

- Angle
The angle of the velocity

- Color
Usually given in rgb and alpha

- Blend mode
How particles mix they colors when they overlap

- Rotation



### Emitters

Emitters take care of creating and configuring the particles. These emitters also have configurable attributes like the frequency of emisssion or the number of particles created. But they also manage another key element in the simulation of effects: Randomness. Adding a variation in some of the atributes of the particles makes the system seem more natural and spontaneous.

![](https://raw.githubusercontent.com/polferrando98/Particle-system/master/docs/Blender3D_LoopingParticleFire.gif)


### Container

We need a container to keep track and update every particle and emitter. This container will also define what is the maximum number of particles on screen.

# Code Implementation

### Object Pool (The Container)

Particles need to be created fast and in large quantities. Dynamically allocating every particle not only is hardly efficient but it could cause memory fragmentation. In order to avoid this, we need to create an **Object Pool.** An Object Pool is a class that will allocate and hold reusable particles at startup. It can be easily done with just two lines of code:

```c++
static const int POOL_SIZE = 1000;

Particle particles_[POOL_SIZE];
```

## The process of creating a particle:

Every particle will need to have a function to know if it is alive or not:

```c++
bool Particle::inUse() const
{
	return framesLeft_ > 0;
}
```

Having this in mind, creating a particle just means "telling it" that it is "alive":

```c++
Particle* mdParticleSystem::create(ParticleInfo info)
{
	// Find an available particle.
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!particles_[i].inUse())
		{
			particles_[i].init(info);
			return &particles_[i];
		}
	}
}
```

In this process, we need to pass as an argument the information that defines the atributes of the Particle, in this case, the information is grouped in a struct.

### Particle Emitter

The class in charge of loading and passing this information, as well as creating the paricle itlsef, is the emmiter:

```c++
Particle * ParticleEmitter::createParticle()
{
	ParticleInfo info;

	configureParticle(info); //This loads the configuration from an XML

	emission_timer.start();

	return App->particle_system->create(info);
}

void ParticleEmitter::update(float dt)
{

	if (emission_timer.read() >= period) {
		createParticle();
		current_emissions++;
	}

	if (current_emissions >= max_emissions)
		active = false;

}
```

As we can see, the emitter creates particles based on a preiod that get out of the frequency that is loaded.

An example of how to configure the Scale of the particle:

### The Particle

```c++
void ParticleEmitter::configureParticle(ParticleInfo & info)
{
	float initial_scale = config.child("initial_scale").attribute("value").as_float(1);
	float initial_scale_var = config.child("initial_scale").attribute("variation").as_float(0);
	info.initial_scale = addOrSubstractRand(initial_scale, initial_scale_var); //This method can be used for variations in all the attributes

	//... Load the rest of the attributes
}

//Adds a random +-variation to the attribute
float ParticleEmitter::addOrSubstractRand(float atribute, int maxVariation) const 
{
	float atribute_variated = atribute;

	int variation = rand() % ((2 * maxVariation) + 1);

	atribute_variated -= maxVariation;
	atribute_variated += +variation;

	return atribute_variated;
}

```

The particle itself  will take care of changing it's attributes in relation with it's lifetime based on the initial and final values:

``` c++
void Particle::animate()
{
	//Here we calculate how the attributes should be:

	framesLeft_--;

	if (!inUse()) {
		App->textures->unload(texture);
		return;
	}

	lifetime_ratio = float(framesLeft_) / float(lifetime); 

	scale = calculateRatio(final_scale, initial_scale);

	current_spin = calculateRatio(final_spin, initial_spin);

	updateColors();

	pos.x += vel.x; //Simple linear motion
	pos.y += vel.y;
}

float Particle::calculateRatio(float final, float inital, float variation) const
{
	return (final - inital) * (1-lifetime_ratio) + inital; //Quick mafhs
}
```

Finally, it is the Container that will update and draw the Particle and it's Emitter:

```c++
void mdParticleSystem::updateParticles()
{
	particles_count = 0;
	for (int i = 0; i < POOL_SIZE; i++)
	{
		particles_[i].animate();

		if (!particles_[i].inUse())
			continue;

		particles_[i].Draw();
		particles_count++;
	}
}


```

## Creating and Deleting Emitters

```c++
void mdParticleSystem::createEmitter(fPoint pos, string config_path)
{
	ParticleEmitter* emitter = nullptr;

	emitter = new ParticleEmitter(pos, config_path);
	particle_emitters.push_back(emitter);
}
```

Creating an emitter is pretty straightforward, we just need to add it to a list in order to iterate all the emitters later and we will also need somewhere to get the data to configure it.

We can use the update loop to check if we need to delete them:

```c++
void mdParticleSystem::updateEmitters()
{
	list<ParticleEmitter*>::iterator it = particle_emitters.begin();
	while (it != particle_emitters.end())
	{
		if (!(*it)->active)
		{
			particle_emitters.erase(it++);  // alternatively, i = items.erase(i);
		}
		else
		{
			(*it)->update(0);
			++it;
		}
	}
}
```