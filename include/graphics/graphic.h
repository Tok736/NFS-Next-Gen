#ifndef NFS_NEXT_GEN_GRAPHIC_H
#define NFS_NEXT_GEN_GRAPHIC_H

class Event {
public:
    virtual void getEvent() = 0;
};

class Window {
public:
    virtual void createRenderWindow() = 0;
    virtual void render() = 0;
    virtual void close() = 0;
};

#endif //NFS_NEXT_GEN_GRAPHIC_H
