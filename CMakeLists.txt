cmake_minimum_required(VERSION 3.12)
project(Project1)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

include_directories(.)
include_directories(Attack)
include_directories(XML_Parser)
include_directories(XML_Tests)

add_executable(Project1
        Attack/Attack.cpp
        Attack/Attack.hpp
        XML_Parser/rapidxml.hpp
        XML_Parser/rapidxml_iterators.hpp
        XML_Parser/rapidxml_print.hpp
        XML_Parser/rapidxml_utils.hpp
        Border.cpp
        Border.hpp
        builder.cpp
        builder.hpp
        Condition.cpp
        Condition.hpp
        Container.cpp
        Container.hpp
        Creature.cpp
        Creature.hpp
        Element.cpp
        Element.hpp
        engine.cpp
        engine.hpp
        Item.cpp
        Item.hpp
        main.cpp
        Person.cpp
        Person.hpp
        Room.cpp
        Room.hpp
        Trigger.cpp
        Trigger.hpp
        util.hpp)
