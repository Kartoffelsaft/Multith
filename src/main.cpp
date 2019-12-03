#include <cstdio>
#include <thread>
#include "./actor.hpp"

struct testActorBody
{
    int internal;

    testActorBody(int n) : internal{n} {}

    int testFunc(int external)
    {
        printf("int: %i\next: %i\n", internal, external);
        return internal * external;
    }

    void increment()
    {
        internal++;
    }
};

int main()
{
    Actor<testActorBody> a{13};

    auto t1 = a.call(&testActorBody::testFunc, 17);
    printf("ret: %i\n\n", t1.get());

    a.call(&testActorBody::increment);

    auto t2 = a.call(&testActorBody::testFunc, 17);
    printf("ret: %i\n", t2.get());

    return 0;
}
