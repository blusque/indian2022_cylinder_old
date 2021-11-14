#ifndef HOUGH_H
#define HOUGH_H
#include "base.h"

namespace hough{
    typedef pcl::PointXYZRGBNormal PointT;
    typedef pcl::PointCloud<PointT> PointCloudT;
    typedef PointCloudT::Ptr PointCloudPtr;
    typedef unsigned short uint16_t;
    typedef uint16_t Vote;
    

    struct SpherePoint{
        uint16_t theta, phi;
        inline SpherePoint(uint16_t theta, uint16_t phi){
            this->theta = theta, this->phi = phi;
        }

        inline SpherePoint(const SpherePoint &other): theta(other.theta), phi(other.phi){}

        inline void operator=(const SpherePoint &other){
            theta = other.theta;
            phi = other.phi;
        }

        inline void operator+=(const SpherePoint &other){
            theta += other.theta;
            phi += other.phi;
        }

        inline void operator/=(uint16_t num){
            theta /= num;
            phi /= num;
        }

        inline SpherePoint operator/(const SpherePoint &point1, uint16_t num){
            SpherePoint p2(p1);
            p2 /= num;
            return p2;
        }
    };

    struct ComparePoint{
        inline bool operator()(const SpherePoint &p1, const SpherePoint &p2){
            return ((p1.theta < p2.theta) || (p1.theta == p2.theta && p1.phi < p2.phi));
        }
    };

    typedef std::vector<SpherePoint> NormalT;
    // typedef std::vector<SpherePoint> VoteList;
    typedef std::map<SpherePoint, Vote, ComparePoint> VoteMap;

    struct VoteList{
        SpherePoint point;
        VoteList *next;
    };

    struct VoteValue{
        Vote vote;
        VoteList *list;
        VoteValue *next;
    };

    typedef std::shared_ptr<VoteValue> VoteValuePtr;
    typedef std::shared_ptr<VoteList> VoteListPtr;

    class Hough{
        public:
            Hough();
            Hough(const Hough &other);
            ~Hough();
            virtual vec2 vote() = 0;
    };
}

#endif // HOUGH_H