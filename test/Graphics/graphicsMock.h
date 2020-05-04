#ifndef NFS_NEXT_GEN_GRAPHICSMOCK_H
#define NFS_NEXT_GEN_GRAPHICSMOCK_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "graphics/graphic.h"

class MockEvent : public Event {
public:
    MOCK_METHOD0(getEvent, void());
};

class MockWindow : public Window {
public:
    MOCK_METHOD0(createRenderWindow, void());
    MOCK_METHOD0(render, void());
    MOCK_METHOD0(close, void());
};

#endif //NFS_NEXT_GEN_GRAPHICSMOCK_H
