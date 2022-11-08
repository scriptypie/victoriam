//
// Created by Вячеслав Кривенко on 31.10.2022.
//

#include <Victoriam/Graphics/Structs/GVertex.hpp>

VISRCBEG

Bool operator==(const SVertex& a, const SVertex& b)
{
	return
	a.Position == b.Position &&
	a.Color    == b.Color &&
	a.Normal   == b.Normal &&
	a.UV       == b.UV;
}

Bool operator!=(const SVertex& a, const SVertex& b)
{
	return !(a == b);
}

VISRCEND
