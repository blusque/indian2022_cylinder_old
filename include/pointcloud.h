#ifndef POINTCLOUD_H
#define POINTCLOUD_H
#include "base.h"
#include <pcl/common/common.h>

namespace hough{
    typedef pcl::PointXYZRGBNormal PointT;
    typedef pcl::PointCloud<PointT> PointCloudT;
    typedef PointCloudT::Ptr PointCloudPtr;

    class PointCloud{
    public:
        void normalCompute();

        void showNormals();

    private:
        PointCloudPtr pc;
        std::vector<pcl::Normal> normals;
        pcl::PointCloud<pcl::Normal> normalsPC;
    };
}

#endif // POINTCLOUD_H