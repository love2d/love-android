cmake_minimum_required(VERSION 3.21)

project(love-android LANGUAGES C CXX)

# Oboe
set(Oboe_DIR "${CMAKE_CURRENT_SOURCE_DIR}/oboe")

# Set LOVE
set(MEGA_LOVE "${CMAKE_CURRENT_SOURCE_DIR}/love")

# Finally, load megasource that will handle everything.
add_subdirectory(megasource)

# TODO: Third-party libraries.
