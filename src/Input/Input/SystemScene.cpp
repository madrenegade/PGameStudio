/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 23, 2011, 8:08 AM
 */

#include "Input/SystemScene.h"
#include "Input/InputTask.h"

#include "Utilities/Memory/MemoryPoolSettings.h"

using namespace Utilities::Memory;

namespace Input
{
    const std::string SystemScene::EXTENSION("input");

    SystemScene::SystemScene()
    {
    }

    SystemScene::~SystemScene()
    {
    }

    void SystemScene::addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties)
    {
        MemoryPoolSettings inputPool(1 * KByte, 1 * KByte, 128 * Byte,
            1 * KByte, 1 * KByte, 128 * Byte,
            1 * KByte, 1 * KByte, 128 * Byte);
        inputPool.addOptionsTo(properties, "Input");
    }

    const char* SystemScene::getSceneFileExtension() const
    {
        return EXTENSION.c_str();
    }

    void SystemScene::load(const Utilities::IO::File& file)
    {

    }

    void SystemScene::initialize()
    {

    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) InputTask();
    }
}
