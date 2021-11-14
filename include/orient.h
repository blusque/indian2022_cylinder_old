#ifndef ORIENTATION_H
#define ORIENTATION_H
#include "hough.h"
#define RESOLUTION 3
#define SPHERE 360
#define HALF_SPHERE 180
#define RANGE (HALF_SPHERE / RESOLUTION)

namespace hough{

    class Orient: public Hough{
        public:
            Orient();
            Orient(const Orient &other);
            Orient(const PointCloud &pc, const GaussianSphere &voteMap);
            ~Orient();
            virtual vec2 vote() override;

        private:
            Matrix<float, 2, 2> vagueMatrix;
            PoinCloud _pc;
            std::vector<std::vector<Vote>> _voteMap(RANGE, std::vector<Vote> (RANGE));
            std::vector<std::vector<uint16_t>> _checkMap(RANGE, std::vector<uint16_t>(RANGE));
            VoteValuePtr _max;
            VoteListPtr _estimationList;

            NormalT _normalProcess();

            void _resetList(const SpherePoint &point);
            void _insertPoint(const SpherePoint &point);
            void _getOrient(vec2 &outputVec);
            void _gothroughList(SpherePoint &outputPoint);
    };
}

#endif // ORIENTATION_H