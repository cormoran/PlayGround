package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"fmt"

	"github.com/cormoran/PlayGround/crypt/aes_decryptability/lib"
)

func encrypt(text string, key []byte) (string, error) {
	padder := lib.NewPkcs7Padding(aes.BlockSize)
	textByte, err := padder.Pad([]byte(text))
	if err != nil {
		return "", err
	}
	block, err := aes.NewCipher([]byte(key))
	if err != nil {
		return "", err
	}
	result := make([]byte, aes.BlockSize+len(textByte))
	iv := result[:aes.BlockSize]
	if _, err := rand.Read(iv); err != nil {
		return "", err
	}
	encrypter := cipher.NewCBCEncrypter(block, iv)
	encrypter.CryptBlocks(result[aes.BlockSize:], textByte)
	return base64.StdEncoding.EncodeToString(result), nil
}

func decrypt(text string, key []byte) (string, error) {
	textByte, err := base64.StdEncoding.DecodeString(text)
	if err != nil {
		return "", err
	}
	block, err := aes.NewCipher([]byte(key))
	if err != nil {
		return "", err
	}
	if len(textByte) < aes.BlockSize {
		return "", fmt.Errorf("len(textByte) = %v < aes.BlockSize", len(textByte))
	}
	iv := textByte[:aes.BlockSize]
	encrypted := textByte[aes.BlockSize:]
	result := make([]byte, len(encrypted))
	decrypter := cipher.NewCBCDecrypter(block, iv)
	decrypter.CryptBlocks(result, encrypted)

	padder := lib.NewPkcs7Padding(aes.BlockSize)
	result, err = padder.Unpad(result)
	if err != nil {
		return "", err
	}
	return string(result), nil
}

func randomStr(n int) (string, error) {
	const letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

	b := make([]byte, n)
	if _, err := rand.Read(b); err != nil {
		return "", err
	}

	var result string
	for _, v := range b {
		result += string(letters[int(v)%len(letters)])
	}
	return result, nil
}

func main() {
	key := make([]byte, aes.BlockSize)
	if _, err := rand.Read(key); err != nil {
		panic(err)
	}
	key2 := make([]byte, aes.BlockSize)
	if _, err := rand.Read(key2); err != nil {
		panic(err)
	}

	const trialCnt int = 10000
	successCnt := 0

	for i := 0; i < trialCnt; i++ {
		s, err := randomStr(10 + (i % 10))
		if err != nil {
			panic(err)
		}
		enc, err := encrypt(s, key)
		if err != nil {
			panic(err)
		}
		dec, err := decrypt(enc, key)
		if err != nil {
			fmt.Println(err)
		}
		if s != dec {
			panic(fmt.Errorf("enc %v dec %v", enc, dec))
		}
		_, err = decrypt(s, key)
		if err == nil {
			fmt.Printf("succeed %v", s)
		}
		dec2, err := decrypt(enc, key2)
		if err == nil {
			successCnt++
			fmt.Printf("succeed2 \n\traw %v\n\tenc %v\n\tdec %v\n", s, enc, dec2)
		}
	}
	fmt.Printf("\nSucceeded: %v/%v = %v%%\n", successCnt, trialCnt, float64(successCnt)/float64(trialCnt)*100)
}
