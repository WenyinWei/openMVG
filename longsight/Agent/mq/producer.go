package mq

import "github.com/nsqio/go-nsq"

type Producer struct {
	*nsq.Producer
}

func NewProducer(addr string) (*Producer, error) {
	p, err := nsq.NewProducer(addr, nsq.NewConfig())
	if err != nil {
		return nil, err
	}
	return &Producer{p}, err
}
