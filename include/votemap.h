#ifndef VOTEMAP_H
#define VOTEMAP_H
#include "base.h"

namespace hough{

    class GaussianSphere{
    public:
        GaussianSphere();
        GaussianSphere(const GaussianSphere &other);
        ~GaussianSphere();

    private:
        VoteMap vmp;
    };
}

#endif // VOTEMAP_H