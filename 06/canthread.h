#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QThread>
#include <QTime>
#include "ControlCAN.h"
#include "basic_circular.h"
#include <QDebug>
#include <QMessageBox>

class CANThread: public QThread
{
    Q_OBJECT
public:
    CANThread();

    // bool stopped;
    // bool playBack_stopped;
    void run();

    bool collect_sign = 0;    //采集标志
    int nDeviceType = 4; /* USBCAN-2A或USBCAN-2C或CANalyst-II */
    int nDeviceInd = 0; /* 第1个设备 */
    int nCANInd = 0; /* 第1个通道 */
    //通用参数
    UINT currentID;     //当前ID
    float range;
    float angle;
    float angle_e;
    float velocity;
    float SNR;
    UINT track_level;   //跟踪等级?
    // UINT ALERT_SIG_L;   //报警等级
    // UINT ALERT_SIG_R;
    bool f_h_sign_l;   //帧开始标志
    bool f_h_sign_r;   //帧开始标志

    // UINT bk_cnt;    //bk目标数
    // UINT ak_cnt;    //ak目标数

    UINT bk_index_l;    //左bk目标编号
    UINT ak_index_l;    //左ak目标编号
    UINT bk_index_r;    //右bk目标编号
    UINT ak_index_r;    //右ak目标编号

    //雷达参数
    UINT frame_number;  //帧编号，对应frame_id
    UINT target_num;

    frame_complete fl;
    frame_complete fr;

    VCI_INIT_CONFIG vic;    //canbus参数
    VCI_CAN_OBJ vco[2000];  //can数据

    UINT classifyID(VCI_CAN_OBJ vco[], UINT index);
    bool clicked_start();

signals:
    void getCompleteFrame(frame_complete fl, frame_complete fr);
    void saveSignal(frame_complete fc, bool position);
    void sleep_50();

};

#endif // CANTHREAD_H
