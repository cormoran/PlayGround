// Copyright 2016 Andre Burgaud. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package padding provides functions for padding blocks of plain text in the
// context of block cipher mode of encryption like ECB or CBC.

// https://github.com/andreburgaud/crypt2go
//
// Copyright (c) 2016 Andre Burgaud. All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:

//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Andre Burgaud nor the names of any
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
package lib

import (
	"bytes"
	"errors"
)

// Padding interface defines functions Pad and Unpad implemented for PKCS #5 and
// PKCS #7 types of padding.
type Padding interface {
	Pad(p []byte) ([]byte, error)
	Unpad(p []byte) ([]byte, error)
}

// Padder struct embeds attributes necessary for the padding calculation
// (e.g. block size). It implements the Padding interface.
type Padder struct {
	blockSize int
}

// NewPkcs5Padding returns a PKCS5 padding type structure. The blocksize
// defaults to 8 bytes (64-bit).
// See https://tools.ietf.org/html/rfc2898 PKCS #5: Password-Based Cryptography.
// Specification Version 2.0
func NewPkcs5Padding() Padding {
	return &Padder{blockSize: 8}
}

// NewPkcs7Padding returns a PKCS7 padding type structure. The blocksize is
// passed as a parameter.
// See https://tools.ietf.org/html/rfc2315 PKCS #7: Cryptographic Message
// Syntax Version 1.5.
// For example the block size for AES is 16 bytes (128 bits).
func NewPkcs7Padding(blockSize int) Padding {
	return &Padder{blockSize: blockSize}
}

// Pad returns the byte array passed as a parameter padded with bytes such that
// the new byte array will be an exact multiple of the expected block size.
// For example, if the expected block size is 8 bytes (e.g. PKCS #5) and that
// the initial byte array is:
// 	[]byte{0x0A, 0x0B, 0x0C, 0x0D}
// the returned array will be:
// 	[]byte{0x0A, 0x0B, 0x0C, 0x0D, 0x04, 0x04, 0x04, 0x04}
// The value of each octet of the padding is the size of the padding. If the
// array passed as a parameter is already an exact multiple of the block size,
// the original array will be padded with a full block.
func (p *Padder) Pad(buf []byte) ([]byte, error) {
	bufLen := len(buf)
	padLen := p.blockSize - (bufLen % p.blockSize)
	padText := bytes.Repeat([]byte{byte(padLen)}, padLen)
	return append(buf, padText...), nil
}

// Unpad removes the padding of a given byte array, according to the same rules
// as described in the Pad function. For example if the byte array passed as a
// parameter is:
// 	[]byte{0x0A, 0x0B, 0x0C, 0x0D, 0x04, 0x04, 0x04, 0x04}
// the returned array will be:
// 	[]byte{0x0A, 0x0B, 0x0C, 0x0D}
func (p *Padder) Unpad(buf []byte) ([]byte, error) {
	bufLen := len(buf)
	if bufLen == 0 {
		return nil, errors.New("cryptgo/padding: invalid padding size")
	}

	pad := buf[bufLen-1]
	padLen := int(pad)
	if padLen > bufLen || padLen > p.blockSize || padLen <= 0 {
		return nil, errors.New("cryptgo/padding: invalid padding size")
	}

	for _, v := range buf[bufLen-padLen : bufLen-1] {
		if v != pad {
			return nil, errors.New("cryptgo/padding: invalid padding")
		}
	}

	return buf[:bufLen-padLen], nil
}