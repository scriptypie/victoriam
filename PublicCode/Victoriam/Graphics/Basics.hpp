//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_BASICS_HPP
#define VICTORIAM_BASICS_HPP

#include <Victoriam/Core/CBase.hpp>


VISRCBEG

/**
 * Opaque object that handles all commands to draw/transfer/etc...
 */
VIDECL typedef struct TSCommandBuffer* SCommandBuffer;
/**
 * Opaque object that handles created and associated descriptors.
 */
VIDECL typedef struct TSDescriptorSet* SDescriptorSet;

VIDECL typedef struct TSImageViewObject* SImageViewObject;

VISRCEND

#endif //VICTORIAM_BASICS_HPP
