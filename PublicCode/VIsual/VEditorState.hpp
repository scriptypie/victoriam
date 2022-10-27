//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VISUAL_EDITORSTATE_HPP
#define VISUAL_EDITORSTATE_HPP

#include <Victoriam/Application/AAppState.hpp>

VISRCBEG

class VEditorState : public CAppState {
public:
	~VEditorState() override;

	void OnCreate() override;

	void OnUpdate(const Float32& dt) override;

	void OnDestroy() override;

	void OnUpdateGUI() override;
};

VISRCEND

#endif //VISUAL_EDITORSTATE_HPP
