#ifndef INCLUDED_FINSLIB_FINS_H
#define INCLUDED_FINSLIB_FINS_H

#if defined(_WIN32)
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#include <stdint.h>
#include <time.h>

#if defined(_WIN32)
#define inet_pton				InetPton
#else
#define INVALID_SOCKET				(-1)
typedef int					SOCKET;
#define closesocket				close
#endif

/********************************************************/
/*							*/
#define FINS_ICF				0			/* Information Control Field				*/
#define FINS_RSV				1			/* Reserved						*/
#define FINS_GCT				2			/* Gateway Counter. Init op 0x07 naar CPU v2.0 of 0x02	*/
#define FINS_DNA				3			/* Destination Network Address (0..127) 0 = lokaal	*/
#define FINS_DA1				4			/* Destination Node Address (0..254) 0 = lokaal		*/
#define FINS_DA2				5			/* Destination Unit Address (0..31) 0 = CPU unit	*/
#define FINS_SNA				6			/* Source Network Address (0..127) 0 = lokaal		*/
#define FINS_SA1				7			/* Source Node Address (0..254) 0 = intern in PLC	*/
#define FINS_SA2				8			/* Source Unit Address (0..31) 0 = CPU unit		*/
#define FINS_SID				9			/* Service ID, uniek nummer 0..FF per commando		*/
#define FINS_MRC				10			/* Main Request Code					*/
#define FINS_SRC				11			/* Sub Request Code					*/
/*							*/
/********************************************************/
#define FINS_MRES				0
#define FINS_SRES				1
/********************************************************/
/*							*/
#define FINS_HEADER_LEN				12			/* Length of a FINS header				*/
#define FINS_BODY_LEN				2000			/* Maximum length of a FINS body			*/
#define FINS_MAX_TCP_HEADER			32			/* Maximum length of a FINS/TCP header			*/
/*							*/
/********************************************************/

#define FINS_PORT_MIN				0
#define FINS_PORT_RESERVED			1024
#define FINS_PORT_MAX				65535

#define FINS_TIMEOUT				60

#define FINS_DEFAULT_PORT			9600			/* Default port for FINS TCP and UDP communications	*/

/********************************************************/
/*							*/
#define FINS_MODE_UNKNOWN			0			/* PLC communication mode unknown			*/
#define FINS_MODE_CV				1			/* PLC communicates like a CV PLC			*/
#define FINS_MODE_CS				2			/* PLC communicates like a CS/CJ/CP PLC		*/		
/*							*/
/********************************************************/

#define FI_RD					0x01
#define FI_WR					0x02
#define FI_FILL					0x04
#define FI_MRD					0x08
#define FI_TRS					0x10
#define FI_TRD					0x20
#define FI_FRC					0x40

#define FINS_MAX_READ_WORDS_SYSWAY		269
#define FINS_MAX_READ_WORDS_ETHERNET		999
#define FINS_MAX_READ_WORDS_CLINK		999
#define FINS_MAX_READ_WORDS_SYSMAC_LINK		269
#define FINS_MAX_READ_WORDS_DEVICENET		269

#define FINS_MAX_WRITE_WORDS_SYSWAY		267
#define FINS_MAX_WRITE_WORDS_ETHERNET		996
#define FINS_MAX_WRITE_WORDS_CLINK		996
#define FINS_MAX_WRITE_WORDS_SYSMAC_LINK	267
#define FINS_MAX_WRITE_WORDS_DEVICENET		267

/********************************************************/
/*							*/
#define FINS_COMM_TYPE_UNKNOWN		0x00			/* No communication protocol has been selected		*/
#define FINS_COMM_TYPE_TCP			0x01			/* The communication protocol is FINS/TCP		*/
#define FINS_COMM_TYPE_UDP			0x02			/* The communication protocol is FINS/UDP		*/
/*							*/
/********************************************************/

/********************************************************/
/*							*/
#define FINS_RETVAL_ERRNO_BASE			0xC000			/* All higher error numbers are errno.h values		*/
/*							*/
#define FINS_RETVAL_SUCCESS			0x0000			/* Execution was successful				*/
#define FINS_RETVAL_NOT_INITIALIZED		0x8001			/* The connection with the PLC was not initialized	*/
#define FINS_RETVAL_NOT_CONNECTED		0x8002			/* There is no connection with the remote PLC		*/
#define FINS_RETVAL_OUT_OF_MEMORY		0x8003			/* There was not enough free memory for the action	*/
#define FINS_RETVAL_SUCCESS_LAST_DATA		0x8004			/* Execution successful and last data delivered		*/
#define FINS_RETVAL_INVALID_IP_ADDRESS		0x8005			/* The IP address passed to inet_pton is invalid	*/
#define FINS_RETVAL_MAX_ERROR_COUNT		0x8006			/* The connection was closed after reaching max errors	*/
#define FINS_RETVAL_SYNC_ERROR			0x8007			/* Synchronization error. Some packets probably lost	*/
/*							*/
#define FINS_RETVAL_NO_READ_ADDRESS		0x8101			/* No read address in the remote PLC was specified	*/
#define FINS_RETVAL_NO_WRITE_ADDRESS		0x8102			/* No write address in the remote PLC was specified	*/
#define FINS_RETVAL_NO_DATA_BLOCK		0x8103			/* No local data memory block was provided		*/
/*							*/
#define FINS_RETVAL_INVALID_READ_ADDRESS	0x8201			/* An invalid read address string was specified		*/
#define FINS_RETVAL_INVALID_WRITE_ADDRESS	0x8202			/* An invalid write address string was specified	*/
/*							*/
#define FINS_RETVAL_INVALID_READ_AREA		0x8301			/* No read area associated with the address		*/
#define FINS_RETVAL_INVALID_WRITE_AREA		0x8302			/* No write area associated with the address		*/
#define FINS_RETVAL_INVALID_FILL_AREA		0x8303			/* No fill area associated with the address		*/
/*							*/
#define FINS_RETVAL_INVALID_PARAMETER_AREA	0x8401			/* The parameter area is invalid			*/
/*							*/
#define FINS_RETVAL_INVALID_DATE		0x8501			/* The provided date is not valid			*/
/*							*/
#define FINS_RETVAL_INVALID_DISK		0x8601			/* An invalid disk was specified			*/
#define FINS_RETVAL_INVALID_PATH		0x8602			/* An invalid path on a disk was specified		*/
#define FINS_RETVAL_INVALID_FILENAME		0x8603			/* An invalid filename was specified			*/
/*							*/
#define FINS_RETVAL_NO_COMMAND			0x8701			/* No command specified when executing a function	*/
#define FINS_RETVAL_NO_COMMAND_LENGTH           0x8702			/* No command length specified when executing a function*/
#define FINS_RETVAL_BODY_TOO_SHORT		0x8703			/* Command body length too short			*/
#define FINS_RETVAL_BODY_TOO_LONG		0x8704			/* The FINS body is longer than allowed			*/
#define FINS_RETVAL_HEADER_SEND_ERROR		0x8705			/* Error sending complete header			*/
#define FINS_RETVAL_COMMAND_SEND_ERROR		0x8706			/* Error sending complete command			*/
#define FINS_RETVAL_RESPONSE_INCOMPLETE		0x8707			/* Response frame is shorter than expected		*/
#define FINS_RETVAL_ILLEGAL_FINS_COMMAND	0x870B			/* Illegal FINS command					*/
#define FINS_RETVAL_RESPONSE_HEADER_INCOMPLETE	0x870C			/* The received response header is incomplete		*/
#define FINS_RETVAL_INVALID_FORCE_COMMAND	0x870D			/* An invalid FORCE mode was specified			*/
/*							*/
#define FINS_RETVAL_TRY_LATER			0x8801			/* Please try again later				*/
/*							*/
#define FINS_RETVAL_CLOSED_BY_REMOTE		0x8900			/* TCP connection closed by remote node without error	*/
#define FINS_RETVAL_NO_FINS_HEADER		0x8901			/* First 4 characters of TCP header are not "FINS"	*/
#define FINS_RETVAL_DATA_LENGTH_TOO_LONG	0x8902			/* TCP connection data length too long			*/
#define FINS_RETVAL_COMMAND_NOT_SUPPORTED	0x8903			/* TCP connection command not supported			*/
#define FINS_RETVAL_ALL_CONNECTIONS_IN_USE	0x8904			/* All TCP connections are in use			*/
#define FINS_RETVAL_NODE_ALREADY_CONNECTED	0x8905			/* Node is already connected				*/
#define FINS_RETVAL_NODE_IP_PROTECTED		0x8906			/* IP address of client not in allowed IP adres list	*/
#define FINS_RETVAL_CLIENT_NODE_OUT_OF_RANGE	0x8907			/* TCP the client node address is out of range		*/
#define FINS_RETVAL_SAME_NODE_ADDRESS		0x8908			/* TCP client and server have the same node address	*/
#define FINS_RETVAL_NO_NODE_ADDRESS_AVAILABLE	0x8909			/* TCP connection no node address available		*/
/*							*/
#define FINS_RETVAL_WSA_UNRECOGNIZED_ERROR	0x8A00			/* Windows WSA returned an unrecognized error code	*/
#define FINS_RETVAL_WSA_NOT_INITIALIZED		0x8A01			/* Windows WSA was not properly initialized		*/
#define FINS_RETVAL_WSA_E_NET_DOWN		0x8A02			/* Windows WSA the network subsystem or provided failed	*/
#define FINS_RETVAL_WSA_E_AF_NO_SUPPORT		0x8A03			/* Windows WSA the address familiy is not supported	*/
#define FINS_RETVAL_WSA_E_IN_PROGRESS		0x8A04			/* Windows WSA a blocking socket 1.1 call is in progres	*/
#define FINS_RETVAL_WSA_E_MFILE			0x8A05			/* Windows WSA no more socket descriptors available	*/
#define FINS_RETVAL_WSA_E_INVAL			0x8A06			/* Windows WSA Invalid argument supplied		*/
#define FINS_RETVAL_WSA_E_INVALID_PROVIDER	0x8A07			/* Windows WSA Server provider function invalid		*/
#define FINS_RETVAL_WSA_E_INVALID_PROCTABLE	0x8A08			/* Windows WSA Invalid procedure table			*/
#define FINS_RETVAL_WSA_E_NOBUFS		0x8A09			/* Windows WSA No buffer space available		*/
#define FINS_RETVAL_WSA_E_PROTO_NO_SUPPORT	0x8A0A			/* Windows WSA the protocol is not supported		*/
#define FINS_RETVAL_WSA_E_PROTO_TYPE		0x8A0B			/* Windows WSA Wrong protocol type for this socket	*/
#define FINS_RETVAL_WSA_E_PROVIDER_FAILED_INIT	0x8A0C			/* Windows WSA Provider failed initialization		*/
#define FINS_RETVAL_WSA_E_SOCKT_NO_SUPPORT	0x8A0D			/* Windows WSA The specified socket type not supported	*/
#define FINS_RETVAL_WSA_SYS_NOT_READY		0x8A0E			/* Windows WSA The network subsystem is not ready	*/
#define FINS_RETVAL_WSA_VER_NOT_SUPPORTED	0x8A0F			/* Windows WSA The socket version is not supported	*/
#define FINS_RETVAL_WSA_E_PROC_LIM		0x8A10			/* Windows WSA Process number limit reached		*/
#define FINS_RETVAL_WSA_E_FAULT			0x8A11			/* Windows WSA The parameter is not valid		*/
#define FINS_RETVAL_WSA_E_NET_RESET		0x8A12			/* Windows WSA Connection timeout during Keep Alive	*/
#define FINS_RETVAL_WSA_E_NO_PROTO_OPT		0x8A13			/* Windows WSA Unsupported option for socket		*/
#define FINS_RETVAL_WSA_E_NOT_CONN		0x8A14			/* Windows WSA Connection reset during Keep Alive	*/
#define FINS_RETVAL_WSA_E_NOT_SOCK		0x8A15			/* Windows WSA The descriptor is not a socket		*/
#define FINS_RETVAL_WSA_E_ACCES			0x8A16			/* Windows WSA Socket access violation			*/
#define FINS_RETVAL_WSA_E_ADDR_IN_USE		0x8A17			/* Windows WSA The address is already in use		*/
#define FINS_RETVAL_WSA_E_ADDR_NOT_AVAIL	0x8A18			/* Windows WSA The address is not available		*/
#define FINS_RETVAL_WSA_E_INTR			0x8A19			/* Windows WSA The blocking 1.1 call was cancelled	*/
#define FINS_RETVAL_WSA_E_ALREADY		0x8A1A			/* Windows WSA Non blocking call already in progress	*/
#define FINS_RETVAL_WSA_E_CONN_REFUSED		0x8A1B			/* Windows WSA The connection was refused		*/
#define FINS_RETVAL_WSA_E_IS_CONN		0x8A1C			/* Windows WSA Socket is already connected		*/
#define FINS_RETVAL_WSA_E_NET_UNREACH		0x8A1D			/* Windows WSA Network is unreacheable			*/
#define FINS_RETVAL_WSA_E_HOST_UNREACH		0x8A1E			/* Windows WSA Host is unreacheable			*/
#define FINS_RETVAL_WSA_E_TIMED_OUT		0x8A1F			/* Windows WSA The connection timed out			*/
#define FINS_RETVAL_WSA_E_WOULD_BLOCK		0x8A20			/* Windows WSA Non-blocking connection would block	*/
/*							*/
#define FINS_RETVAL_CANCELED			0x0001			/* End code 0x0001 The service was canceled		*/
/*							*/
#define FINS_RETVAL_LOCAL_NODE_NOT_IN_NETWORK	0x0101			/* End code 0x0101 Local node is not in network		*/
#define FINS_RETVAL_LOCAL_TOKEN_TIMEOUT		0x0102			/* End code 0x0102 Local node token timeout		*/
#define FINS_RETVAL_LOCAL_RETRIES_FAILED	0x0103			/* End code 0x0103 Local node retries failed		*/
#define FINS_RETVAL_LOCAL_TOO_MANY_SEND_FRAMES	0x0104			/* End code 0x0104 Local node too many send frames	*/
#define FINS_RETVAL_LOCAL_ADDRESS_RANGE_ERROR	0x0105			/* End code 0x0105 Local node address range error	*/
#define FINS_RETVAL_LOCAL_ADDRESS_DUPLICATION	0x0106			/* End code 0x0106 Local node address duplication	*/
/*							*/
#define FINS_RETVAL_DEST_NOT_IN_NETWORK		0x0201			/* End code 0x0201 Destination is not in network	*/
#define FINS_RETVAL_DEST_UNIT_MISSING		0x0202			/* End code 0x0202 Destination unit missing		*/
#define FINS_RETVAL_DEST_THIRD_NODE_MISSING	0x0203			/* End code 0x0203 Destination third node missing	*/
#define FINS_RETVAL_DEST_NODE_BUSY		0x0204			/* End code 0x0204 Destination node is busy		*/
#define FINS_RETVAL_DEST_TIMEOUT		0x0205			/* End code 0x0205 Destination response timed out	*/
/*							*/
#define FINS_RETVAL_CONTR_COMM_ERROR		0x0301			/* End code 0x0301 Communications controller error	*/
#define FINS_RETVAL_CONTR_CPU_UNIT_ERROR	0x0302			/* End code 0x0302 CPU Unit error			*/
#define FINS_RETVAL_CONTR_BOARD_ERROR		0x0303			/* End code 0x0303 Controller board error		*/
#define FINS_RETVAL_CONTR_UNIT_NUMBER_ERROR	0x0304			/* End code 0x0304 Unit number error			*/
/*							*/
#define FINS_RETVAL_UNSUPPORTED_COMMAND		0x0401			/* End code 0x0401 Undefined command			*/
#define FINS_RETVAL_UNSUPPORTED_VERSION		0x0402			/* End code 0x0402 Not supported by model/version	*/
/*							*/
#define FINS_RETVAL_ROUTING_ADDRESS_ERROR	0x0501			/* End code 0x0501 Routing destination address error	*/
#define FINS_RETVAL_ROUTING_NO_TABLES		0x0502			/* End code 0x0502 No routing tables available		*/
#define FINS_RETVAL_ROUTING_TABLE_ERROR		0x0503			/* End code 0x0503 Routing table error			*/
#define FINS_RETVAL_ROUTING_TOO_MANY_RELAYS	0x0504			/* End code 0x0504 Too many relays			*/
/*							*/
#define FINS_RETVAL_COMMAND_TOO_LONG		0x1001			/* End code 0x1001 Command too long			*/
#define FINS_RETVAL_COMMAND_TOO_SHORT		0x1002			/* End code 0x1002 Command too short			*/
#define FINS_RETVAL_COMMAND_ELEMENT_MISMATCH	0x1003			/* End code 0x1003 Elements/data don't match		*/
#define FINS_RETVAL_COMMAND_FORMAT_ERROR	0x1004			/* End code 0x1004 Command format error			*/
#define FINS_RETVAL_COMMAND_HEADER_ERROR	0x1005			/* End code 0x1005 Command header error			*/
/*							*/
#define FINS_RETVAL_PARAM_AREA_MISSING		0x1101			/* End code 0x1101 Parameter area classification missing*/
#define FINS_RETVAL_PARAM_ACCESS_SIZE_ERROR	0x1102			/* End code 0x1102 Parameter access size wrong		*/
#define FINS_RETVAL_PARAM_START_ADDRESS_ERROR	0x1103			/* End code 0x1103 Start address out of range		*/
#define FINS_RETVAL_PARAM_END_ADDRESS_ERROR	0x1104			/* End code 0x1104 End address out of range		*/
#define FINS_RETVAL_PARAM_PROGRAM_MISSING	0x1106			/* End code 0x1106 Program number is missing		*/
#define FINS_RETVAL_PARAM_RELATIONAL_ERROR	0x1109			/* End code 0x1109 Parameter relational error		*/
#define FINS_RETVAL_PARAM_DUPLICATE_ACCESS	0x110A			/* End code 0x110A Duplicate data access		*/
#define FINS_RETVAL_PARAM_RESPONSE_TOO_LONG	0x110B			/* End code 0x110B Response too long			*/
#define FINS_RETVAL_PARAM_PARAMETER_ERROR	0x110C			/* End code 0x110C Parameter error			*/
/*							*/
#define FINS_RETVAL_RD_ERR_PROTECTED		0x2002			/* End code 0x2002 The program area is protected	*/
#define FINS_RETVAL_RD_ERR_TABLE_MISSING	0x2003			/* End code 0x2003 The table is not existing		*/
#define FINS_RETVAL_RD_ERR_DATA_MISSING		0x2004			/* End code 0x2004 The search data does not exist	*/
#define FINS_RETVAL_RD_ERR_PROGRAM_MISSING	0x2005			/* End code 0x2005 The program does not exist		*/
#define FINS_RETVAL_RD_ERR_FILE_MISSING		0x2006			/* End code 0x2006 The file does not exist		*/
#define FINS_RETVAL_RD_ERR_DATA_MISMATCH	0x2007			/* End code 0x2007 Data comparison failed		*/
/*							*/
#define FINS_RETVAL_WR_ERR_READ_ONLY		0x2101			/* End code 0x2101 The specified area is read-only	*/
#define FINS_RETVAL_WR_ERR_PROTECTED		0x2102			/* End code 0x2102 The program area is protected	*/
#define FINS_RETVAL_WR_ERR_CANNOT_REGISTER	0x2103			/* End code 0x2103 Cannot register file			*/
#define FINS_RETVAL_WR_ERR_PROGRAM_MISSING	0x2105			/* End code 0x2105 Program number is not valid		*/
#define FINS_RETVAL_WR_ERR_FILE_MISSING		0x2106			/* End code 0x2106 File does not exist			*/
#define FINS_RETVAL_WR_ERR_FILE_EXISTS		0x2107			/* End code 0x2107 The file already exists		*/
#define FINS_RETVAL_WR_ERR_CANNOT_CHANGE	0x2108			/* End code 0x2108 Cannot change the data		*/
/*							*/
#define FINS_RETVAL_MODE_NOT_DURING_EXECUTION	0x2201			/* End code 0x2201 Not possible during execution	*/
#define FINS_RETVAL_MODE_NOT_DURING_RUN		0x2202			/* End code 0x2202 Not possible while running		*/
#define FINS_RETVAL_MODE_IS_PROGRAM		0x2203			/* End code 0x2203 Not possible in program mode		*/
#define FINS_RETVAL_MODE_IS_DEBUG		0x2204			/* End code 0x2204 Not possible in debug mode		*/
#define FINS_RETVAL_MODE_IS_MONITOR		0x2205			/* End code 0x2205 Not possible in monitor mode		*/
#define FINS_RETVAL_MODE_IS_RUN			0x2206			/* End code 0x2206 Not possible in run mode		*/
#define FINS_RETVAL_MODE_NODE_NOT_POLLING	0x2207			/* End code 0x2207 Specified node not in polling mode	*/
#define FINS_RETVAL_MODE_NO_STEP		0x2208			/* End code 0x2208 Step cannot be executed		*/
/*							*/
#define FINS_RETVAL_DEVICE_FILE_MISSING		0x2301			/* End code 0x2301 File device missing			*/
#define FINS_RETVAL_DEVICE_MEMORY_MISSING	0x2302			/* End code 0x2302 There is no file memory		*/
#define FINS_RETVAL_DEVICE_CLOCK_MISSING	0x2303			/* End code 0x2303 There is no clock			*/
/*							*/
#define FINS_RETVAL_DATALINK_TABLE_MISSING	0x2401			/* End code 0x2401 Data link table missing or corrupt	*/
/*							*/
#define FINS_RETVAL_UNIT_MEMORY_CONTENT_ERROR	0x2502			/* End code 0x2502 Memory content error			*/
#define FINS_RETVAL_UNIT_IO_SETTING_ERROR	0x2503			/* End code 0x2503 I/O setting error			*/
#define FINS_RETVAL_UNIT_TOO_MANY_IO_POINTS	0x2504			/* End code 0x2504 Too many I/O points registered	*/
#define FINS_RETVAL_UNIT_CPU_BUS_ERROR		0x2505			/* End code 0x2505 CPU bus line error			*/
#define FINS_RETVAL_UNIT_IO_DUPLICATION		0x2506			/* End code 0x2506 Duplicate I/O address		*/
#define FINS_RETVAL_UNIT_IO_BUS_ERROR		0x2507			/* End code 0x2507 I/O bus error			*/
#define FINS_RETVAL_UNIT_SYSMAC_BUS2_ERROR	0x2509			/* End code 0x2509 Sysmac bus/2 error			*/
#define FINS_RETVAL_UNIT_CPU_BUS_UNIT_ERROR	0x250A			/* End code 0x250A CPU bus unit error			*/
#define FINS_RETVAL_UNIT_SYSMAC_BUS_DUPLICATION	0x250D			/* End code 0x250D Same word is used more than once	*/
#define FINS_RETVAL_UNIT_MEMORY_ERROR		0x250F			/* End code 0x250F Memory error in internal memory	*/
#define FINS_RETVAL_UNIT_SYSMAC_BUS_TERMINATOR	0x2510			/* End code 0x2510 Sysmac bus terminator missing	*/
/*							*/
#define FINS_RETVAL_COMMAND_NO_PROTECTION	0x2601			/* End code 0x2601 The specified area is not protected	*/
#define FINS_RETVAL_COMMAND_WRONG_PASSWORD	0x2602			/* End code 0x2602 Wrong password specified		*/
#define FINS_RETVAL_COMMAND_PROTECTED		0x2604			/* End code 0x2604 The specified area is protected	*/
#define FINS_RETVAL_COMMAND_SERVICE_EXECUTING	0x2605			/* End code 0x2605 Service is already executing		*/
#define FINS_RETVAL_COMMAND_SERVICE_STOPPED	0x2606			/* End code 0x2606 The service is stopped		*/
#define FINS_RETVAL_COMMAND_NO_EXECUTION_RIGHT	0x2607			/* End code 0x2607 No execution right			*/
#define FINS_RETVAL_COMMAND_SETTINGS_INCOMPLETE	0x2608			/* End code 0x2608 The settings are not complete	*/
#define FINS_RETVAL_COMMAND_ITEMS_NOT_SET	0x2609			/* End code 0x2609 Necessary items not set		*/
#define FINS_RETVAL_COMMAND_ALREADY_DEFINED	0x260A			/* End code 0x260A Number already defined		*/
#define FINS_RETVAL_COMMAND_ERROR_WONT_CLEAR	0x260B			/* End code 0x260B Error will not clear			*/
/*							*/
#define FINS_RETVAL_ACCESS_NO_RIGHTS		0x3001			/* End code 0x3001 No access right			*/
/*							*/
#define FINS_RETVAL_ABORTED			0x4001			/* End code 0x3001 Service aborted			*/
/*							*/
/********************************************************/
#pragma pack(push,1)
struct fins_command_tp
{
	unsigned char header[FINS_HEADER_LEN];
	unsigned char body[FINS_BODY_LEN];
};
#pragma pack(pop)
/********************************************************/
struct fins_area_tp
{
	/*							*/
	int plc_mode; /* CS/CJ or CV mode communication			*/
	const char* name; /* Text string with the area short code			*/
	int bits; /* Number of bits in the data				*/
	int length; /* Number of bytes per element				*/
	uint8_t area; /* Area code						*/
	uint32_t low_id; /* Lowest identificator					*/
	uint32_t high_id; /* Highest identificator				*/
	uint32_t low_addr; /* Lowest memory address				*/
	uint32_t high_addr; /* Highest memory address				*/
	int32_t access; /* Read or Read/Write access				*/
	bool force; /* Force status used 					*/
}; /*							*/
/********************************************************/
struct fins_sys_tp
{
	char address[128];
	uint16_t port;
	SOCKET sockfd;
	time_t timeout;
	int error_count;
	int error_max;
	int last_error;
	bool error_changed;
	uint8_t local_net;
	uint8_t local_node;
	uint8_t local_unit;
	uint8_t remote_net;
	uint8_t remote_node;
	uint8_t remote_unit;
	uint8_t sid;
	uint8_t comm_type;
	char model[21];
	char version[21];
	int plc_mode;
};

struct fins_cpudata_tp
{
	char model[21];
	char version[21];
	unsigned char system_block[40];
	int largest_em_bank;
	int program_area_size;
	int iom_size;
	int number_of_dm_words;
	int timer_counter_size;
	int em_non_file_memory_size;
	int memory_card_size;
	int num_sysmac_bus_masters;
	int num_racks;
	uint16_t bus_unit_id[16];
	bool bus_unit_present[16];
	bool dip_switch[8];
	uint8_t memory_card_type;
};

struct fins_address_tp
{
	char name[4];
	uint32_t main_address;
	uint32_t sub_address;
};

int finslib_cpu_unit_data_read(struct fins_sys_tp* sys, struct fins_cpudata_tp* cpudata);

//�Ͽ�����
//�������ΪFINS�豸ָ��
void finslib_disconnect(struct fins_sys_tp* sys);

//��ȡN��bitλ
//�������ΪFINS�豸ָ�룬��ʼ��ַ��charָ�룬��ʽ���ơ�CIO100.1�����洢�����boolֵ����ָ�룬��Ҫ��ȡ��λ��
int finslib_memory_area_read_bit(struct fins_sys_tp* sys, const char* start, bool* data, size_t num_bits);

//��ȡN��int16ֵ
//�������ΪFINS�豸ָ�룬��ʼ��ַ��charָ�룬��ʽ���ơ�CIO100�����洢�����int16_tֵ����ָ�룬��Ҫ��ȡ��int16_t�ĸ���
int finslib_memory_area_read_int16(struct fins_sys_tp* sys, const char* start, int16_t* data, size_t num_int16);

//��ȡN��uint16ֵ
//�������ΪFINS�豸ָ�룬��ʼ��ַ��charָ�룬��ʽ���ơ�CIO100�����洢�����uint16_tֵ����ָ�룬��Ҫ��ȡ��uint16_t�ĸ���
int finslib_memory_area_read_uint16(struct fins_sys_tp* sys, const char* start, uint16_t* data, size_t num_uint16);

//д��N��bitλ
//�������ΪFINS�豸ָ�룬��ʼ��ַ��charָ�룬��ʽ���ơ�CIO100.1����Ҫд����������ڵ��ڴ�ָ�룬��Ҫд���bitֵ����
int finslib_memory_area_write_bit(struct fins_sys_tp* sys, const char* start, const bool* data, size_t num_bit);

//д��N��int16ֵ
//�������ΪFINS�豸ָ�룬��ʼ��ַ��charָ�룬��ʽ���ơ�CIO100����Ҫд����������ڵ��ڴ�ָ�룬��Ҫд���int16_t�ĸ���
int finslib_memory_area_write_int16(struct fins_sys_tp* sys, const char* start, const int16_t* data, size_t num_int16);

//д��N��uint16ֵ
//�������ΪFINS�豸ָ�룬��ʼ��ַ��charָ�룬��ʽ���ơ�CIO100����Ҫд����������ڵ��ڴ�ָ�룬��Ҫд���uint16_t�ĸ���
int finslib_memory_area_write_uint16(struct fins_sys_tp* sys, const char* start, const uint16_t* data,
                                     size_t num_uint16);
void finslib_milli_second_sleep(int msec);
time_t finslib_monotonic_sec_timer(void);

//����PLC����ģʽ
//����FINS�豸ָ�룬Զ���豸IP���˿ںţ�Զ���豸�ڵ�ţ��������ָ�����������������������������ֵ��᷵�شﵽ�������޵Ĵ���
struct fins_sys_tp* finslib_tcp_connect(struct fins_sys_tp* sys, const char* address, uint16_t port, uint8_t remote_node, int* error_val, int error_max);

//����PLC������ģʽ
//����FINS�豸ָ�룬Զ���豸IP���˿ںţ���������ţ����ؽڵ�ţ����ص�Ԫ�ţ�Զ���豸����ţ�Զ���豸�ڵ�ţ�Զ���豸��Ԫ�ţ��������ָ���������������������������ֵ��᷵�شﵽ�������޵Ĵ���
struct fins_sys_tp* finslib_tcp_connect(struct fins_sys_tp* sys, const char* address, uint16_t port, uint8_t local_net,
                                        uint8_t local_node, uint8_t local_unit, uint8_t remote_net, uint8_t remote_node,
                                        uint8_t remote_unit, int* error_val, int error_max);

int XX_finslib_communicate(struct fins_sys_tp* sys, struct fins_command_tp* command, size_t* bodylen);
bool XX_finslib_decode_address(const char* str, struct fins_address_tp* address);
void XX_finslib_init_command(struct fins_sys_tp* sys, struct fins_command_tp* command, uint8_t mrc, uint8_t src);
const struct fins_area_tp* XX_finslib_search_area(struct fins_sys_tp* sys, const struct fins_address_tp* address,
                                                  int bits, uint32_t access, bool force);
int XX_finslib_wsa_errorcode_to_fins_retval(int errorcode);

#endif
