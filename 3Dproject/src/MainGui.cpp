#include "MainGui.h"
#include "imgui.h"
#include "BoxObject.h"
void MainGui::show()
{
	ImGui::Begin(m_strname.c_str());                      

	if (ImGui::Button("Box"))
	{
		BoxObject box(10,10,10);
		box.Draw();
	}
	if (ImGui::Button("Sphere"))

	ImGui::SameLine();
	ImGui::End();
}