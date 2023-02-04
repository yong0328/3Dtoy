// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "BoxObject.h"
#include "Base.h"
#include "CubeMap.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "MainGui.h"
#include "Camera.h"
// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
glm::mat4x4 _projectMatrix;
//skybox
CubeMap gCubeMap;
unsigned int cubemapID;

Camera _camera;
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
void MainWndRender(MainGui& Gui)
{
	switch (Gui.m_eBtnType)
	{
	case eCreateBox:
	{
		BoxObject box(10, 10, 10);
		box.Render();
		break;
	}
	case eClear:
	{
		Gui.m_eBtnType = eNone;
		break;
	}
	default:
		break;
	}
}
void keyboardCallback(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		_camera.Move(MOVE_RIGHT);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		_camera.Move(MOVE_LEFT);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		_camera.Move(MOVE_FRONT);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		_camera.Move(MOVE_BACK);
}
void mouseEventProcess(ImGuiIO& io)
{
	if (io.MouseDown[0])
		std::cout << "left press" << std::endl;
	if (io.MouseDown[1])
		std::cout << "right press" << std::endl;
}
void MouseScrollEventProcess(GLFWwindow* window,double x,double y)
{
	if (y > 0)
		_camera.MouseMidScroll(SCROLL_FRONT);
	else 
		_camera.MouseMidScroll(SCROLL_BACK);
}
int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
	
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);


    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

	//mouse scroll callback
	glfwSetScrollCallback(window, MouseScrollEventProcess);
	gCubeMap.initCubeMap();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	MainGui mainGui("main");
	_camera.lookAt(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
		keyboardCallback(window);
		mouseEventProcess(io);
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
		
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	    //glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//static float fRotAngle = 0.0f;  
		//fRotAngle += 0.5f;
		//_viewMatrix = glm::rotate(viewMatrix,glm::radians(fRotAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		
		_camera.update();
		_projectMatrix = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 100.0f);
		
		gCubeMap.Render();
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();
		{
			mainGui.show();
		}

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		MainWndRender(mainGui);
        glfwSwapBuffers(window);
		glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
