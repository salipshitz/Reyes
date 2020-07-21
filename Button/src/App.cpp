#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <glfw/glfw3.h>
#include <glad/glad.h>

const int BITMAP_W = 512;
const int BITMAP_H = 512;

const float scale[]{24.f, 14.f};

const int sf[]{0, 1, 2, 0, 1, 2};

stbtt_aligned_quad q;
float x;
float y;

GLFWwindow *window;

int ww = 1024;
int wh = 768;

int fbw = ww;
int fbh = wh;

int font_tex;

stbtt_packedchar *charData;

int font = 3;

bool black_on_white;
bool integer_align;
bool translating;
bool rotating;

bool supportsSRGB;
bool srgb;

float rotate, translate;

bool show_tex;

int main()
{
    if (!glfwInit())
        __debugbreak();

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, false);
    glfwWindowHint(GLFW_RESIZABLE, true);
    window = glfwCreateWindow(ww, wh, "Text Test", NULL, NULL);
    if (!window)
        __debugbreak();

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        ww = width;
        wh = height;
    });
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        fbw = width;
        fbh = height;
    });

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (action == GLFW_RELEASE)
            return;

        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_O:
            font = (font + 1) % 3 + (font / 3) * 3;
            break;
        case GLFW_KEY_S:
            font = (font + 3) % 6;
            break;
        case GLFW_KEY_T:
            translating = !translating;
            translate = 0.f;
            break;
        case GLFW_KEY_R:
            rotating = !rotating;
            rotate = 0.f;
            break;
        case GLFW_KEY_P:
            integer_align = !integer_align;
            break;
        case GLFW_KEY_G:
            if (!supportsSRGB)
                break;

            srgb = !srgb;
            if (srgb)
                glEnable(GL_FRAMEBUFFER_SRGB);
            else
                glDisable(GL_FRAMEBUFFER_SRGB);
            break;
        case GLFW_KEY_V:
            show_tex = !show_tex;
            break;
        case GLFW_KEY_B:
            black_on_white = !black_on_white;
            break;
        default:
            break;
        }
    });

    const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (vidmode->width - ww) / 2, (vidmode->height - wh) / 2);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(1);
    glfwShowWindow(window);

    supportsSRGB = false;
}