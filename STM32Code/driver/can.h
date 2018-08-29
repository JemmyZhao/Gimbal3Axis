/*
 * File      : can.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author            Notes
 * 2015-05-14     aubrcool@qq.com   first version
 * 2015-07-06     Bernard           remove RT_CAN_USING_LED.
 */

#ifndef __CAN_H_
#define __CAN_H_

#include <rtthread.h>

#define RT_CAN_USING_HDR

#ifndef RT_CANMSG_BOX_SZ
#define RT_CANMSG_BOX_SZ    16
#endif
#ifndef RT_CANSND_BOX_NUM
#define RT_CANSND_BOX_NUM   1
#endif

#define RT_CAN_STD          0
#define RT_CAN_EXT          1

#define RT_CAN_DATA         0          
#define RT_CAN_RTR          1

#define RT_CAN_MASK         0
#define RT_CAN_LIST         1

#define RT_CAN_FIFO0        0
#define RT_CAN_FIFO1        1

enum CANBAUD
{
    CAN1MBaud   = 1000UL * 1000,/* 1 MBit/sec   */
    CAN800kBaud = 1000UL * 800, /* 800 kBit/sec */
    CAN500kBaud = 1000UL * 500, /* 500 kBit/sec */
    CAN250kBaud = 1000UL * 250, /* 250 kBit/sec */
    CAN125kBaud = 1000UL * 125, /* 125 kBit/sec */
    CAN100kBaud = 1000UL * 100, /* 100 kBit/sec */
    CAN50kBaud  = 1000UL * 50,  /* 50 kBit/sec  */
    CAN20kBaud  = 1000UL * 20,  /* 20 kBit/sec  */
    CAN10kBaud  = 1000UL * 10   /* 10 kBit/sec  */
};

#define RT_CAN_MODE_NORMAL              0
#define RT_CAN_MODE_LISEN               1
#define RT_CAN_MODE_LOOPBACK            2
#define RT_CAN_MODE_LOOPBACKANLISEN     3

#define RT_CAN_MODE_PRIV                0x01
#define RT_CAN_MODE_NOPRIV              0x00

struct rt_can_filter_item
{
    rt_uint32_t id  : 29;   // ��ʶ��
    rt_uint32_t ide : 1;    // STD & EXT           0-STD  1-EXT
    rt_uint32_t rtr : 1;    // Զ��                0-DATA 1-ROMAT
    rt_uint32_t mode : 1;   // IDmask & IDlist     0-MASK 1-LIST
    rt_uint32_t fifo : 1;   // ��FIFO
    rt_uint32_t fno;
    rt_uint32_t foff;       // ��ǰ��������FR1&FR2�еĵ�ַƫ��(��������ID32MASK Filter)
    rt_uint32_t mask;       // �����������λ
    
    rt_int32_t hdr;         // ������������
    // �ص�����
    rt_err_t (*ind)(rt_device_t dev, void *args , rt_int32_t hdr, rt_size_t size);
    // �ص����������¼�
    void *args;
};

// ��������ʼ��
#define RT_CAN_FILTER_ITEM_INIT(id,ide,rtr,mode,fifo,fno,foff,mask,hdr,ind,args) \
     {(id), (ide), (rtr), (mode), (fifo), (fno), (foff), (mask), (hdr), (ind), (args)}
// ��׼ID������
#define RT_CAN_FILTER_STD_INIT(id,mode,fifo,fno,foff,hdr,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,mode,fifo,fno,foff,0xFFFFFFFF,hdr,ind,args)
// ��չID������
#define RT_CAN_FILTER_EXT_INIT(id,mode,fifo,fno,foff,hdr,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,mode,fifo,fno,foff,0xFFFFFFFF,hdr,ind,args)


//// ��׼IDԶ��֡
//#define RT_CAN_STD_RMT_FILTER_INIT(id,mode,fnum,fifo,hdr,ind,args) \
//     RT_CAN_FILTER_ITEM_INIT(id,0,1,mode,fnum,fifo,0xFFFFFFFF,hdr,ind,args)
//// ��չIDԶ��֡
//#define RT_CAN_EXT_RMT_FILTER_INIT(id,mode,fnum,fifo,hdr,ind,args) \
//     RT_CAN_FILTER_ITEM_INIT(id,1,1,mode,fnum,fifo,0xFFFFFFFF,hdr,ind,args)

// ��׼ID16Mask
#define RT_CAN_FILTER_STD_MASK(id,fifo,fno,foff,hdr,ind,args) \
     RT_CAN_FILTER_STD_INIT(id,0,fifo,fno,foff,hdr,ind,args)
// ��׼ID16LIST
#define RT_CAN_FILTER_STD_LIST(id,fifo,fno,foff,hdr,ind,args) \
     RT_CAN_FILTER_STD_INIT(id,1,fifo,fno,foff,hdr,ind,args)

// ��չID32MASK
#define RT_CAN_FILTER_EXT_MASK(id,fifo,fno,hdr,ind,args) \
     RT_CAN_FILTER_EXT_INIT(id,0,fifo,fno,0,hdr,ind,args)
// ��չID32LIST
#define RT_CAN_FILTER_EXT_LIST(id,fifo,fno,foff,hdr,ind,args) \
     RT_CAN_FILTER_EXT_INIT(id,1,fifo,fno,foff,hdr,ind,args)

struct rt_can_filter_config
{
    rt_uint32_t count;
    rt_uint32_t actived;
    rt_uint32_t fifobaseoff;
    struct rt_can_filter_item *items;
};

struct can_configure
{
    rt_uint32_t baud_rate;
    rt_uint32_t msgboxsz;
    rt_uint32_t sndboxnumber;
    rt_uint32_t mode      : 8;
    rt_uint32_t privmode  : 8;
    rt_uint32_t reserved  : 16;
    rt_uint32_t ticks;

    rt_uint32_t maxhdr;
};

#define CANDEFAULTCONFIG \
{\
        CAN1MBaud,\
        RT_CANMSG_BOX_SZ,\
        RT_CANSND_BOX_NUM,\
        RT_CAN_MODE_NORMAL,\
};

struct rt_can_ops;
#define RT_CAN_CMD_SET_FILTER       0x13
#define RT_CAN_CMD_SET_BAUD         0x14
#define RT_CAN_CMD_SET_MODE         0x15
#define RT_CAN_CMD_SET_PRIV         0x16
#define RT_CAN_CMD_GET_STATUS       0x17
#define RT_CAN_CMD_SET_STATUS_IND   0x18
#define RT_CAN_CMD_SET_BUS_HOOK     0x19

#define RT_DEVICE_CAN_INT_ERR       0x1000

enum RT_CAN_STATUS_MODE
{
    NORMAL = 0,
    ERRWARNING = 1,
    ERRPASSIVE = 2,
    BUSOFF = 4,
};
enum RT_CAN_BUS_ERR
{
    RT_CAN_BUS_NO_ERR = 0,
    RT_CAN_BUS_BIT_PAD_ERR = 1,
    RT_CAN_BUS_FORMAT_ERR = 2,
    RT_CAN_BUS_ACK_ERR = 3,
    RT_CAN_BUS_IMPLICIT_BIT_ERR = 4,
    RT_CAN_BUS_EXPLICIT_BIT_ERR = 5,
    RT_CAN_BUS_CRC_ERR = 6,
};

struct rt_can_status
{
    rt_uint32_t rcverrcnt;
    rt_uint32_t snderrcnt;
    rt_uint32_t errcode;
    rt_uint32_t rcvpkg;
    rt_uint32_t dropedrcvpkg;
    rt_uint32_t sndpkg;
    rt_uint32_t dropedsndpkg;
    rt_uint32_t bitpaderrcnt;
    rt_uint32_t formaterrcnt;
    rt_uint32_t ackerrcnt;
    rt_uint32_t biterrcnt;
    rt_uint32_t crcerrcnt;
    rt_uint32_t rcvchange;
    rt_uint32_t sndchange;
    rt_uint32_t lasterrtype;
};

#ifdef RT_CAN_USING_HDR
struct rt_can_hdr
{
    rt_uint32_t connected;            // �ýṹ���Ƿ���������Ӧ�Ĺ�����
    rt_uint32_t msgs;                 // �����еĽڵ���
    struct rt_can_filter_item filter; // ����������
    struct rt_list_node list;         // rt_can_msg_list �� hdrlist��ͷ�ڵ㣬ָ��rt_can_msg_list
};
#endif
struct rt_can_device;
typedef rt_err_t (*rt_canstatus_ind)(struct rt_can_device *, void *);
typedef struct rt_can_status_ind_type
{
    rt_canstatus_ind ind;
    void *args;
} *rt_can_status_ind_type_t;
typedef void (*rt_can_bus_hook)(struct rt_can_device *);

struct rt_can_device
{
    struct rt_device parent;

    const struct rt_can_ops *ops;
    struct can_configure config;
    struct rt_can_status status;

    rt_uint32_t timerinitflag;
    struct rt_timer timer;

    struct rt_can_status_ind_type status_indicate;
#ifdef RT_CAN_USING_HDR
    struct rt_can_hdr *hdr; 
#endif
#ifdef RT_CAN_USING_BUS_HOOK
    rt_can_bus_hook bus_hook;
#endif /*RT_CAN_USING_BUS_HOOK*/
    struct rt_mutex lock;
    void *can_rx;      // can���ջ�����
    void *can_tx;      // can���ͻ�����
};
typedef struct rt_can_device *rt_can_t;

#define RT_CAN_STDID 0
#define RT_CAN_EXTID 1
#define RT_CAN_DTR   0
#define RT_CAN_RTR   1

typedef struct rt_can_status *rt_can_status_t;
struct rt_can_msg
{
    rt_uint32_t id  : 29;      // ������
    rt_uint32_t ide : 1;       // ��ʶ������
    rt_uint32_t rtr : 1;       // Զ�̷�������
    rt_uint32_t rsv : 1;       // (N/C)
    rt_uint32_t len : 8;       // ���ݳ���
    rt_uint32_t priv : 8;      // ���ȼ�  ���������
    rt_uint32_t hdr : 8;       // ������ƥ������
    rt_uint32_t reserved : 8;  // (N/C)
    rt_uint8_t data[8];        // ����
};
typedef struct rt_can_msg *rt_can_msg_t;

struct rt_can_msg_list
{
    struct rt_list_node list;
#ifdef RT_CAN_USING_HDR
    struct rt_list_node hdrlist;
    struct rt_can_hdr *owner;
#endif
    struct rt_can_msg data;
};

struct rt_can_rx_fifo
{
    /* software fifo */
    struct rt_can_msg_list *buffer;
    rt_uint32_t freenumbers;
    struct rt_list_node freelist;
    struct rt_list_node uselist;
};

#define RT_CAN_SND_RESULT_OK        0
#define RT_CAN_SND_RESULT_ERR       1
#define RT_CAN_SND_RESULT_WAIT      2

#define RT_CAN_EVENT_RX_IND         0x01    /* Rx indication */
#define RT_CAN_EVENT_TX_DONE        0x02    /* Tx complete   */
#define RT_CAN_EVENT_TX_FAIL        0x03    /* Tx complete   */
#define RT_CAN_EVENT_RX_TIMEOUT     0x05    /* Rx timeout    */
#define RT_CAN_EVENT_RXOF_IND       0x06    /* Rx overflow */

struct rt_can_sndbxinx_list
{
    struct rt_list_node list;
    struct rt_completion completion;
    rt_uint32_t result;
};

struct rt_can_tx_fifo
{
    struct rt_can_sndbxinx_list *buffer;
    struct rt_completion completion;
    struct rt_list_node freelist;
};

struct rt_can_ops
{
    rt_err_t (*configure)(struct rt_can_device *can, struct can_configure *cfg);
    rt_err_t (*control)(struct rt_can_device *can, int cmd, void *arg);
    int (*sendmsg)(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);
    int (*recvmsg)(struct rt_can_device *can, void *buf, rt_uint32_t boxno);
};

rt_err_t rt_hw_can_register(struct rt_can_device *can,
                            const char              *name,
                            const struct rt_can_ops *ops,
                            void                    *data);
void rt_hw_can_isr(struct rt_can_device *can, int event);
#endif /*_CAN_H*/

