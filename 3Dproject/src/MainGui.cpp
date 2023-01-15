#include "MainGui.h"
#include "imgui.h"

void MainGui::show()
{
	ImGui::Begin(m_strname.c_str());                      

	if (ImGui::Button("Box"))
		m_eBtnType = eCreateBox;
	if (ImGui::Button("Sphere"))
		m_eBtnType = eCreateSphere;
	if (ImGui::Button("Sphere"))
		m_eBtnType = eCreateSphere;
	if (ImGui::Button("Clear"))
		m_eBtnType = eClear;
	ImGui::SameLine();
	ImGui::End();
}