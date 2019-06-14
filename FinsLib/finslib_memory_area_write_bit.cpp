#include "fins.h"

/*
* int finslib_memory_area_write_bit( struct fins_sys_tp *sys, const char *start, const bool *data, size_t num_bits );
*
* ��Զ��PLC�Ĵ洢����д��һϵ��bitλ��
*
* �ú�������FINS_RETVAL _...�б��еĳɹ��������롣
* �������ΪFINS�豸ָ�룬��ʼ��ַ��charָ�룬��ʽ���ơ�CIO100.1����Ҫд����������ڵ��ڴ�ָ�룬��Ҫд���bitֵ����
*/

int finslib_memory_area_write_bit(struct fins_sys_tp *sys, const char *start, const bool *data, size_t num_bits) {

	int chunk_bit;
	size_t chunk_start;
	size_t chunk_length;
	size_t offset;
	size_t a;
	size_t todo;
	size_t bodylen;
	struct fins_command_tp fins_cmnd;
	const struct fins_area_tp *area_ptr;
	struct fins_address_tp address;
	int retval;

	if (num_bits == 0) return FINS_RETVAL_SUCCESS;
	if (sys == NULL) return FINS_RETVAL_NOT_INITIALIZED;
	if (start == NULL) return FINS_RETVAL_NO_WRITE_ADDRESS;
	if (data == NULL) return FINS_RETVAL_NO_DATA_BLOCK;
	if (sys->sockfd == INVALID_SOCKET) return FINS_RETVAL_NOT_CONNECTED;
	if (XX_finslib_decode_address(start, &address)) return FINS_RETVAL_INVALID_WRITE_ADDRESS;

	area_ptr = XX_finslib_search_area(sys, &address, 1, FI_WR, false);
	if (area_ptr == NULL) return FINS_RETVAL_INVALID_WRITE_AREA;

	offset = 0;
	todo = num_bits;
	chunk_start = address.main_address;
	chunk_start += area_ptr->low_addr >> 8;
	chunk_start -= area_ptr->low_id;
	chunk_bit = address.sub_address & 0x0f;

	do {
		chunk_length = FINS_MAX_WRITE_WORDS_SYSWAY;
		if (chunk_length > todo) chunk_length = todo;

		XX_finslib_init_command(sys, &fins_cmnd, 0x01, 0x02);

		bodylen = 0;

		fins_cmnd.body[bodylen++] = area_ptr->area;
		fins_cmnd.body[bodylen++] = (chunk_start >> 8) & 0xff;
		fins_cmnd.body[bodylen++] = (chunk_start) & 0xff;
		fins_cmnd.body[bodylen++] = 0x00;
		fins_cmnd.body[bodylen++] = (chunk_length >> 8) & 0xff;
		fins_cmnd.body[bodylen++] = (chunk_length) & 0xff;

		for (a = 0; a<chunk_length; a++) fins_cmnd.body[bodylen++] = data[offset + a];

		if ((retval = XX_finslib_communicate(sys, &fins_cmnd, &bodylen)) != FINS_RETVAL_SUCCESS) return retval;

		if (bodylen != 2) return FINS_RETVAL_BODY_TOO_SHORT;

		todo -= chunk_length;
		offset += chunk_length;
		chunk_start <<= 4;
		chunk_start += chunk_bit;
		chunk_start += chunk_length;
		chunk_bit = chunk_start & 0x0f;
		chunk_start >>= 4;

	} while (todo > 0);

	return FINS_RETVAL_SUCCESS;

}  /* finslib_memory_area_write_bit */
