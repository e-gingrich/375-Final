/// \file KeyBuffer.cpp
/// \brief Initializiation of KeyBuffer class and any associated global functions.
/// \author Ethan Gingrich
/// \version A04

#include "KeyBuffer.hpp"

KeyBuffer::KeyBuffer () 
{
    reset();
}

void 
KeyBuffer::setKeyDown (int key)
{
    keyIsPressed[key] = true;
}

void
KeyBuffer::reset () 
{
    int i = 0;
    int size = sizeof(keyIsPressed) / sizeof(keyIsPressed[0]);
    while (i < size)
    {
        keyIsPressed[i] = false;
        i++;
    }
}

void
KeyBuffer::setKeyUp (int key) 
{
    keyIsPressed[key] = false;
}

bool
KeyBuffer::isKeyDown (int key) const
{
    return keyIsPressed[key];
}