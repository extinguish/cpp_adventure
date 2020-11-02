//
// Created by guoshichao on 2020/10/23.
//

#include "RtpSend.h"

int RtpSend::makePsHeader(char *pData, uint64_t currPts) {
    unsigned long long lScrExt = (currPts) % 100;
    unsigned long long s64Scr = currPts / 100;
    // 这里除以100是由于sdp协议返回的video的频率是90000，帧率是25帧/s，所以每次递增的量是3600,
    // 所以实际你应该根据你自己编码里的时间戳来处理以保证时间戳的增量为3600即可，
    //如果这里不对的话，就可能导致卡顿现象了
    bits_buffer_s bitsBuffer;
    bitsBuffer.i_size = PS_HDR_LEN;
    bitsBuffer.i_data = 0;
    bitsBuffer.i_mask = 0x80; // 二进制：10000000 这里是为了后面对一个字节的每一位进行操作，避免大小端夸字节字序错乱
    bitsBuffer.p_data = (unsigned char *) (pData);
    memset(bitsBuffer.p_data, 0, PS_HDR_LEN);
    bits_write(&bitsBuffer, 32, 0x000001BA);                    /*start codes*/
    bits_write(&bitsBuffer, 2, 1);                              /*marker bits '01b'*/
    bits_write(&bitsBuffer, 3, (s64Scr >> 30) & 0x07);          /*System clock [32..30]*/
    bits_write(&bitsBuffer, 1, 1);                              /*marker bit*/
    bits_write(&bitsBuffer, 15, (s64Scr >> 15) & 0x7FFF);       /*System clock [29..15]*/
    bits_write(&bitsBuffer, 1, 1);                              /*marker bit*/
    bits_write(&bitsBuffer, 15, s64Scr & 0x7fff);               /*System clock [29..15]*/
    bits_write(&bitsBuffer, 1, 1);                              /*marker bit*/
    bits_write(&bitsBuffer, 9, lScrExt & 0x01ff);               /*System clock [14..0]*/
    bits_write(&bitsBuffer, 1, 1);                              /*marker bit*/
    bits_write(&bitsBuffer, 22, (255) & 0x3fffff);              /*bit rate(n units of 50 bytes per second.)*/
    bits_write(&bitsBuffer, 2, 3);                              /*marker bits '11'*/
    bits_write(&bitsBuffer, 5, 0x1f);                           /*reserved(reserved for future use)*/
    bits_write(&bitsBuffer, 3, 0);                              /*stuffing length*/

    return 0;
}

int RtpSend::makeSysHeader(char *pData) {
    bits_buffer_s bitsBuffer;
    bitsBuffer.i_size = SYS_HDR_LEN;
    bitsBuffer.i_data = 0;
    bitsBuffer.i_mask = 0x80;
    bitsBuffer.p_data = (unsigned char *) (pData);
    memset(bitsBuffer.p_data, 0, SYS_HDR_LEN);
    /*system header*/
    bits_write(&bitsBuffer, 32, 0x000001BB);    /*start code*/
    bits_write(&bitsBuffer, 16, SYS_HDR_LEN - 6);/*header_length 表示次字节后面的长度，后面的相关头也是次意思*/
    bits_write(&bitsBuffer, 1, 1);            /*marker_bit*/
    bits_write(&bitsBuffer, 22, 50000);        /*rate_bound*/
    bits_write(&bitsBuffer, 1, 1);            /*marker_bit*/
    bits_write(&bitsBuffer, 6, 1);            /*audio_bound*/
    bits_write(&bitsBuffer, 1, 0);            /*fixed_flag */
    bits_write(&bitsBuffer, 1, 1);            /*CSPS_flag */
    bits_write(&bitsBuffer, 1, 1);            /*system_audio_lock_flag*/
    bits_write(&bitsBuffer, 1, 1);            /*system_video_lock_flag*/
    bits_write(&bitsBuffer, 1, 1);            /*marker_bit*/
    bits_write(&bitsBuffer, 5, 1);            /*video_bound*/
    bits_write(&bitsBuffer, 1, 0);            /*dif from mpeg1*/
    bits_write(&bitsBuffer, 7, 0x7F);        /*reserver*/
    /*audio stream bound*/
    bits_write(&bitsBuffer, 8, 0xC0);         /*stream_id*/
    bits_write(&bitsBuffer, 2, 3);            /*marker_bit */
    bits_write(&bitsBuffer, 1, 0);            /*PSTD_buffer_bound_scale*/
    bits_write(&bitsBuffer, 13, 512);          /*PSTD_buffer_size_bound*/
    /*video stream bound*/
    bits_write(&bitsBuffer, 8, 0xE0);         /*stream_id*/
    bits_write(&bitsBuffer, 2, 3);            /*marker_bit */
    bits_write(&bitsBuffer, 1, 1);            /*PSTD_buffer_bound_scale*/
    bits_write(&bitsBuffer, 13, 2048);        /*PSTD_buffer_size_bound*/
    return 0;

}

int RtpSend::makePsmHeader(char *pData) {
    bits_buffer_s bitsBuffer;
    bitsBuffer.i_size = PSM_HDR_LEN;
    bitsBuffer.i_data = 0;
    bitsBuffer.i_mask = 0x80;
    bitsBuffer.p_data = (unsigned char *) (pData);
    memset(bitsBuffer.p_data, 0, PS_SYS_MAP_SIZE);
    bits_write(&bitsBuffer, 24, 0x000001);    /*start code*/
    bits_write(&bitsBuffer, 8, 0xBC);        /*map stream id*/
    bits_write(&bitsBuffer, 16, 18);            /*program stream map length*/
    bits_write(&bitsBuffer, 1, 1);            /*current next indicator */
    bits_write(&bitsBuffer, 2, 3);            /*reserved*/
    bits_write(&bitsBuffer, 5, 0);            /*program stream map version*/
    bits_write(&bitsBuffer, 7, 0x7F);        /*reserved */
    bits_write(&bitsBuffer, 1, 1);            /*marker bit */
    bits_write(&bitsBuffer, 16, 0);            /*programe stream info length*/
    bits_write(&bitsBuffer, 16, 8);        /*elementary stream map length	is*/
    /*audio*/
    bits_write(&bitsBuffer, 8, 0x90);       /*stream_type*/
    bits_write(&bitsBuffer, 8, 0xC0);        /*elementary_stream_id*/
    bits_write(&bitsBuffer, 16, 0);        /*elementary_stream_info_length is*/
    /*video*/
    bits_write(&bitsBuffer, 8, 0x1B);       /*stream_type*/
    bits_write(&bitsBuffer, 8, 0xE0);        /*elementary_stream_id*/
    bits_write(&bitsBuffer, 16, 0);        /*elementary_stream_info_length */
    /*crc (2e b9 0f 3d)*/
    bits_write(&bitsBuffer, 8, 0x45);        /*crc (24~31) bits*/
    bits_write(&bitsBuffer, 8, 0xBD);        /*crc (16~23) bits*/
    bits_write(&bitsBuffer, 8, 0xDC);        /*crc (8~15) bits*/
    bits_write(&bitsBuffer, 8, 0xF4);        /*crc (0~7) bits*/
    return 0;
}

int
RtpSend::makePesHeader(char *pData, int stream_id, int payload_len, unsigned long long pts, unsigned long long dts) {
    bits_buffer_s bitsBuffer;
    bitsBuffer.i_size = PES_HDR_LEN;
    bitsBuffer.i_data = 0;
    bitsBuffer.i_mask = 0x80;
    bitsBuffer.p_data = (unsigned char *) (pData);
    memset(bitsBuffer.p_data, 0, PES_HDR_LEN);
    /*system header*/
    bits_write(&bitsBuffer, 24, 0x000001);    /*start code*/
    bits_write(&bitsBuffer, 8, (stream_id));    /*streamID*/
    bits_write(&bitsBuffer, 16, (payload_len) + 13);    /*packet_len*/ //指出pes分组中数据长度和该字节后的长度和
    bits_write(&bitsBuffer, 2, 2);        /*'10'*/
    bits_write(&bitsBuffer, 2, 0);        /*scrambling_control*/
    bits_write(&bitsBuffer, 1, 0);        /*priority*/
    bits_write(&bitsBuffer, 1, 0);        /*data_alignment_indicator*/
    bits_write(&bitsBuffer, 1, 0);        /*copyright*/
    bits_write(&bitsBuffer, 1, 0);        /*original_or_copy*/
    bits_write(&bitsBuffer, 1, 1);        /*PTS_flag*/
    bits_write(&bitsBuffer, 1, 1);        /*DTS_flag*/
    bits_write(&bitsBuffer, 1, 0);        /*ESCR_flag*/
    bits_write(&bitsBuffer, 1, 0);        /*ES_rate_flag*/
    bits_write(&bitsBuffer, 1, 0);        /*DSM_trick_mode_flag*/
    bits_write(&bitsBuffer, 1, 0);        /*additional_copy_info_flag*/
    bits_write(&bitsBuffer, 1, 0);        /*PES_CRC_flag*/
    bits_write(&bitsBuffer, 1, 0);        /*PES_extension_flag*/
    bits_write(&bitsBuffer, 8, 10);        /*header_data_length*/
    // 指出包含在 PES 分组标题中的可选字段和任何填充字节所占用的总字节数。该字段之前
    //的字节指出了有无可选字段。

    /*PTS,DTS*/
    bits_write(&bitsBuffer, 4, 3);                    /*'0011'*/
    bits_write(&bitsBuffer, 3, ((pts) >> 30) & 0x07);     /*PTS[32..30]*/
    bits_write(&bitsBuffer, 1, 1);
    bits_write(&bitsBuffer, 15, ((pts) >> 15) & 0x7FFF);    /*PTS[29..15]*/
    bits_write(&bitsBuffer, 1, 1);
    bits_write(&bitsBuffer, 15, (pts) & 0x7FFF);          /*PTS[14..0]*/
    bits_write(&bitsBuffer, 1, 1);
    bits_write(&bitsBuffer, 4, 1);                    /*'0001'*/
    bits_write(&bitsBuffer, 3, ((dts) >> 30) & 0x07);     /*DTS[32..30]*/
    bits_write(&bitsBuffer, 1, 1);
    bits_write(&bitsBuffer, 15, ((dts) >> 15) & 0x7FFF);    /*DTS[29..15]*/
    bits_write(&bitsBuffer, 1, 1);
    bits_write(&bitsBuffer, 15, (dts) & 0x7FFF);          /*DTS[14..0]*/
    bits_write(&bitsBuffer, 1, 1);

    return 0;
}

int RtpSend::sendDataByUDP(int nChn, char *databuff, int nLen) {
    printf("sendDataByUDP %s:%d\n", m_DataInfo[nChn].dstIP, m_DataInfo[nChn].nPort);
    struct sockaddr_in addrSrv;
    addrSrv.sin_addr.s_addr = inet_addr(m_DataInfo[nChn].dstIP);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(m_DataInfo[nChn].nPort);

    int sendRet = sendto(m_sock[nChn], databuff, nLen, 0,
                         (struct sockaddr *) &addrSrv, sizeof(sockaddr));
    return sendRet;
}

int RtpSend::makeRtpHeader(char *pData, int marker_flag, unsigned short cseq, long long curpts, unsigned int ssrc) {
    bits_buffer_s bitsBuffer;
    if (pData == NULL)
        return -1;
    bitsBuffer.i_size = RTP_HDR_LEN;
    bitsBuffer.i_data = 0;
    bitsBuffer.i_mask = 0x80;
    bitsBuffer.p_data = (unsigned char *) (pData);
    memset(bitsBuffer.p_data, 0, RTP_HDR_SIZE);
    bits_write(&bitsBuffer, 2, RTP_VERSION);    /* rtp version 	*/
    bits_write(&bitsBuffer, 1, 0);                /* rtp padding 	*/
    bits_write(&bitsBuffer, 1, 0);                /* rtp extension 	*/
    bits_write(&bitsBuffer, 4, 0);                /* rtp CSRC count */
    bits_write(&bitsBuffer, 1, (marker_flag));            /* rtp marker  	*/
    bits_write(&bitsBuffer, 7, 96);            /* rtp payload type*/
    bits_write(&bitsBuffer, 16, (cseq));            /* rtp sequence 	 */
    bits_write(&bitsBuffer, 32, (curpts));        /* rtp timestamp 	 */
    bits_write(&bitsBuffer, 32, (ssrc));        /* rtp SSRC	 	 */
    return 0;
}

int RtpSend::sendRtpPacket(int nChn, char *databuff, int nDataLen, int mark_flag, Data_Info_s *pPacker) {
    printf("sendRtpPacket %d\n", pPacker->u32Ssrc);
    int nRet = 0;
    int nPlayLoadLen = 0;
    int nSendSize = 0;
    char szRtpHdr[RTP_HDR_LEN];
    memset(szRtpHdr, 0, RTP_HDR_LEN);

    if (nDataLen + RTP_HDR_LEN <= RTP_MAX_PACKET_BUFF) {
        // 一帧数据发送完后，给mark标志位置1
//        makeRtpHeader(szRtpHdr, ((mark_flag == 1) ? 1 : 0), ++pPacker->u16CSeq, (pPacker->sCurPts / 300), pPacker->u32Ssrc);
        makeRtpHeader(szRtpHdr, ((mark_flag == 1) ? 1 : 0), ++pPacker->u16CSeq, (pPacker->sCurPts), pPacker->u32Ssrc);

        memcpy(pPacker->szBuff, szRtpHdr, RTP_HDR_LEN);

        memcpy(pPacker->szBuff + RTP_HDR_LEN, databuff, nDataLen);

        nRet = sendDataByUDP(nChn, pPacker->szBuff, RTP_HDR_LEN + nDataLen);

        if (nRet != (RTP_HDR_LEN + nDataLen)) {
            printf(" udp send error !\n");
            return -1;
        }

    } else {
        nPlayLoadLen = RTP_MAX_PACKET_BUFF - RTP_HDR_LEN; // 每次只能发送的数据长度 除去rtp头
//        makeRtpHeader(pPacker->szBuff, 0, ++pPacker->u16CSeq, (pPacker->sCurPts / 100), pPacker->u32Ssrc);
        makeRtpHeader(pPacker->szBuff, 0, ++pPacker->u16CSeq, (pPacker->sCurPts), pPacker->u32Ssrc);
        memcpy(pPacker->szBuff + RTP_HDR_LEN, databuff, nPlayLoadLen);
        nRet = sendDataByUDP(nChn, pPacker->szBuff, RTP_HDR_LEN + nPlayLoadLen);
        if (nRet != (RTP_HDR_LEN + nPlayLoadLen)) {
            printf("udp send error !\n");
            return -1;
        }

        nDataLen -= nPlayLoadLen;
        // databuff += (nPlayLoadLen - RTP_HDR_LEN);
        databuff += nPlayLoadLen; // 表明前面到数据已经发送出去
        databuff -= RTP_HDR_LEN; // 用来存放rtp头
        while (nDataLen > 0) {
            if (nDataLen <= nPlayLoadLen) {
                //一帧数据发送完，置mark标志位
//                makeRtpHeader(databuff, mark_flag, ++pPacker->u16CSeq, (pPacker->sCurPts / 100), pPacker->u32Ssrc);
                makeRtpHeader(databuff, mark_flag, ++pPacker->u16CSeq, (pPacker->sCurPts), pPacker->u32Ssrc);
                nSendSize = nDataLen;
            } else {
//                makeRtpHeader(databuff, 0, ++pPacker->u16CSeq, (pPacker->sCurPts / 100), pPacker->u32Ssrc);
                makeRtpHeader(databuff, 0, ++pPacker->u16CSeq, (pPacker->sCurPts), pPacker->u32Ssrc);
                nSendSize = nPlayLoadLen;
            }

            nRet = sendDataByUDP(nChn, databuff, RTP_HDR_LEN + nSendSize);
            if (nRet != (RTP_HDR_LEN + nSendSize)) {
                printf(" udp send error !\n");
                return -1;
            }

            nDataLen -= nSendSize;
            databuff += nSendSize;
        }

    }
    return 0;
}

void RtpSend::SaveSpsPps(int nChn, char *pBuf, int nLen, int type) {
    if (nLen < 1024) {
        if (type == 7) {
            memcpy(m_pSps[nChn], pBuf, nLen);
            m_nSps[nChn] = nLen;
        } else if (type == 8) {
            memcpy(m_pPps[nChn], pBuf, nLen);
            m_nPps[nChn] = nLen;
        }
    }
}

RtpSend::RtpSend() {
    for (int i = 0; i < MAX_RTP_CHANNEL; i++) {
        int on = 1;
        m_sock[i] = socket(AF_INET, SOCK_DGRAM, 0);
        setsockopt(m_sock[i], SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));

        m_rtpSendPort[i] = 6666 + i;
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_port = htons(m_rtpSendPort[i]);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(m_sock[i], (struct sockaddr *) &addr, sizeof(addr))) {
            printf("bind error\n");
        }

        m_pResBuf[i] = new char[MAX_RES_BUF];
        m_pPps[i] = new char[1024];
        m_pSps[i] = new char[1024];
        m_nSps[i] = 0;
        m_nPps[i] = 0;
        m_DataInfo[i].sCurPts = 0;
        m_bOpenStream[i] = false;
        m_bCanWrite[i] = false;
    }
}

RtpSend::~RtpSend() {
    for (int i = 0; i < MAX_RTP_CHANNEL; i++) {
        delete[] m_pResBuf[i];
        delete[] m_pPps[i];
        delete[] m_pSps[i];
        close(m_sock[i]);
    }
}

void RtpSend::SetSSRC(int nChn, int nSsc) {
    m_DataInfo[nChn].u32Ssrc = nSsc;
}

void RtpSend::SetRemoteAddr(int nChn, char *ip, int nPort) {
    strcpy(m_DataInfo[nChn].dstIP, ip);
    m_DataInfo[nChn].nPort = nPort;
}

int RtpSend::GetOneIdleChan() {
    for (int i = 0; i < MAX_RTP_CHANNEL; i++) {
        if (!m_bOpenStream[i])
            return i;
    }
    return -1;
}

// SPS(frameType=7),PPS(frameType=8)和I帧(frameType=5)合在一个帧发
int RtpSend::SendH264Stream(int nChn, char *pData, int nFrameLen, uint32_t sCurPts, int frameType) {
    char szPsHead[256];
    int nSizePos = 0;
    int nSize = 0;

    if (frameType == 7 || frameType == 5) //SPS或I帧
    {
        m_bWaitIFrame[nChn] = false;
    }

    if (!m_bOpenStream[nChn] || !m_bCanWrite[nChn]) {
        return -2;
    }

    if (m_bWaitIFrame[nChn]) {
        return -3;
    }

    memset(szPsHead, 0, 256);

    //m_DataInfo[nChn].sCurPts += 3600;
    m_DataInfo[nChn].sCurPts = sCurPts;

    makePsHeader(szPsHead + nSizePos, m_DataInfo[nChn].sCurPts);

    nSizePos += PS_HDR_LEN;

    char *pPayload = m_pResBuf[nChn] + 4096;

    m_DataInfo[nChn].IFrame = 0;

    memcpy(pPayload, pData, nFrameLen);

    if (frameType == 7 || frameType == 5) {
        makeSysHeader(szPsHead + nSizePos);
        nSizePos += SYS_HDR_LEN;

        makePsmHeader(szPsHead + nSizePos);
        nSizePos += PSM_HDR_LEN;

        m_DataInfo[nChn].IFrame = 1;
    }

    // 加上rtp发送出去，这样的话，后面的数据就只要分片分包就只有加上pes头和rtp头了
    if (sendRtpPacket(nChn, szPsHead, nSizePos, 0, &m_DataInfo[nChn]) != 0) {
        return -1;
    }

    char *pTmp = pPayload - PES_HDR_LEN;

    while (nFrameLen > 0) {
        //每次帧的长度不要超过short类型，过了就得分片进循环行发送
        nSize = (nFrameLen > PS_PES_PAYLOAD_SIZE) ? PS_PES_PAYLOAD_SIZE : nFrameLen;

        // 添加pes头
        makePesHeader(pTmp, 0xE0, nSize, (m_DataInfo[nChn].sCurPts / 100), (m_DataInfo[nChn].sCurPts / 300));

        // 最后在添加rtp头并发送数据
        if (sendRtpPacket(nChn, pTmp, nSize + PES_HDR_LEN, ((nSize == nFrameLen) ? 1 : 0), &m_DataInfo[nChn]) != 0) {
            printf("sendRtpPacket failed!\n");
            return -1;
        }

        nFrameLen -= nSize;
        pTmp += nSize;
    }

    return 0;
}

int RtpSend::SendPSStream(int nChn, char *pData, int nFrameLen, uint32_t sCurPts, int mark_flag) {
    if (!m_bOpenStream[nChn] || !m_bCanWrite[nChn]) {
        return -2;
    }
    m_DataInfo[nChn].sCurPts = sCurPts;

    // 最后在添加rtp头并发送数据
    if (sendRtpPacket(nChn, pData, nFrameLen, mark_flag, &m_DataInfo[nChn]) != 0) {
        printf("sendRtpPacket failed!\n");
        return -1;
    }

    return 0;
}

int RtpSend::OpenStream(int nChn) {
    printf("open stream %d\n", nChn);

    m_bOpenStream[nChn] = true;
    m_bWaitIFrame[nChn] = true;

    m_DataInfo[nChn].sCurPts = 0;
    m_DataInfo[nChn].u16CSeq = 0;

    return true;
}

void RtpSend::CloseStream(int nChn) {
    printf("close stream %d\n", nChn);
    m_bOpenStream[nChn] = false;
    m_bCanWrite[nChn] = false;
}

bool RtpSend::IsStreamOpen(int nChn) {
    return m_bOpenStream[nChn];
}

void RtpSend::SetWritable(int nChn, bool bWrite) {
    m_bCanWrite[nChn] = bWrite;
}

bool RtpSend::IsWritable(int nChn) {
    return m_bCanWrite[nChn];
}
