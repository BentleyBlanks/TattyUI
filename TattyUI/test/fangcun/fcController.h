#ifndef FCCONTROLLER_H
#define FCCONTROLLER_H

#include <TattyUI/common/t2Vector2.h>
using namespace TattyUI;

class fcRay;
class fcCircle;
class fcController
{
public:
    static fcController* getInstace();

    void addCircle(fcCircle* c);

    void deleteCircle(fcCircle* c);

    void draw();
    
    t2Vector2f* intersection(fcRay &r);

protected:
    vector<fcCircle*> circles;

private:
    // 非常严格的单例模式
    fcController();
    fcController(const fcController&) {}
    ~fcController() {}
    fcController& operator=(const fcController& event) const {}
};


#endif