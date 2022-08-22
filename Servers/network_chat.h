#ifndef __NETWORK_CHAT_H__
#define __NETWORK_CHAT_H__

//聊天室中能注册登陆的最大人员数量
#define  PEOPLE_NUM_MAX   10
//聊天信息（发送结构体）长度
#define  CHAT_STRUCT_SIZE (POSITION_CONTENT+128)
//客户端最大连接数量
#define  CLIENT_MAX       3

#define  POSITION_SELFID  0
#define  POSITION_NAME    (4+POSITION_SELFID)
#define  POSITION_DESTID  (4+POSITION_NAME)
#define  POSITION_TIME    (4+POSITION_DESTID)
#define  POSITION_CONTENT (26+POSITION_TIME)

//用户信息
typedef struct 
{
  char id[4];	 //系统生成用户id
  char name[4];	 //用户自定义昵称
  char passwd[8];//密码
}client_info; 

//信息发送结构体
typedef struct
{
  char self_id[4];	//发信人id
  char name[4];		//发信人昵称
  char dest_id[4];	//收信人id
  char time[26];	//发送系统时间
  char content[128];	//信息内容?
}send_msg;

//信息接收结构体
typedef struct
{
  char writer[4];		//发送者
  char time[26];	//发送时间
  char content[128];	//发送内容
}recv_msg;




#endif

