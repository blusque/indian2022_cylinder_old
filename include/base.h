#ifndef BASE_H
#define BASE_H
#include "pcl/common/common.h"
#include "Eigen/Core"

#define PI 3.1416
#define PI_2 1.5708
#define ZERO 0

namespace hough{
    typedef float vec3[3];
    typedef float vec2[2];
    typedef unsigned short uint16_t;

    namespace Base{
        class Tree{
        };

        class KdTree: public Tree
        {
        public:
        private:
            vec3 variance;
            enum Orient
            {
                X_Ori,
                Y_Ori,
                Z_Ori
            };
        };

        class Normal
        {
        public:
        };
    }
}

#endif // BASE_H