//
// Created by Вячеслав Кривенко on 30.10.2022.
//

#include <Victoriam/Utils/UJobWorker.hpp>

VISRCBEG

void CJobWorker::Join()
{
	if (m_WorkingThread.joinable())
		m_WorkingThread.join();
}

VISRCEND
