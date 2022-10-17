//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VISUAL_EDITORSTATE_HPP
#define VISUAL_EDITORSTATE_HPP

#include <Victoriam/Application/AppState.hpp>

VISRCBEG

class EditorState : public cAppState {
public:
	~EditorState() override;

	void OnCreate() override;

	void OnUpdate() override;

	void OnDestroy() override;

	void OnUpdateGUI() override;
};

VISRCEND

#endif //VISUAL_EDITORSTATE_HPP
