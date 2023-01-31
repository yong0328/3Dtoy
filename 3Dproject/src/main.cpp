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
#include "Line.h"
#include "BezierCurve.h"
// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

SHOWMODE curShowMode = SHOWMODE::SHOW3D;
glm::mat4x4 _viewMatrix;
glm::mat4x4 _projectMatrix;
CubeMap gCubeMap;
unsigned int cubemapID;
ButtonType2D m_eBtnType2D;
ButtonType3D m_eBtnType3D;
std::vector<Point3D> _vPt;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
//std::shared_ptr<Line> m_DrawLine = nullptr;
void MainWndRender(const MainGui& Gui)
{
	if (curShowMode == SHOW2D)
	{
		switch (m_eBtnType2D)
		{
		case eBizierCurve:
		{
			static BezierCurve line;
			line.Render();
		}
		default:
			break;
		}
	}
	else
	{
		switch (m_eBtnType3D)
		{
		case eCreateBox:
		{
			static BoxObject box(10, 10, 10);
			box.Render();
		}
		default:
			break;
		}
	}
}
void processMouseInput(GLFWwindow* window, int button, int action, int mods)
{
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	if (main_viewport == nullptr)
		return;
	if (curShowMode == SHOWMODE::SHOW2D)
	{
		if (m_eBtnType2D == ButtonType2D::eBizierCurve)
		{
			if (action == GLFW_PRESS)
			{
				if (button == GLFW_MOUSE_BUTTON_LEFT)
				{
					double xpos = 0.0;
					double ypos = 0.0;
					glfwGetCursorPos(window, &xpos, &ypos);
					double localXpos = xpos - main_viewport->WorkPos.x;
					double localYpos = main_viewport->WorkSize.y - ypos + main_viewport->WorkPos.y;
					double projectionXPos = localXpos * 2 / main_viewport->WorkSize.x - 1;
					double projectionYPos = localYpos * 2 / main_viewport->WorkSize.y - 1;
					glm::mat4x4 inverViewMat = glm::inverse(_viewMatrix);
					glm::mat4x4 inverProjMat = glm::inverse(_projectMatrix);
					glm::vec4 projpos(projectionXPos,projectionYPos, 0.5,1.0);
					glm::vec4 pos =  inverViewMat* inverProjMat* projpos;
					_vPt.push_back(Point3D(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w));
				}
			}
		}

	}
	
}
int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
	
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, processMouseInput);
    glfwSwapInterval(1); // Enable vsync
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

	gCubeMap.initCubeMap();
    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	MainGui mainGui("Function list");
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
		
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
	    //glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//static float fRotAngle = 0.0f;
		//fRotAngle += 0.5f;
		//_viewMatrix = glm::rotate(viewMatrix,glm::radians(fRotAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		if (curShowMode == SHOWMODE::SHOW2D)
		{
			//_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 200.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			//_projectMatrix = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 1000.0f);
			_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			_projectMatrix = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 1000.0f);
			
		}
		else
		{
			_viewMatrix = glm::lookAt(glm::vec3(3.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			_projectMatrix = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 1000.0f);

			gCubeMap.Render();
		}
		mainGui.show();
		// Rendering
		MainWndRender(mainGui);
		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 1100, main_viewport->WorkPos.y + 10), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(150, 55), ImGuiCond_Always);
		ImGui::Begin("Show Mode Select");
		if (ImGui::Button("2D"))
			curShowMode = SHOWMODE::SHOW2D;
		ImGui::SameLine();
		if (ImGui::Button("3D"))
			curShowMode = SHOWMODE::SHOW3D;
		ImGui::SameLine();
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
