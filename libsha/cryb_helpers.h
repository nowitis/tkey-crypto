// SPDX-License-Identifier: BSD-3-Clause
/*-
 * Copyright (c) 2012 The University of Oslo
 * Copyright (c) 2012-2016 Dag-Erling Smørgrav
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef SRC_LIBSHA_CRYB_HELPERS_H
#define SRC_LIBSHA_CRYB_HELPERS_H

#ifdef __riscv
#include <types.h>
#else
#include <stddef.h>
#include <stdint.h>
#endif

#define CRYB_ROR(N)                                            \
	static inline uint##N##_t ror##N(uint##N##_t i, int n)     \
	{                                                          \
		return (i << (-n & ((N)-1)) | i >> (n & ((N)-1)));     \
	}

#define CRYB_ROL(N)                                            \
	static inline uint##N##_t rol##N(uint##N##_t i, int n)     \
	{                                                          \
		return (i << (n & ((N)-1)) | i >> (-n & ((N)-1)));     \
	}

CRYB_ROL(32);

static inline uint32_t be32dec(const void *p)
{
	return ((uint32_t)((const uint8_t *)p)[3] |
		(uint32_t)((const uint8_t *)p)[2] << 8 |
		(uint32_t)((const uint8_t *)p)[1] << 16 |
		(uint32_t)((const uint8_t *)p)[0] << 24);
}

static inline void be32decv(uint32_t *u32, const void *p, size_t n)
{
	for (const uint8_t *u8 = p; n--; u8 += sizeof *u32, u32++)
		*u32 = be32dec(u8);
}

static inline void be32enc(void *p, uint32_t u32)
{
	((uint8_t *)p)[3] = u32 & 0xff;
	((uint8_t *)p)[2] = (u32 >> 8) & 0xff;
	((uint8_t *)p)[1] = (u32 >> 16) & 0xff;
	((uint8_t *)p)[0] = (u32 >> 24) & 0xff;
}

static inline void be32encv(void *p, const uint32_t *u32, size_t n)
{
	for (uint8_t *u8 = p; n--; u8 += sizeof *u32, u32++)
		be32enc(u8, *u32);
}

static inline void be64enc(void *p, uint64_t u64)
{
	((uint8_t *)p)[7] = u64 & 0xff;
	((uint8_t *)p)[6] = (u64 >> 8) & 0xff;
	((uint8_t *)p)[5] = (u64 >> 16) & 0xff;
	((uint8_t *)p)[4] = (u64 >> 24) & 0xff;
	((uint8_t *)p)[3] = (u64 >> 32) & 0xff;
	((uint8_t *)p)[2] = (u64 >> 40) & 0xff;
	((uint8_t *)p)[1] = (u64 >> 48) & 0xff;
	((uint8_t *)p)[0] = (u64 >> 56) & 0xff;
}

#endif