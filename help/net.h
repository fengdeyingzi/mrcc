/*
HTTP�����ļ�����
��ʼ������ initnetwork
��ȡ����IP gethostbyname
�������� socket
�������� connect
�������� send
�������� recev
�رշ��� closesocket
�ر����� closenetwork
*/

//ע�⣡�лص��ĺ���ֻ���ڻص�������ִ�к��ٴε��ã�
//���֮ǰ�Ļص�������û�б�ִ�У���ʱ����ٴε��ý������𲻿�Ԥ�ϵĽ��

/*
�����ʼ���ص�����(ֻ��һ����ʽ���ڱ�ϵͳ��Ч,�붨ʱ���ص�ԭ������)
����:
result:
MR_SUCCESS ��ʼ���ɹ�
MR_FAILED ��ʼ��ʧ��
����ֵ:
MR_SUCCESS �����ɹ�
MR_FAILED ����ʧ��
�����ķ���ֵ����Ϊ���������汾������Ŀǰmythroad
�����ĺ����ķ���ֵ��
*/
typedef int (*MR_INIT_NETWORK_CB)(int32 result);

/*
�����ʼ�������û�в��ţ����в��Ų�����
������Ҫע����ǣ����ĵ���������������ӿں�
����ʵ��ʱ�������ȿ��ǲ��÷�������ʽ��
�������ʼ��ʹ���첽ģʽ��ʹ�ûص�����֪ͨ��
���ʼ�������

����:
cb �������ʼ��ʹ���첽ģʽʱ��ʹ�øûص�����
֪ͨӦ�ó�ʼ�����
mode ���ŷ�ʽ��"CMNET"��" CMWAP"�Ĳ��ŷ�ʽ��

����:
MR_SUCCESS ͬ��ģʽ����ʼ���ɹ������ٵ���cb
MR_FAILED ��������֪�ģ�ʧ�ܣ����ٵ���cb
MR_WAITING ʹ�ûص�����֪ͨ�����ʼ�����
*/
int32 initnetwork(char* cb, const char *mode);




/*
��ȡ����IP�ص�����(ֻ��һ����ʽ���ڱ�ϵͳ��Ч)
����:
ip:
MR_FAILED ��ȡIPʧ��
����ֵ IP��ַ
����ֵ:
MR_SUCCESS �����ɹ�
MR_FAILED ����ʧ��
�����ķ���ֵ����Ϊ���������汾������Ŀǰmythroad
�����ĺ����ķ���ֵ��
*/
typedef int (*MR_GET_HOST_CB)(int32 ip);

/*
ͨ����������ø�������IP��ֵַ�����һ������
��IP��ַΪ218.18.95.203����ֵΪ218<<24 + 18<<16 + 95<<8 + 203
= 0xda125fcb��
����ȡ����IPʹ���첽ģʽ��ʹ�ûص�����֪ͨ��
���ȡIP�Ľ����

����:
name ������
cb �ص�����


����:
MR_FAILED ��������֪�ģ�ʧ�ܣ����ٵ���cb
MR_WAITING ʹ�ûص�����֪ͨ�����ȡIP�Ľ��
����ֵ ͬ��ģʽ���������ص�IP��ַ�����ٵ���cb
*/
int32 gethostbyname(const char *name, char* cb);





/*
ȡ������ID��

����:
0 �ƶ�GSM
1 ��ͨGSM
2 ��ͨCDMA
3 δ�忨���������
*/
int32 getnetworkid(void);


/*
�Ͽ��������ӡ�

����:

����:
MR_SUCCESS �ɹ�
MR_FAILED ʧ��
*/
int32 closenetwork(void);


/*
����һ��socket��

����:
type Socket���ͣ�
MR_SOCK_STREAM 0 ������
MR_SOCK_DGRAM 1 ���ݰ�
protocol ����Э������:
MR_IPPROTO_TCP��0 TCP
MR_IPPROTO_UDP 1 UDP

����:
>=0 ���ص�Socket���
MR_FAILED ʧ��
*/
int32 socket(int32 type, int32 protocol);

/*
����TCP���ӡ�

����:
s �򿪵�socket�����
ip IP��ַ
port �˿ں�
type:
MR_SOCKET_BLOCK 0 //������ʽ��ͬ����ʽ��
MR_SOCKET_NONBLOCK 1 //��������ʽ���첽��ʽ��

����:
MR_SUCCESS �ɹ�
MR_FAILED ʧ��
MR_WAITING ʹ���첽��ʽ�������ӣ�Ӧ����Ҫ��ѯ
��socket��״̬�Ի�֪����״��
*/
int32 connect(int32 s, int32 ip, uint16 port, int32 type);


/*
��ȡsocket connect ״̬����Ҫ����TCP���첽���ӣ�
���أ�

����:
Socket���

����:
MR_SUCCESS �� ���ӳɹ�
MR_FAILED ������ʧ��
MR_WAITING ��������
MR_IGNORE ����֧�ָù���
*/
int32 getsocketstate(int32 s);

/*
�ر�һ��socket���ӡ�

����:
s �򿪵�socket���

����:
MR_SUCCESS �ɹ�
MR_FAILED ʧ��
*/
int32 closesocket(int32 s);

/*
������������ݡ�

����:
s �򿪵�socket�����
len ��������С��

���:
buf ����������Ž��յ������ݡ�

����:
>=0������ ʵ�ʽ��յ������ֽڸ���
MR_FAILED Socket�Ѿ����رջ��������޷��޸��Ĵ���
*/
int32 recv(int32 s, char *buf, int len);

/*
��ָ����ַ�������ݡ�

����:
s �򿪵�socket�����
len ��������С��
ip �Զ�IP��ַ
port �Զ˶˿ں�

���:
buf ����������Ž��յ������ݡ�


����:
>=0������ ʵ�ʽ��յ������ֽڸ���
MR_FAILED Socket�Ѿ����رջ��������޷��޸��Ĵ���
*/
int32 recvfrom(int32 s, char *buf, int len, int32 *ip, uint16 *port);

/*
�������ݡ�

����:
s �򿪵�socket���
len ��������С

���:
buf Ҫ�������ݵĻ�����

����:
>=0 ʵ�ʷ��͵������ֽڸ���
MR_FAILED Socket�Ѿ����رջ��������޷��޸��Ĵ���
*/
int32 send(int32 s, const char *buf, int len);

/*
��ָ����ַ�������ݡ�

����:
s �򿪵�socket���
len ��������С
ip �Զ�IP��ַ
port �Զ˶˿ں�

���:
buf Ҫ�������ݵĻ�����

����:
>=0 ʵ�ʷ��͵������ֽڸ���
MR_FAILED Socket�Ѿ����رջ��������޷��޸��Ĵ���
*/
int32 sendto(int32 s, const char *buf, int len, int32 ip, uint16 port);
