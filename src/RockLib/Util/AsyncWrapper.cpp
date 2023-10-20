//
// Created by Rocky Chen on 2023/10/3.
//

#include "RockLib/Util/AsyncWrapper.hpp"

namespace RockLib {

    AsyncWrapper::~AsyncWrapper() {
        this->task->remove();
        this->task.reset(nullptr);
    }

    void AsyncWrapper::start(const char* name){
        task = std::move(std::make_unique<pros::Task>(loopWrapper, this, name));
    }

    void AsyncWrapper::pause(){
        task->suspend();
    }

    void AsyncWrapper::resume(){
        task->resume();
    }

    void AsyncWrapper::stop(){
        task->remove();
        task = nullptr;
    }

    void AsyncWrapper::loopWrapper(void* args){
        if(args != nullptr){
            auto it = static_cast<AsyncWrapper*>(args);
            it->run();
        }
    }

} // RockLib