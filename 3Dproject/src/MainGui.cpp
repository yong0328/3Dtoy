#include "MainGui.h"
#include "imgui.h"

void MainGui::show()
{
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(150, main_viewport->Size.y), ImGuiCond_Always);
	ImGui::Begin(m_strname.c_str());                      

	if (curShowMode == SHOWMODE::SHOW2D)
	{
		if (ImGui::Button("Bezier curve"))
			m_eBtnType2D = eBizierCurve;
			//std::cout << "Draw Bezier curve" << std::endl;
		if (ImGui::Button("B spline curve"))
			m_eBtnType2D = eBspline;
			//std::cout << "Draw B spline curve" << std::endl;
		if (ImGui::Button("NUBRS curve"))
			m_eBtnType2D = eNurbs;
			//std::cout << "Draw NUBRS curve" << std::endl;
		if (ImGui::Button("Clear"))
			_vPt.clear();
	}
	else
	{
		if (ImGui::Button("Box"))
			m_eBtnType3D = eCreateBox;
		if (ImGui::Button("Sphere"))
			m_eBtnType3D = eCreateSphere;
		if (ImGui::Button("Sphere"))
			m_eBtnType3D = eCreateSphere;
		if (ImGui::Button("Clear"))
			m_eBtnType3D = eClear;
	}
	ImGui::End();
}