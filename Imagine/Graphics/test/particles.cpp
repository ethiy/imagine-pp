// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#include <Imagine/Graphics.h>
using namespace Imagine;

#ifdef IMAGINE_OPENGL

// Particles
struct ParticleParameters {
    // Physics
    int amount;
    int life;
    float speed;
    float weight;
    int size;
    int quality;
    Color color;
    FloatVector3 forces;
    int* currentLife;
    FloatVector3* currentSpeed;
    FloatPoint3* currentPosition;

    // Source & beam
    FloatPoint3 source;
    FloatVector3 direction;
    float radius;
    float angle;
    float sharpness;
};
float theta = 0.0;
class Particle {
private:
    bool active;
    ParticleParameters p;
    Mesh* meshes;
    FloatVector3 axe1, axe2, axe3;
    void reset(int id);
    FloatVector3 randomVector(float value);
    void initialize();
    void makeAxes();


public:
    Particle(int amount=30, int life=50, float speed=0.1f, float weight=1,
             int size=1, int quality=2, Color color=Color(0,100,255),
             FloatPoint3 source=FloatPoint3(0,-10,0), float radius=3,
             FloatVector3 direction=FloatVector3(0,1,0),
             float angle=0.2f, float sharpness=0,
             FloatVector3 forces=FloatVector3(0,0.02f,0));
    void draw();
    void start();
    void stop();

};

// Particle.
// Constructor for particles generation.
// \param amount Quantity of particles
// \param life Duration of each particle before regeneration
// \param speed Speed (in 3D vector units)
// \param weight Particles weight.
// \param size Particles size.
// \param quality Sphere resolution.
// \param color Particles color.
// \param source Broadcast point.
// \param radius Transmitter radius.
// \param direction Diffusion direction.
// \param angle Diffusion cone beam peak half-angle.
// \param sharpness Accuracy in cone beam form.
// \param forces Gravity.
Particle::Particle(int amount, int life, float speed, float weight, int size, int quality, Color color, FloatPoint3 source, float radius, FloatVector3 direction, float angle, float sharpness, FloatVector3 forces)
{
    p.amount = amount;
    p.life = life;
    p.speed = speed;
    p.weight = weight;
    p.size = size;
    p.quality = quality + 1;
    p.color = color;

    p.source = source;
    p.radius = radius;
    p.direction = direction;

    p.angle = tan(angle);
    p.sharpness = sharpness;

    p.forces = forces;

    initialize();
}

void Particle::start()
{
    active = true;
    for (int i(0) ; i < p.amount ; i++) showMesh(meshes[i], false);
}

void Particle::stop()
{
    active = false;
    for (int i(0) ; i < p.amount ; i++) hideMesh(meshes[i], false);
}

void Particle::makeAxes()
{
    axe1 = p.direction / norm(p.direction);
    axe2 = FloatVector3(-axe1.y(), axe1.x(), axe1.z());
    axe3 = axe1^axe2;
}

void Particle::initialize()
{
    // Creates axes w/ direction for the cone beam
    makeAxes();

    p.currentLife = new int[p.amount];
    p.currentSpeed = new FloatVector3[p.amount];
    p.currentPosition = new FloatPoint3[p.amount];

    meshes = new Mesh[p.amount];

    for (int i(0) ; i < p.amount ; i++)
    {
        meshes[i] = Mesh::Sphere(p.source + randomVector(p.radius), p.size, p.quality);
        meshes[i].setColor(p.color);
        reset(i);
        p.currentLife[i] = 1 + rand()%p.life;
    }
}

void Particle::draw()
{
    if (active == true) for (int i(0) ; i < p.amount ; i++)
    {
        hideMesh(meshes[i], false);
        if (--p.currentLife[i] == 0) reset(i);
        p.currentSpeed[i] += p.forces / p.weight;
        p.currentPosition[i] += p.currentSpeed[i];
        meshes[i] = Mesh::Sphere(p.currentPosition[i], p.size, p.quality);
        meshes[i].setColor(p.color);
        meshes[i].setOpacity(p.currentLife[i] / (float)p.life);
        showMesh(meshes[i], false);
    }
}

float randomValue(float max)
{
    int randomSign = (rand() % 2 == 0) ? 1 : -1;
    return float(rand() % (int) (100 * max)) * randomSign / 100;
}

float randomAngle()
{
    return ((float) (rand() % 1000)) / 100.0f;
}

FloatVector3 Particle::randomVector(float value)
{
    if (value == 0)
        return FloatVector3(0, 0, 0);
    return randomValue(value) * axe2 + randomValue(value) * axe3;
}

void Particle::reset(int id)
{
    p.currentLife[id] = p.life;
    p.currentPosition[id] = p.source + randomVector(p.radius);

    DoublePoint3 a = DoublePoint3(0,0,0) + DoubleVector3(1,1,1);

    float theta = randomAngle();
    p.currentSpeed[id] = (axe1 + (p.angle * cos(theta)) * axe2 + (p.angle * sin(theta)) * axe3 + randomVector(p.sharpness));
    p.currentSpeed[id] *= p.speed / norm(p.currentSpeed[id]);
}


void animateCamera(){
    DoublePoint3 pos(0,0,0);
    DoubleVector3 dir (-10,0,0);
    DoubleVector3 up(0,1,0);

   for (int i=0;i<200;i++){
        theta +=0.1f;
        DoubleVector3 dir (10*cos(theta),0,10*sin(theta));
        setCamera(pos,dir,up);
        milliSleep(20);
    }
}

int main(int argc, char** argv)
{
    Window glWindow = openWindow3D(512, 512, "3D Window");
    setActiveWindow(glWindow);
    setBackGround(Color(0,0,0));
    std::string fileName = srcPath("bunny.obj");
    Mesh mesh;
    readMeshFromObjFile(mesh, fileName);
    mesh.setColor(Color(255,100,0));
    showMesh(mesh);
    animateCamera();
    Particle particles1; // creates particles
    particles1.start();

    for (int i=0;i<200;i++)
    {
        particles1.draw();
        milliSleep(20);
    }
    anyClick();
    particles1.stop();
    closeWindow(glWindow);
    endGraphics();
    return 0;
}

#else

int main(int argc, char** argv)
{
    openWindow(512,64,argv[0]);
    drawString(0,20,"Imagine++ was configured with no OpenGL support", RED);
    drawString(0,40,"This test does nothing...", RED);
    endGraphics();
    return 0;
}

#endif
