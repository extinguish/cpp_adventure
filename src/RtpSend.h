//
// Created by guoshichao on 2020/10/23.
//

#ifndef CPPADVENTURE_RTPSEND_H
#define CPPADVENTURE_RTPSEND_H

#include <stdint.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define bits_write(buffer, count, bits)\
{\
    bits_buffer_s *p_buffer = (buffer);\
    int i_count = (count);\
    uint64_t i_bits = (bits);\
    while( i_count > 0 )\
{\
    i_count--;\
    if( ( i_bits >> i_count )&0x01 )\
{\
    p_buffer->p_data[p_buffer->i_data] |= p_buffer->i_mask;\
}\
        else\
{\
    p_buffer->p_data[p_buffer->i_data] &= ~p_buffer->i_mask;\
}\
    p_buffer->i_mask >>= 1;         /*操作完一个字节第一位后，操作第二位*/\
    if( p_buffer->i_mask == 0 )     /*循环完一个字节的8位后，重新开始下一位*/\
{\
    p_buffer->i_data++;\
    p_buffer->i_mask = 0x80;\
}\
}\
}


#define PS_HDR_LEN  14
#define SYS_HDR_LEN 18
#define PSM_HDR_LEN 24
#define PES_HDR_LEN 19
#define  PS_SYS_MAP_SIZE 30
#define PS_PES_PAYLOAD_SIZE (65535 - PES_HDR_LEN)

#define RTP_HDR_LEN 12
#define  RTP_HDR_SIZE 12 // ?
#define RTP_MAX_PACKET_BUFF 1300
#define  RTP_VERSION 2//?

struct bits_buffer_s {
    int i_size;
    int i_data;
    int i_mask;
    unsigned char *p_data;
};

struct Data_Info_s {
    char dstIP[32];
    int nPort;
    uint32_t sCurPts;
    int IFrame;
    unsigned short u16CSeq;
    unsigned int u32Ssrc;
    char szBuff[RTP_MAX_PACKET_BUFF];
};

#define MAX_RES_BUF 512000 //512*1024
#define MAX_RTP_CHANNEL 8

class RtpSend {
protected:
    int makePsHeader(char *pData, uint64_t s64Scr);

    int makeSysHeader(char *pData);

    int makePsmHeader(char *pData);

    int makePesHeader(char *pData, int stream_id, int payload_len, unsigned long long pts, unsigned long long dts);

    int sendDataByUDP(int nChn, char *databuff, int nLen);

    int makeRtpHeader(char *pData, int marker_flag, unsigned short cseq, long long curpts, unsigned int ssrc);

    int sendRtpPacket(int nChn, char *databuff, int nDataLen, int mark_flag, Data_Info_s *pPacker);

    void SaveSpsPps(int nChn, char *pBuf, int nLen, int type);

public:
    RtpSend();

    ~RtpSend();

    void SetSSRC(int nChn, int nSsc);

    void SetRemoteAddr(int nChn, char *ip, int nPort); //设置目标发送地址

    int GetOneIdleChan(); //获得一个空闲的通道

    int SendH264Stream(int nChn, char *pData, int nFrameLen, uint32_t curPts, int frameType);

    int SendPSStream(int nChn, char *pData, int nFrameLen, uint32_t sCurPts, int mark_flag);

    int rtpSendPort(int nChn) { return m_rtpSendPort[nChn]; }

    int OpenStream(int nChn);

    void CloseStream(int nChn);

    bool IsStreamOpen(int nChn);

    void SetWritable(int nChn, bool bWrite);

    bool IsWritable(int nChn);

private:
    int m_sock[MAX_RTP_CHANNEL];
    int m_rtpSendPort[MAX_RTP_CHANNEL];
    Data_Info_s m_DataInfo[MAX_RTP_CHANNEL];
    char *m_pResBuf[MAX_RTP_CHANNEL];
    char *m_pPps[MAX_RTP_CHANNEL];
    char *m_pSps[MAX_RTP_CHANNEL];
    int m_nSps[MAX_RTP_CHANNEL];
    int m_nPps[MAX_RTP_CHANNEL];
    bool m_bOpenStream[MAX_RTP_CHANNEL];
    bool m_bWaitIFrame[MAX_RTP_CHANNEL];
    bool m_bCanWrite[MAX_RTP_CHANNEL];
};


#endif //CPPADVENTURE_RTPSEND_H
