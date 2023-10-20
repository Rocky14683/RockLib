//
// Created by Rocky Chen on 2023/10/3.
//
#pragma once
#include "pros/rtos.hpp"
#include <memory>

namespace RockLib {

    class AsyncWrapper {
    protected:
        AsyncWrapper() = default;
        virtual ~AsyncWrapper();

        virtual void run() = 0;

    public:
        virtual void start(const char* name);

        virtual void pause();

        virtual void resume();

        virtual void stop();

    private:
        static void loopWrapper(void* args);
        std::unique_ptr<pros::Task> task = nullptr;

    };

} // RockLib
