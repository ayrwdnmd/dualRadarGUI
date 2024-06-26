#include "canthread.h"

CANThread::CANThread()
{
    // stopped = 1;
    // playBack_stopped = 1;
}

void CANThread::run()
{
    DWORD rel;
    while(!Basic_Circular::getStopped())
    {
        rel = VCI_GetReceiveNum (nDeviceType, nDeviceInd, nCANInd);
        if(rel > 0)
        {
            rel = VCI_Receive(nDeviceType, nDeviceInd, nCANInd, vco,2000,0);
        }
        for(UINT i = 0; i < rel; i++)
        {
            classifyID(vco,i);
        }
    }
    // float time = Basic_Circular::getFrameLength();
    // qDebug() << time;
    while(!Basic_Circular::getPlayBack_stopped())
    {
        emit sleep_50();
        msleep(50);
    }
}


UINT CANThread::classifyID(VCI_CAN_OBJ vco[], UINT index)
{
    UINT currentID = vco[index].ID;
    switch(currentID)
    {
    case 0x300:
    {
        f_h_sign_l = 1;
        fl.bk_cnt = vco[index].Data[6]
                    + (vco[index].Data[7] << 8);
        bk_index_l = 0;
        fl.frame_number = vco[index].Data[2]
                          + (vco[index].Data[3] << 8)
                          + (vco[index].Data[4] << 16)
                          + (vco[index].Data[5] << 24);
        // qDebug() << " ID:" << 300
        //          << " fl.bk_cnt:" << fl.bk_cnt
        //          << " fl.frame_number" << fl.frame_number;
        break;
    }
    case 0x301:
    {
        if (f_h_sign_l == 0)
            break;
        fl.ak_cnt = vco[index].Data[0]
                    + (vco[index].Data[1] << 8);
        ak_index_l = 0;
        // qDebug() << " ID:" << 301
        //          << " fl.ak_cnt:" << fl.ak_cnt;
        break;
    }
    case 0x310:
    {
        f_h_sign_r = 1;
        fr.bk_cnt = vco[index].Data[6]
                    + (vco[index].Data[7] << 8);
        bk_index_r = 0;
        fr.frame_number = vco[index].Data[2]
                          + (vco[index].Data[3] << 8)
                          + (vco[index].Data[4] << 16)
                          + (vco[index].Data[5] << 24);
        // qDebug() << " ID:" << 310
        //          << " fr.bk_cnt:" << fr.bk_cnt
        //          << " fr.frame_number" << fr.frame_number;
        break;
    }
    case 0x311:
    {
        if(f_h_sign_r == 0)
            break;
        fr.ak_cnt = vco[index].Data[0]
                    + (vco[index].Data[1] << 8);
        ak_index_r = 0;
        // qDebug() << " ID:" << 311
        //          << " ak_cnt_right:" << fr.ak_cnt;
        break;
    }
    case 0x400:
    {
        if (f_h_sign_l == 0)
            break;
        target_num = vco[index].Data[0];
        range = vco[index].Data[2]
                + (vco[index].Data[3] << 8)
                + (vco[index].Data[4] << 16)
                + (vco[index].Data[5] << 24);
        range /= 100;
        velocity = vco[index].Data[6]
                   + (vco[index].Data[7] << 8)
                   - 16384;
        velocity /= 100;
        fl.bk[bk_index_l].target_number = target_num;
        fl.bk[bk_index_l].range = range;
        fl.bk[bk_index_l].velocity = velocity;
        // qDebug() << " ID:" << 400
        //          << " fl target_number:" << fl.bk[bk_index_l].target_number
        //          << " fl range" << fl.bk[bk_index_l].range
        //          << " fl velocity:" << fl.bk[bk_index_l].velocity;
        break;
    }
    case 0x401:
    {
        if (f_h_sign_l == 0)
            break;
        SNR = vco[index].Data[0]
              + (vco[index].Data[1] << 8)
              -16384;
        SNR /= 100;
        angle = vco[index].Data[2]
                + (vco[index].Data[3] << 8)
                - 16384;
        angle /= 100;
        angle_e = vco[index].Data[4]
                  + (vco[index].Data[5] << 8)
                  - 16384;
        angle_e /= 100;
        fl.bk[bk_index_l].SNR = SNR;
        fl.bk[bk_index_l].angle = angle;
        fl.bk[bk_index_l].angle_e = angle_e;
        // qDebug() << " ID:" << 401
        //          << " fl SNR:" << fl.bk[bk_index_l].SNR
        //          << " fl angle" << fl.bk[bk_index_l].angle;
        // qDebug()<<angle_e;
        // qDebug()<<fl.bk[bk_index_l].angle_e;
        bk_index_l++;
        break;
    }
    case 0x410:
    {
        if(f_h_sign_r == 0)
            break;
        target_num = vco[index].Data[0]
                     + (vco[index].Data[1] << 8);
        range = vco[index].Data[2]
                + (vco[index].Data[3] << 8)
                + (vco[index].Data[4] << 16)
                + (vco[index].Data[5] << 24);
        range /= 100;
        velocity = vco[index].Data[6]
                   + (vco[index].Data[7] << 8)
                   - 16384;
        velocity /= 100;
        fr.bk[bk_index_r].target_number = target_num;
        fr.bk[bk_index_r].range = range;
        fr.bk[bk_index_r].velocity = velocity;
        // qDebug() << " ID:" << 410
        //          << " fr target_number:" << fr.bk[bk_index_r].target_number
        //          << " fr range" << fr.bk[bk_index_r].range
        //          << " fr velocity:" << fr.bk[bk_index_r].velocity;
        break;
    }
    case 0x411:
    {
        if(f_h_sign_r == 0)
            break;
        SNR = vco[index].Data[0]
              + (vco[index].Data[1] << 8)
              -16384;
        SNR /= 100;
        angle = vco[index].Data[2]
                + (vco[index].Data[3] << 8)
                - 16384;
        angle /= 100;
        angle_e = vco[index].Data[4]
                  + (vco[index].Data[5] << 8)
                  - 16384;
        angle_e /= 100;
        fr.bk[bk_index_r].SNR = SNR;
        fr.bk[bk_index_r].angle = angle;
        fr.bk[bk_index_r].angle_e = angle_e;
        // qDebug() << " ID:" << 401
        //          << " fr SNR:" << fr.bk[bk_index_r].SNR
        //          << " fr angle" << fr.bk[bk_index_r].angle;
        bk_index_r++;
        break;
    }
    case 0x500:
    {
        if (f_h_sign_l == 0)
            break;
        target_num = vco[index].Data[0];
        track_level = vco[index].Data[1] >> 2;
        range = vco[index].Data[2]
                + (vco[index].Data[3] << 8)
                + (vco[index].Data[4] << 16)
                + (vco[index].Data[5] << 24);
        range /= 100;
        velocity = vco[index].Data[6]
                   + (vco[index].Data[7] << 8)
                   - 16384;
        velocity /= 100;
        fl.ak[ak_index_l].target_number = target_num;
        // fl.ak[ak_index_l].track_level = track_level;
        fl.ak[ak_index_l].range = range;
        fl.ak[ak_index_l].velocity = velocity;
        // qDebug() << " ID:" << 500
        //          << " fl target_number:" << fl.ak[ak_index_l].target_number
        //          << " fl track_level:" << fl.ak[ak_index_l].track_level
        //          << " fl range" << fl.ak[ak_index_l].range
        //          << " fl velocity:" << fl.ak[ak_index_l].velocity;
        break;
    }
    case 0x501:
    {
        if (f_h_sign_l == 0)
            break;
        SNR = vco[index].Data[0]
              + (vco[index].Data[1] << 8)
              -16384;
        SNR /= 100;
        angle = vco[index].Data[2]
                + (vco[index].Data[3] << 8)
                - 16384;
        angle /= 100;
        angle_e = vco[index].Data[4]
                  + (vco[index].Data[5] << 8)
                  - 16384;
        angle_e /= 100;
        fl.ak[ak_index_l].SNR = SNR;
        fl.ak[ak_index_l].angle = angle;
        fl.ak[ak_index_l].angle_e = angle_e;
        // qDebug() << " ID:" << 501
        //          << " fl SNR:" << fl.ak[ak_index_l].SNR
        //          << " fl angle" << fl.ak[ak_index_l].angle;
        ak_index_l++;
        break;
    }
    case 0x510:
    {
        if(f_h_sign_r == 0)
            break;
        target_num = vco[index].Data[0];
        track_level = vco[index].Data[1] >> 2;
        range = vco[index].Data[2]
                + (vco[index].Data[3] << 8)
                + (vco[index].Data[4] << 16)
                + (vco[index].Data[5] << 24);
        range /= 100;
        velocity = vco[index].Data[6]
                   + (vco[index].Data[7] << 8)
                   - 16384;
        velocity /= 100;
        fr.ak[ak_index_r].target_number = target_num;
        // fr.ak[ak_index_r].track_level = track_level;
        fr.ak[ak_index_r].range = range;
        fr.ak[ak_index_r].velocity = velocity;
        // qDebug() << " ID:" << 510
        //          << " fr target_number:" << fr.ak[ak_index_r].target_number
        //          << " fr track_level:" << fr.ak[ak_index_r].track_level
        //          << " fr range" << fr.ak[ak_index_r].range
        //          << " fr velocity:" << fr.ak[ak_index_r].velocity;
        break;
    }
    case 0x511:
    {
        if(f_h_sign_r == 0)
            break;
        SNR = vco[index].Data[0]
              + (vco[index].Data[1] << 8)
              -16384;
        SNR /= 100;
        angle = vco[index].Data[2]
                + (vco[index].Data[3] << 8)
                - 16384;
        angle /= 100;
        angle_e = vco[index].Data[4]
                  + (vco[index].Data[5] << 8)
                  - 16384;
        angle_e /= 100;
        fr.ak[ak_index_r].SNR = SNR;
        fr.ak[ak_index_r].angle = angle;
        fr.ak[ak_index_r].angle_e = angle_e;
        // qDebug() << " ID:" << 511
        //          << " fr SNR:" << fr.ak[ak_index_r].SNR
        //          << " fr angle" << fr.ak[ak_index_r].angle;
        ak_index_r++;
        break;
    }
    case 0x750:
    {
        if (f_h_sign_l == 0)
            break;
        fl.ALERT_SIG = vco[index].Data[0];
        fl.VS.Speed = vco[index].Data[1] * 3.6;
        fl.VS.doorStatusLeft = vco[index].Data[2];
        fl.VS.doorStatusRight = vco[index].Data[3];
        fl.VS.Gear = vco[index].Data[4];
        fl.VS.ExtrLtgStsTurnIndrLe = vco[index].Data[5];
        fl.VS.ExtrLtgStsTurnIndrRi = vco[index].Data[6];
        fl.VS.sysfuncmode = vco[index].Data[7];
        // qDebug() << " ID:" << 750
        //          << " fl.ALERT_SIG_L:" << fl.ALERT_SIG_L;
        emit getCompleteFrame(fl, fr);
        emit saveSignal(fl, 0);
        break;
    }
    case 0x760:
    {
        if(f_h_sign_r == 0)
            break;
        fr.ALERT_SIG = vco[index].Data[0];
        fr.VS.Speed = vco[index].Data[1] * 3.6;
        fr.VS.doorStatusLeft = vco[index].Data[2];
        fr.VS.doorStatusRight = vco[index].Data[3];
        fr.VS.Gear = vco[index].Data[4];
        fr.VS.ExtrLtgStsTurnIndrLe = vco[index].Data[5];
        fr.VS.ExtrLtgStsTurnIndrRi = vco[index].Data[6];
        fr.VS.sysfuncmode = vco[index].Data[7];
        // qDebug() << " ID:" << 760
        //          <<" fr.ALERT_SIG_R:" << fr.ALERT_SIG_R;
        emit getCompleteFrame(fl, fr);
        emit saveSignal(fr,1);
        break;
    }
    }
    return 0;
}

bool CANThread::clicked_start()
{
    DWORD dwRel;

    dwRel = VCI_OpenDevice(nDeviceType, nDeviceInd, 0);
    // qDebug()<<"打开设备"<<dwRel;

    vic.AccCode=0x80000008;
    vic.AccMask=0xFFFFFFFF;
    vic.Filter=1;
    vic.Timing0=0x00;
    vic.Timing1=0x1C;
    vic.Mode=0;
    dwRel = VCI_InitCAN(nDeviceType, nDeviceInd, nCANInd, &vic);
    qDebug()<<"设备初始化"<<dwRel;

    // dwRel = VCI_ResetCAN(nDeviceType, nDeviceInd, nCANInd);
    // qDebug()<<"复位"<<dwRel;

    dwRel = VCI_StartCAN(nDeviceType, nDeviceInd, nCANInd);
    qDebug()<<"启动设备"<<dwRel;

    if(dwRel == 0)
    {
        // Basic_Circular::setStopped(1);
        QMessageBox msgBox;
        msgBox.setText("启动设备失败");
        msgBox.exec();
        return false;
    }

    f_h_sign_l = 0;
    f_h_sign_r = 0;
    fl.bk_cnt = 0;
    fl.ak_cnt = 0;
    collect_sign = 0;

    memset(fl.bk,0,sizeof(track_measu_t)*64);
    memset(fr.bk,0,sizeof(track_measu_t)*64);
    memset(fl.ak,0,sizeof(track_measu_t)*64);
    memset(fr.ak,0,sizeof(track_measu_t)*64);
    return true;
}
