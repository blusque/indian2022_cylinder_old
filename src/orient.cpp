#include "orient.h"


namespace{
    Orient::Orient(const PointCloud &pc, const GaussianSphere &voteMap):
    _pc(pc)
    {
        vagueMatrix << (float)1 / (float)RESOLUTION, ZERO, ZERO, (float)1 / (float)RESOLUTION;
        _max.reset(new VoteValue);
        _estimationList.reset(new VoteList);
        for (auto vec : _voteMap)
        {
            for (auto vote : vec)
            {
                vote = 0;
            }
        }
        for (auto vec : _checkMap)
        {
            for (auto cell : vec)
            {
                cell = 0;
            }
        }
    }

    vec2 Orient::vote()
    {
        
        NormalT normalsProcessed;

        // 法线处理：对法线进行模糊处理，3°之内的算同一条法线
        normalsProcessed = _normalProcess();

        // 处理过后的法线加入投票
        // 遍历法线
        for (auto normal : normalsProcessed){
            // 遍历theta
            // 60：180 / 3，180°的半球，3°的分辨率，这里需要更改为宏定义或
            for (int i = 0; i < RANGE; i++){
                float theta, phi;
                
                theta = (float)i / (float)RANGE * PI;
                phi = atan(-(float)vec.n_z / ((float)vec.n_x * cos(theta) + (float)vec.n_y) * sin(theta));
                j = (int)(phi / PI * (float)RANGE);
                
                // 投票
                _voteMap[i][j] += 1;
                Vote vote = _voteMap[i][j];
                //
                SpherePoint point((uint16_t)i, (uint16_t)j);
                if (vote > _max->vote){
                    // 更新最大投票数点队列
                    _resetList(point);
                }
                else if (vote == _max->vote){
                    // 将该点插入最大投票数点队列
                    _insertPoint(point);
                }
            }
        }

        vec2 result;
        // 获取圆柱轴线方向
        _getOrient(result);

        return result;
    }

    // 待完成
    NormalT Orient::_normalProcess()
    {
        NormalT result;
        for (auto normal : _pc.normals)
        {
            normal.normal_x
        }
    }
    //

    void Orient::_getOrient(vec2 &outputVec){

        SpherePoint outputPoint(0, 0);
        _gothroughList(outputPoint);

        outputVec[0] = outputPoint.theta * RESOLUTION;
        outputVec[1] = outputPoint.phi * RESOLUTION;
    }

    void Orient::_resetList(const SpherePoint &point)
    {
        _max->vote = vote;
        _estimationList.reset(new VoteList);
        _estimationList->point = point;
        _estimationList->next = NULL;
        _max->list = _estimationList;
        _max->next = NULL;
    }

    void Orient::_insertPoint(const SpherePoint &point)
    {
        VoteList *ptr = new VoteList;
        ptr->point = point;
        ptr->next = _estimationList->next;
        _estimationList->next = ptr;
    }

    void Orient::_gothroughList(SpherePoint &outputPoint)
    {
        VoteListPtr ptr(_estimationList);

        uint16_t count = 0;

        while (ptr != NULL){
            outputPoint += ptr->point;
            ptr = ptr->next;
            count += 1;
        }
        outputPoint /= count;
    }
}