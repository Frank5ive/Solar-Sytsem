#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <string>

// Constants
const float PI = 3.14159265359f;

// Class to represent a planet
class Planet {
public:
    float orbitRadius, orbitSpeed, size, r, g, b, angle;
    std::string name;
    bool hasRing;

    Planet(float orbitRadius, float orbitSpeed, float size, float r, float g, float b, const std::string& name, bool hasRing = false)
        : orbitRadius(orbitRadius), orbitSpeed(orbitSpeed), size(size), r(r), g(g), b(b), angle(0.0f), name(name), hasRing(hasRing) {}

    void update(float speedMultiplier) {
        angle += orbitSpeed * speedMultiplier;
        if (angle > 360.0f) angle -= 360.0f;
    }

    void render() {
        glPushMatrix();
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(orbitRadius, 0.0f, 0.0f);

        // Draw planet with gradient effect
        glColor3f(r, g, b);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= 360; i++) {
            float theta = i * PI / 180.0f;
            glColor3f(r * 0.8f, g * 0.8f, b * 0.8f); // Gradient
            glVertex2f(size * cos(theta), size * sin(theta));
        }
        glEnd();

        // Draw ring if the planet has one
        if (hasRing) {
            glColor3f(0.8f, 0.8f, 0.5f);
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i <= 360; i++) {
                float theta = i * PI / 180.0f;
                glVertex2f((size * 2.0f) * cos(theta), (size * 1.5f) * sin(theta));
            }
            glEnd();
        }

        // Draw label
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(size + 0.02f, 0.0f);
        for (char c : name) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }

        glPopMatrix();
    }
};

// Class to represent the solar system
class SolarSystem {
private:
    std::vector<Planet> planets;

public:
    SolarSystem() {
        planets.emplace_back(0.0f, 0.0f, 0.15f, 1.0f, 1.0f, 0.0f, "Sun");            // Sun
        planets.emplace_back(0.3f, 0.5f, 0.02f, 0.5f, 0.5f, 0.5f, "Mercury");        // Mercury
        planets.emplace_back(0.5f, 0.4f, 0.04f, 0.9f, 0.7f, 0.4f, "Venus");          // Venus
        planets.emplace_back(0.7f, 0.3f, 0.05f, 0.2f, 0.5f, 1.0f, "Earth");          // Earth
        planets.emplace_back(0.9f, 0.25f, 0.03f, 1.0f, 0.2f, 0.2f, "Mars");          // Mars
        planets.emplace_back(1.2f, 0.15f, 0.08f, 0.8f, 0.7f, 0.4f, "Jupiter");       // Jupiter
        planets.emplace_back(1.5f, 0.1f, 0.07f, 0.9f, 0.8f, 0.6f, "Saturn", true);   // Saturn
        planets.emplace_back(1.8f, 0.07f, 0.05f, 0.6f, 0.8f, 0.9f, "Uranus");        // Uranus
        planets.emplace_back(2.1f, 0.05f, 0.05f, 0.4f, 0.6f, 0.9f, "Neptune");       // Neptune
        planets.emplace_back(2.4f, 0.02f, 0.03f, 0.9f, 0.5f, 0.7f, "Pluto");         // Pluto (dwarf planet)
    }

    void update(float speedMultiplier) {
        for (size_t i = 1; i < planets.size(); ++i)
            planets[i].update(speedMultiplier);
    }

    void render() {
        planets[0].render(); // Render the Sun
        for (size_t i = 1; i < planets.size(); ++i)
            planets[i].render();
    }
};

// Global variables
SolarSystem solarSystem;
bool animate = true;
float zoomLevel = 1.0f, speedMultiplier = 1.0f, panX = 0.0f, panY = 0.0f;
std::vector<std::pair<float, float>> stars; // Star positions
GLuint starDisplayList;

// Function to initialize OpenGL
void initialize() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -1.5, 1.5);

    // Generate star positions
    for (int i = 0; i < 200; i++) {
        stars.emplace_back((rand() % 300 - 150) / 100.0f, (rand() % 300 - 150) / 100.0f);
    }

    // Create a display list for stars
    starDisplayList = glGenLists(1);
    glNewList(starDisplayList, GL_COMPILE);
    glBegin(GL_POINTS);
    for (const auto& star : stars) {
        glVertex2f(star.first, star.second);
    }
    glEnd();
    glEndList();
}

// Function to render the starry background
void renderStars() {
    glCallList(starDisplayList);
}

// Function to render the scene
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(zoomLevel, zoomLevel, 1.0f);
    glTranslatef(panX, panY, 0.0f);

    renderStars();
    solarSystem.render();

    glFlush();
}

// Function to update the scene
void updateScene(int value) {
    if (animate)
        solarSystem.update(speedMultiplier);
    glutPostRedisplay();
    glutTimerFunc(16, updateScene, 0);
}

// Keyboard input handling
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case ' ': // Pause/Resume animation
            animate = !animate;
            break;
        case '+': // Zoom in
            zoomLevel *= 1.1f;
            break;
        case '-': // Zoom out
            zoomLevel /= 1.1f;
            break;
        case 'f': // Increase speed
            speedMultiplier *= 1.1f;
            break;
        case 's': // Decrease speed
            speedMultiplier /= 1.1f;
            break;
        case 'r': // Reset
            zoomLevel = 1.0f;
            panX = panY = 0.0f;
            speedMultiplier = 1.0f;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// Mouse input handling for panning
void handleMouseMotion(int x, int y) {
    static int lastMouseX = x, lastMouseY = y;
    float deltaX = (x - lastMouseX) / 300.0f;
    float deltaY = (lastMouseY - y) / 300.0f;

    panX += deltaX;
    panY += deltaY;

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Enhanced Solar System");

    initialize();

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(handleKeyboard);
    glutMotionFunc(handleMouseMotion);
    glutTimerFunc(16, updateScene, 0);

    glutMainLoop();
    return 0;
}
