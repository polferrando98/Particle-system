
I am [Pol Ferrando Folch](https://www.linkedin.com/in/pol-ferrando-ab8170b9/), student of the [Bachelor’s Degree in 
Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s 
subject Project 2, under supervision of lecturer [Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

# Particle systems

## What is a Particle system?

In a 2D videogame, a Particle system is a technique that uses a large number of small sprites in order to represent fuzzy phenomena, such as fire, rain, explosions...

Even simple games benefit a lot from particle effects:


<iframe width="560" height="315" src="https://www.youtube.com/embed/m_kPN9QeHXs?rel=0" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>


## How do they work

Basically, a particle system needs three elements:

- Particles

- Emitters

- A container

### Particles

Particles are the small sprites. They have a combiantion of diverse atributes, the change of this atributes during the lifetime of a particle is a key ingredient in simulating the fuzzy effects. These atributes usually include:

- Scale

- Lifetime

- Position

- Velocity

- Angle

- Color

- Blend mode

- Rotation


### Emitters

Emitters take care of creating and configuring the particles. These emitters also have configurable attributes like the frequency of emisssion or the number of particles created. But they also manage another key element in the simulation of effects: Randomness. Adding a variation in some of the atributes of the particles makes the system seem more natural and spontaneous.

![](https://raw.githubusercontent.com/polferrando98/Particle-system/master/docs/Blender3D_LoopingParticleFire.gif)


### Container

We need a container to keep track and update every particle and emitter. This container will also define what is the maximum number of particles on screen.

