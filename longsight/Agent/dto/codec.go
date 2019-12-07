package dto

import (
	"bytes"
	"encoding/gob"
	"log"
)

type Message struct {
	Type Type
	Body []byte
}

func Encode(msg interface{}) ([]byte, error) {
	var buf bytes.Buffer
	encoder := gob.NewEncoder(&buf)
	if err := encoder.Encode(msg); err != nil {
		log.Printf("Encode: gob cannot encode message: %s\n", err)
		return nil, err
	}
	return buf.Bytes(), nil
}

func Decode(raw []byte) (*Message, error) {
	var msg Message
	decoder := gob.NewDecoder(bytes.NewReader(raw))
	if err := decoder.Decode(&msg); err != nil {
		log.Printf("HandleMessage: gob cannot decode message: %s\n", err)
		return nil, err
	}
	return &msg, nil
}

func DecodeCaptureMessage(raw []byte) (*CaptureMessage, error) {
	var msg CaptureMessage
	decoder := gob.NewDecoder(bytes.NewReader(raw))
	if err := decoder.Decode(&msg); err != nil {
		log.Printf("HandleMessage: gob cannot decode message: %s\n", err)
		return nil, err
	}
	return &msg, nil
}

func DecodeCaptureCallbackMessage(raw []byte) (*CaptureCallbackMessage, error) {
	var msg CaptureCallbackMessage
	decoder := gob.NewDecoder(bytes.NewReader(raw))
	if err := decoder.Decode(&msg); err != nil {
		log.Printf("HandleMessage: gob cannot decode message: %s\n", err)
		return nil, err
	}
	return &msg, nil
}
