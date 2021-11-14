#include "pointcloud.h"

namespace hough
{
    void PointCloud::normalCompute()
    {
        // 点云降噪（后面补充）

        // 建立点云法线识别器
        pcl::NormalEstimation<PointT, pcl::Normal> ne;
        ne.setInputCloud(pc);

        // 生成kd树，并传给之前建立的法线识别器
        pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>());
        ne.setSearchMethod(tree);

        // 设置搜索半径为30cm
        ne.setSearchRadius(0.03);
        ne.compute(*(normals));
    }

    void PointCloud::vote(GaussianSphere &sphere)
    {
        // 投票
        float phi, theta;
        for (auto vec : normals)
        {
            for (int i = 0; i < 180; i++)
            {
                theta = (float)i / 180.0 * PI;
                phi = atan(-(float)vec.n_z / ((float)vec.n_x * cos(theta) + (float)vec.n_y) * sin(theta));
                j = (int)(phi / PI * 180.0);
                sphere.voteMap[i] += 1;
            }
        }
        // 时间复杂度O(n^2)，可以考虑改用gpu并行计算或更改算法
    }
}